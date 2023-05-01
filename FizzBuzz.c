#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fizzbuzz(int x);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("FizzBuzz \n");
        return 1;
    }

    int x = atoi(argv[1]);
    fizzbuzz(x);

    return 0;
}

void fizzbuzz(int x){
    char **results = malloc(sizeof(char*) * (x + 1));
    if (results == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for(int i = 0; i <=x; i++){
        if (i % 3 == 0 && i % 7 == 0) {
            results[i] = strdup("FIZZBUZZ");
        } else if (i % 3 == 0) {
            results[i] = strdup("BUZZ");
        } else if (i % 7 == 0) {
            results[i] = strdup("FIZZ");
        } else {
            results[i] = NULL;
        }
    }

    for (int i = 0; i <= x; i++) {
        if (results[i] != NULL) {
            printf("%s\n", results[i]);
        } else {
            printf("%d\n", i);
        }
        free(results[i]);
    }

    free(results);
    
    }