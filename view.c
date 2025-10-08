#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "view.h"
#include "common.h"


TagData *view_tags(const char *filename){

    FILE *fp = fopen(filename,"rb");
    if (!fp) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    unsigned char header[11];
    fread(header,1,10,fp);
    header[10] = '\0';

    if((strncmp(header,"ID3",3)) !=  0){
        printf("Error: Not a valid MP3 with ID3 tags\n");
        fclose(fp);
        return NULL;
    }

    if(header[3] != 3 || header[4] != 0){
        printf("Unsupported ID3 version: %d.%d\n", header[3], header[4]);
        fclose(fp);
        return NULL;
    }

    TagData *data = create_tag(); //create a variable pointer of type TagData

    if (data == NULL) {
        printf("Memory allocation failed !!");
        return NULL;
    }

    char version_str[10];
    sprintf(version_str, "ID3v2.%d", header[3]);
    version_str[8] = '\0';
    data -> version = strdup(version_str);   //strdup = strcpy + malloc (it allocates a memory)
    
    //printf("%s",data -> version); //to print version 

    unsigned char frame_header[10];
    unsigned int tag_size = big_to_little_endian(header + 6);

    
    printf("\n+-------------------SELECTED VIEW DETAILS------------------------+\n");
    printf("+----------------------------------------------------------------+\n");
    printf("             MP3 TAG READER AND EDITOR FOR ID3v2.3            \n");
    printf("+----------------------------------------------------------------+\n");

    while(ftell(fp) < tag_size + 10){

        fread(frame_header,1,10,fp);
        
        unsigned char frame_tag[5];

        strncpy(frame_tag,frame_header,4);  //copies first 4 bytes from frame_header to frame_tag to check for the tag

        frame_tag[4] = '\0';
        
        if (frame_tag[0] == '\0')    //if frame tag is empty break and means end of frame
            break;

        unsigned int frame_size = big_to_little_endian(frame_header + 4);

        unsigned char *frame_data = malloc(frame_size + 1);

        // fread(frame_data,1,frame_size,fp) -> to read data of size equal to frame_size from each frame tag

        if (fread(frame_data, 1, frame_size, fp) != frame_size) {
        free(frame_data);
        break;
        }

        frame_data[frame_size] = '\0'; 

        if(strcmp(frame_tag,"TIT2") == 0){
            data -> title = strdup((char *)frame_data + 1);
            printf("TITLE      :       %s\n", data -> title);
        }
        else if(strcmp(frame_tag,"TPE1") == 0){
            data -> artist = strdup((char *)frame_data + 1);
            printf("ARTIST     :       %s\n", data -> artist);
        }
        else if(strcmp(frame_tag,"TALB") == 0){
            data -> album = strdup((char *)frame_data + 1);
            printf("ALBUM      :       %s\n", data -> album);
        }
        else if(strcmp(frame_tag,"TYER") == 0){
            data -> year = strdup((char *)frame_data + 1);
            printf("YEAR       :       %s\n", data -> year);
        }
        else if(strcmp(frame_tag,"TCON") == 0){
            data -> genre = strdup((char *)frame_data + 1);
             printf("GENRE      :       %s\n", data -> genre);
        }
        else if(strcmp(frame_tag,"COMM") == 0){
            data -> comment = strdup((char *)frame_data + 1);
            printf("COMMENT    :       %s\n", data -> comment);
        }
        else if(strcmp(frame_tag,"TCOM") == 0){
            data -> composer = strdup((char *)frame_data + 1);
            printf("COMPOSER   :       %s\n", data -> composer);
        }

        free(frame_data);
        
    }

    printf("+----------------------------------------------------------------+\n");
    printf("+----------------DETAILS DISPLAYED SUCCESSFULLY------------------+\n\n");
    free_tag( data );
    fclose( fp );
    return data;
}
