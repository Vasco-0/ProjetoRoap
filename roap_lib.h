#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct coord_parent{

    int l;
    int c;
    
}coord_parent;

typedef struct coord_minH{

    int l;
    int c;
    int cost;
    
}coord_minH;

typedef struct slot{

    int w;
    coord_parent* position;

}slot;

typedef struct minHeap{

    int size; /*LxC*/

    coord_minH* minHeap_array;

}minHeap;

typedef struct Lab
{
    int L;
    int C;
    char variante;
    int L1;
    int C1;
    int L2;
    int C2;
    int P;    
} Lab;

typedef struct lab_info{ /*para o final*/

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

/*para paredes*/
typedef struct parede
{
    int L;
    int C;
    int custo;
} parede;



char* nome_file_out;

int C_max;
int L_max;
int N_mapas;
int vect_insert_pos;

/*vars final*/
int hash_size;
int C_aux;
int* st;
int* wt;
parede** walls;



/*  inf->custo "infinito"
    out->não pertence ao grafo (visto que 0 já é um custo valido)*/
#define INF INT_MAX

/*================= lib.c ====================*/ 
FILE* open_file_in(char* filename);
FILE* open_file_out(char* filename);
int check_args(int argc, char**argv);
void check_extension(char* filename, int fase_flag);
void write_to_file(char* nome_file_out);

int** mat_alloc(int** mat, int L, int C);
int* vect_alloc(int* vect, int size);
void free_mat(int** mat, int L);



/*============= intsolver.c ==================*/

    /*data ops*/
int* Data_Process(int* vect, Lab* new_lab, FILE* fptr,int** mat);
void vect_to_File(int* vect, char * nome_file_out);
int teste_valid_mapa(int L_aux, int C_aux, int L1_aux, int C1_aux, char A_var, int var_aux, int L2_aux, int C2_aux, int P_aux);
FILE* maior_mapa(FILE* fptr);
    /*struct ops*/
Lab* struct_insert (Lab* new_lab,
		int L_aux,int C_aux, int L1_aux , int C1_aux, int L2_aux , int C2_aux,
		char A_var, int var_aux, int P_aux);
int* insere_resposta_vect(int* vect, int resposta);

    /*solver*/
int solver (Lab* new_lab, int** mat);
int solver_1 (Lab* new_lab, int** mat);
int solver_2 (Lab* new_lab, int** mat);
int solver_3 (Lab* new_lab, int** mat);
int solver_4 (Lab* new_lab, int** mat);
int solver_5 (Lab* new_lab, int** mat);
int solver_6 (Lab* new_lab, int** mat);

        /*aux*/
FILE* maior_P(FILE* fptr, int* P_max);
int hash_key(int L, int C, int C_dim);
parede* struct_wall_insert(parede* new_wall, int l, int c, int val);
        /*hash*/
parede** walls_vect_init(parede** vect, int P_max);
parede** hash_insert(parede** vect, parede* p, int idx);
int hash_get(parede** vect, int idx, int L, int C);
parede** hash_clear(parede** vect);
/*so para teste*/
void hash_print(parede** vect);

void free_walls(parede** heap, int P);

/*djisktra*/
lab_info* Data_Process_final(FILE* fptr, parede** walls,lab_info* lab);
int get_weight (int L, int C, lab_info* lab);



int get_weight_beta(int l,int c, lab_info* lab);
lab_info* read_file_beta(lab_info* new);



slot** init_slot_matrix(lab_info* lab);
void print_slot_matrix_w(slot** slot_matrix,lab_info* lab);
void conceptual_matrix_printer(lab_info* lab);

#endif