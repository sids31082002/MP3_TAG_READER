#ifndef COMMON_H
#define COMMON_H
#define MAX 100

typedef struct{
    char *version;
    char *title;
    char *artist;
    char *album;
    char *year;
    char *comment;
    char *genre;
    char *composer;
}TagData;

TagData* create_tag();

void free_tag(TagData *data);

int big_to_little_endian(char frame_size[4]);

void little_to_big_endian(int *new_size , unsigned char size_bytes[4]);


#endif
