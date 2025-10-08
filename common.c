#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common.h"


TagData* create_tag(){
    TagData *data = malloc(sizeof(TagData));
    if (!data) {
        return NULL; // caller handles error
    }

    // initialize all pointers to NULL
    data->version = NULL;
    data->title   = NULL;
    data->artist  = NULL;
    data->album   = NULL;
    data->year    = NULL;
    data->comment = NULL;
    data->genre   = NULL;
    data->composer = NULL;

    return data;

}

void free_tag(TagData *data) {
    if (!data) return;

    free(data->version);
    free(data->title);
    free(data->artist);
    free(data->album);
    free(data->year);
    free(data->comment);
    free(data->genre);
    free(data->composer);
    free(data);
}

int big_to_little_endian(char frame_size[4]){
    unsigned int size = 0;
    char swapped[4];
    swapped[0] = frame_size[3];
    swapped[1] = frame_size[2];
    swapped[2] = frame_size[1];
    swapped[3] = frame_size[0];

    memcpy(&size, swapped, 4);
    return size;

}

void little_to_big_endian(int *new_size , unsigned char size_bytes[4]){
    for(int i = 0;i < 4;i++){
        size_bytes[i] = *((char *)new_size + (3 - i));
    }    
}

