// no-comment.c
// Řešení IJC-DU1, příklad b), 25.3.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)
// Spravne bere 1 argument, v pripade vice, zbyle ignoruje.
// Zadani spatne adresy ukoncuje program.

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "error.h"
#define MAX_ARGC 2

int main(int argc, char **argv) {
  FILE *file = stdin;
  
  // Arguments check
  if(argc > 1) {
    if(argc > MAX_ARGC) warning("Too many arguments: %d of max %d\n", argc, MAX_ARGC);
    
    file = fopen(argv[1], "r");
    if(!file) error_exit("Could not open file: %s\n", argv[1]);
    
    // Check for invalid pipe
    struct stat f_in;
    struct stat f_out;
    if(stat(argv[1], &f_in)) {
      warning("stat: failed to get %s info\n", argv[1]);
    }
    if(fstat(STDOUT_FILENO, &f_out)) {
      warning("fstat: failed to get stdout info\n");
    }
    if(f_in.st_dev == f_out.st_dev && f_in.st_ino == f_out.st_ino) {
      error_exit("stdout redirected to input file\n");
    }
  }
  int state = 0;
  char c;
  while((c = fgetc(file)) != EOF) {
    switch(state) {
      case 0: \
        if(c == '/') state = 1;
        else {
          if(c == '"') state = 6;
          else if(c == '\'') state = 8;
          putchar(c);
        }
        break;
      case 1: \
        if(c == '/') state = 2;
        else if(c == '*') state = 4;
        else {
          state = 0;
          putchar('/');
          putchar(c);
        }
        break;
      case 2: \
        if(c == '\n') {
          state = 0;
          putchar(c);
        }
        else if(c == '\\') state = 3;
        break;
      case 3: \
        state = 2;
        break;
      case 4: \
        if(c == '*') state = 5;
        break;
      case 5: \
        if(c == '/') {
          state = 0;
          putchar(' ');
        }
        else if(c == '*') {
          state = 5;
        } else {
          state = 4;
        }
        break;
      case 6: \
        if(c == '"') state = 0;
        else if(c == '\\') state = 7;
        putchar(c);
        break;
      case 7: \
        state = 6;
        putchar(c);
        break;
      case 8: \
        if(c == '\'') state = 0;
        else if(c == '\\') state = 9;
        putchar(c);
        break;
      case 9: \
        state = 8;
        putchar(c);
        break;
      default:
        putchar(c);
        break;
    }
  }
  
  if(argc > 1) fclose(file);
  if(state != 0 && state != 2) {
    error_exit("Input file ended inside comment or string\n");
  }
  
  return EXIT_SUCCESS;
}
