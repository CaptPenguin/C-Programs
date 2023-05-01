#include <stdio.h>
#include <stdlib.h>


int main(){

    char* outstand = "Hello, Standard output!\n";
    char* errstand = "Hello, Standard error!\n";
    char* inptStand = (char *) malloc(129);
    fprintf(stdout,"%s",outstand);
    fprintf(stderr,"%s",errstand);

    fread(inptStand,sizeof(char),128,stdin);
    printf("Standard input had this!:\n");
    fwrite(inptStand,sizeof(char),128,stdout);
    printf("\nDone!\n");


}