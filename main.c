#include<stdio.h>
#include<string.h>
#include "main.h"
#include "view.h"
#include "common.h"
#include "edit.h"

void display_error( ){
    printf("ERROR: ./a.out: INVALID ARGUMENTS\n\n");

    printf("USAGE:\n\n");

    printf("To view, please pass like: ./a.out -v mp3filename\n\n");

    printf("To edit, please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n\n");

    printf("To get help, pass like: ./a.out --help\n");
}

void display_help( ){
    printf("------------- HELP MENU -------------\n\n");

    printf("-v  -> to view mp3 file contents\n\n");

    printf("-e  -> to edit mp3 file contents\n");
    printf("      title\n\n");

    printf("    2.1. -t -> to edit song title\n");
    printf("    2.2. -a -> to edit artist name\n");
    printf("    2.3. -A -> to edit album name\n");
    printf("    2.4. -y -> to edit year\n");
    printf("    2.5. -m -> to edit content\n");
    printf("    2.6. -c -> to edit comment\n");
}

int main(int argc , char *argv[]){
    if(argc == 1){
        display_error();
        return 1;
    }
    else if((strcmp(argv[1] , "-h")) == 0 || (strcmp(argv[1] , "--help")) == 0) {
        display_help();
        return 1;
    }
    else if((strcmp(argv[1] , "-v")) == 0 ){
        if (argc < 3) {
        printf("Error: Missing MP3 filename.\n");
        return 1;
        }
        view_tags(argv[2]);
        return 0;
    }  
    else if((strcmp(argv[1] , "-e")) == 0 && (argc == 5)){
        edit_tags(argv[2],argv[3],argv[4]);
        return 1;
    }
    else{
        display_error();
        return 1;
    }

}
    