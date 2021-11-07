#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 9999

typedef struct coord{

    int l;
    int c;
    
}coord;

typedef struct slot{

    int w;
    coord* position;

}slot;

typedef struct minHeap{

    int size;

    coord** minHeap_array;

}minHeap;



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
  
    struct parede* prev;// not sure if needed
    int c;
    int val;
    struct parede* next;

}parede;

/* lib.c -------------------------------------*/

FILE* open_file(char** argv, int fase_flag);/*NM-Vasco*/
void write_to_file(char* nome_file_out); /*L*/

int check_args(int argc, char**argv); /*NM - Vasco*/
char* check_extension(char** argv, int fase_flag); /*NM - Vasco*/
int is_lab_valid(lab_info* new);

lab_info* read_file(FILE* fptr,lab_info* head);/*Livre*/
int is_wall_valid(int l,int c,int val, lab_info* lab);
lab_info* insert_lab_list(lab_info* head,lab_info* new_lab);/*Livre*/

int get_weight(int l, int c, lab_info* lab, parede** wall); /*EP - Vasco*/
parede* insert_col(int l,int c,int v,parede** wall_vector,lab_info* lab);

parede** init_wall_vect(parede** wall_vector,lab_info* new);

lab_info* solve(lab_info* lab, parede** wall);/*EP - Vasco*/

slot** init_slot_matrix(lab_info* lab);

/* intsolver.c ------------------------------------- */




/* djisktra.c ------------------------------------- */


/* auxtools.c ------------------------------------- */
void print_wall_vector(parede** wall_vect,lab_info* lab);
void conceptual_matrix_printer(parede** wall, lab_info* lab);/*L*/
lab_info* read_file_beta(lab_info* lab);/*EP-Vasco*/
int get_weight_beta(int l,int c, lab_info* lab); /*while */
void print_slot_matrix_w(slot** slot_matrix,lab_info* lab);


#endif