#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lib.c 
FILE* open_file(char** argv, int fase_flag);
int check_args(int argc, char**argv);
char* check_entension(char** argv, int fase_flag);
void write_to_file(char* nome_file_out);

// intsolver.c

// djisktra.c

#endif