#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv){
    char * filepath;
    if (argc != 2){
        printf("[*]No outfile provided... Setting default output\n");
        char* temp = "./tempOut";
        filepath = temp;
    }
    else{
        filepath = argv[1];
    }
    FILE * dst;
    if((dst = fopen(filepath,"w")) == NULL){
        printf("[!]ERROR: unable to open file %s for writing\n",filepath);
        return -1;
    }

    printf("[*]Please enter something to write to the file! Press Ctrl+D when finished\n");
    char* buf = malloc(sizeof(char) * 128);
    size_t numread;
    do{
        numread = fread(buf,sizeof(char),128,stdin);
        fwrite(buf,numread,sizeof(char),dst);
    } while(numread == 128);

    printf("\n[*]Thank you!\n");
}