// no-comment.c
// Řešení IJC-DU1, příklad b), 24.2.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)


#include <stdlib.h>
#include <stdio.h>
#include "error.h"

#define MAX_ARGC 2

int main(int argc, char **argv) {
    
    FILE *file = stdin;
    if(argc > 1) {
        if(argc > MAX_ARGC) warning("Too many arguments: %d of max %d\n", argc, MAX_ARGC);

        file = fopen(argv[1], "r");
        if(!file) error_exit("Could not open file: %s\n", argv[1]);
    }
    
    char c;
    while((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    
    if(argc > 1) {
        putchar('\n');
        fclose(file);
    }
    
    return EXIT_SUCCESS;
}