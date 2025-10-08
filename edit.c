#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "edit.h"
#include "common.h"
#include "view.h"

void edit_tags(const char *edit , const char *new_text,const char *filename){
    FILE *fp1 = fopen(filename , "r");
    if(fp1 == NULL){
        printf("File not found !!");
        return;
    } 
    FILE *fp2 = fopen("temp.mp3" , "w");
    if(fp2 == NULL){
        printf("File not found !!");
        return;
    } 
    char header[11];
    fread(header,1,10,fp1);
    header[10] = '\0';
    if(header[0]!='I' || header[1] != 'D' || header[2] != '3'){
        printf("Invalid file format !!");
        return;
    }
    if(header[3]!=3 || header[4]!=0){
        printf("Invalid file format !!");
        return;
    }
    
    fwrite(header,1,10,fp2);
    char *tags[7] = {"TIT2","TALB","TPE1","TYER","TCON","COMM","TCOM"};
    char *options[7] = {"-t","-a","-A","-y","-m","-c","-C"};    //array of pointers used to map the required tag to edit and set which tag is req to be edited
    
    char target_frame[5] ;
    for (int i = 0; i < 7; i++) {
        if (strcmp(edit, options[i]) == 0) {
            strcpy(target_frame, tags[i]);  // copy matching frame ID
            break;
        }
    }

    if (target_frame[0] == '\0') {
        printf("Unknown edit option: %s\n", edit);
        fclose(fp1);
        fclose(fp2);
        return;
    }

    unsigned char frame_header[10];
    while(fread(frame_header,1,10,fp1) == 10){
        char frame_signature[5];
        memcpy(frame_signature,frame_header,4);

        if(frame_signature[0] == '\0'){
            fwrite(frame_header,1,10,fp2);
            char ch;
            while((ch = fgetc(fp1)) != EOF){
                fputc(ch,fp2);
            }
            break;
        }

        unsigned int frame_size = big_to_little_endian(frame_header + 4);

        unsigned char *frame_data = malloc(frame_size + 1);
        if(frame_data == NULL){
            fclose(fp1);
            fclose(fp2);
            return ;
        }

        fread(frame_data,1,frame_size,fp1);

        int flag = 0;
        if(strcmp(frame_signature,target_frame) == 0){
            flag = 1;
        }
        
        if(flag == 1){
            int new_size = strlen(new_text) + 1;
            unsigned char size_bytes[4];

            little_to_big_endian(&new_size , size_bytes);

            memcpy(frame_header+4,size_bytes,4);

            fwrite(frame_header,1,10,fp2);
            fputc(0x00,fp2);
            fwrite(new_text,1,strlen(new_text),fp2);

        }
        else{
            fwrite(frame_header,1,10,fp2);
            fwrite(frame_data,1,frame_size,fp2);

        }

        free(frame_data);

    }

    int ch;
    while ((ch = fgetc(fp1)) != EOF) {
        fputc(ch, fp2);                           //copy all other data that is song data after the tags to the new file
    }
    
    // char audio_buffer;
    // size_t bytes_read ;

    // while((bytes_read = fread(&audio_buffer,1,1,fp1)) > 0){
    //     fwrite(&audio_buffer,1,1,fp2);
    // }

    fclose(fp1);
    fclose(fp2);

    remove(filename);
    rename("temp.mp3",filename);

    TagData *data = view_tags(filename);
    printf("\nTag edited successfully!!\n");
    


}