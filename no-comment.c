// no-comment.c
// Řešení IJC-DU1, příklad b), 25.2.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)
// Spravne bere 1 argument, v pripade vice, zbyle ignoruje.
// Zadani spatne adresy ukoncuje program.

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
    
    int state = 0;
    char c;
    while((c = fgetc(file)) != EOF) {
        switch(state) {
            case 0: if(c == '/') state = 1;
                    else {
                        if(c == '"') {
                            state = 5;
                        }
                        putchar(c);
                    }
                    break;
            case 1: if(c == '/') state = 2;
                    else if(c == '*') state = 3;
                    else {
                        state = 0;
                        putchar('/');
                        putchar(c);
                    }
                    break;
            case 2: if(c == '\n') {
                        state = 0;
                        putchar(c);
                    }
                    else if(c == '\\') state = 7;
                    break;
            case 3: if(c == '*') state = 4;
                    break;
            case 4: if(c == '/') {
                    state = 0;
                    putchar(' ');
                    }
                    else if(c != '*') state = 3;
                    break;
            case 5: if(c == '"') state = 0;
                    else if(c == '\\') state = 6;
                    putchar(c);
                    break;
            case 6: state = 5;
                    putchar(c);
                    break;
            case 7: state = 2;
                    break;
            default:
                putchar(c);
                break;
        }
    }
    
    if(argc > 1) fclose(file);
    return EXIT_SUCCESS;
}