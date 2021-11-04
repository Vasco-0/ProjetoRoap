#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* alternativa de usar matrix LxC*/
typedef struct lab_info{

    int id; /* for debug purposes */
    int L;
    int C;
    int L_target;
    int C_target;
    int P;
    int valid_flag;
    int resposta;
    lab_info * next;

}lab_info;


/* lib.c */

/*file IO*/
FILE* open_file(char** argv, int fase_flag);
void write_to_file(char* nome_file_out);

/*verifications*/
int check_args(int argc, char**argv);
char* check_entension(char** argv, int fase_flag);
int is_lab_valid(lab_info* lab);

void read_file(FILE* fptr);
char** matrix_alloc_fill(lab_info* lab);
lab_info* new_lab_alloc_fill(int L,int C,int L_t,int C_t,int P,int valid_flag);
lab_info* insert_lab_list(lab_info* head,lab_info* new_lab);

void is_neighbour_valid(int l_n,int c_n);

void matrix_printer(char** lab_matrix, lab_info* lab);

/* intsolver.c */

/* djisktra.c */

#endif