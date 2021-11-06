#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    aqui da mesma forma as estruturas e cabeçalhos vão ter as mesmas 3 designações
    NM - nome
    EP - nome
    L
*/

/*NM - Vasco*/
typedef struct lab_info{

    int id; /* for debug purposes */
    int L;
    int C;
    int L_target;
    int C_target;
    int P;
    int B; 
    int valid_flag;
    struct lab_info * next;
    /*talvez adicionar lista de paredes* partidas*/

}lab_info;

/*NM- Vasco*/
typedef struct parede{
    int l;
    int c;
    int val;

}parede;

/* lib.c -------------------------------------*/

FILE* open_file(char** argv, int fase_flag);/*NM-Vasco*/
void write_to_file(char* nome_file_out); /*L*/

int check_args(int argc, char**argv); /*NM - Vasco*/
char* check_extension(char** argv, int fase_flag); /*NM - Vasco*/
int is_lab_valid(lab_info* new);

lab_info* read_file(FILE* fptr,lab_info* head);/*Livre*/
lab_info* insert_lab_list(lab_info* head,lab_info* new_lab);/*Livre*/

int get_weight(int l, int c, lab_info* lab, parede** wall); /*EP - Vasco*/

void conceptual_matrix_printer(parede** wall, lab_info* lab);/*L*/

lab_info* solve(lab_info* lab, parede** wall);/*EP - Vasco*/
lab_info* read_file_beta(lab_info* lab);/*EP-Vasco*/


/* intsolver.c ------------------------------------- */




/* djisktra.c ------------------------------------- */

#endif