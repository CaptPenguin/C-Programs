#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 157

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    int input_byte, output_byte;

    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("Error: cannot open input file '%s'\n", argv[1]);
        return 1;
    }

    output_file = fopen(argv[2], "wb");
    if (output_file == NULL) {
        printf("Error: cannot open output file '%s'\n", argv[2]);
        return 1;
    }

    while ((input_byte = fgetc(input_file)) != EOF) {
        output_byte = input_byte ^ KEY;
        fputc(output_byte, output_file);
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    char *file_contents = (char *) malloc(file_size);
    fread(file_contents, 1, file_size, input_file);

    fwrite(file_contents, 1, file_size, stdout);
    printf("\nFile size: %ld bytes\n", file_size);


    fclose(input_file);
    free(file_contents);


    return 0;
}





