#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
    FILE *src_file, *dest_file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    long int file_size;
    long total_bytes = 0;
    int percent_complete;

    if(argc < 3){
        fprintf(stderr, "Usage: %s src_file dest_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    src_file = fopen(argv[1], "rb");
    if (src_file == NULL){
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    dest_file = fopen(argv[2], "wb");
    if(dest_file == NULL){
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    fseek(src_file, 0L, SEEK_END);
    file_size = ftell(src_file);
    fseek(src_file, 0L, SEEK_SET);

    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, src_file)) > 0) {
        total_bytes += bytes_read;
        fwrite(buffer, sizeof(char), bytes_read, dest_file);
        int new_percent_complete = (int)(((float)total_bytes / (float)file_size) * 100);
        if (new_percent_complete != percent_complete) {
            percent_complete = new_percent_complete;
            printf("\rCopying %s to %s ...\n<%-20s> %d%% ", argv[1], argv[2], "====================", percent_complete);
            fflush(stdout);
        }
    }

    printf("\nCopy Completed\n");

    fclose(src_file);
    fclose(dest_file);

    return 0;
}