#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct coord{ /*mesma função de um node name num grafo*/
    int l;
    int c;
    
}coord;

typedef struct slot{
    int w;
    coord parent_position;

}slot;

typedef struct traceback{

    int flag_found;
    int steps; /*size of path */
    int total_cost;
    coord* path;

}traceback;

typedef struct minHeap{

    int size; /*LxC quando iniciado*/
    coord** minHeap_array; /*double pointer para facilidade de rearranjar array*/

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


int N_mapas;
int vect_insert_pos;

int hash_size;
int C_aux;


/*  inf->custo "infinito"
    out->não pertence ao grafo (visto que 0 já é um custo valido)*/
#define INF INT_MAX

/*================= lib.c ====================*/ 
FILE* open_file_in(char* filename);
FILE* open_file_out(char* filename);
int check_args(int argc, char**argv);
char* check_extension (char* nome_file_out, char* filename, int fase_flag);
void write_to_file(char* nome_file_out);
lab_info* Data_Process_final(FILE* fptr,minHeap* PQ, parede** walls,lab_info* lab);

FILE* maior_mapa(FILE* fptr, int* C_max, int* L_max, int* P_max, int fase_flag);

/*hash*/
parede** walls_vect_init(parede** vect, int P_max);
parede** hash_insert(parede** vect, parede* p, int idx);
int hash_get(parede** vect, int idx, int L, int C);
parede** hash_clear(parede** vect);
int hash_key(int L, int C, int C_dim);
parede* struct_wall_init(parede* new_wall, int l, int c, int val);
void free_walls(parede** heap, int P);

/*djisktra*/
traceback* dijsktra(parede** walls, lab_info* lab, minHeap* PQ);
int get_weight (parede** walls, int L, int C, lab_info* lab);
slot** init_slot_matrix(lab_info* lab);
int isEmpty(minHeap* PQ);
int is_neighbour_valid(parede** walls, coord* v,slot** slot_matrix,lab_info* lab,minHeap* PQ,int dir_flag);
int isTarget(coord* u,lab_info* lab);
traceback* tracebackaroni(slot** slot_matrix,traceback* final_path);
traceback* init_trace(traceback* final_path,int step_count,int found_flag);

/*aux tools*/
void print_slot_matrix_w(slot** slot_matrix,lab_info* lab);
void conceptual_matrix_printer(parede** walls, lab_info* lab);
void hash_print(parede** vect);
void PQ_print(minHeap* PQ, slot** slot_matix);


/*PQ*/
minHeap* PQ_init(minHeap* PQ, int V);
int PQ_find(minHeap* PQ, int l,int c); /*verifica se existe na queue o par (l,c) e retorna um apontador para a estrutura */
coord* PQ_pop(minHeap* PQ,slot** slo_matrix);/*pop do valor do topo da queue*/
minHeap* PQ_restart(lab_info* lab, minHeap* PQ);
minHeap* PQ_update(minHeap* PQ, slot** slot_matrix, int l, int c);
minHeap* fixup(int idx,minHeap* PQ,slot** slot_matrix);
minHeap* fixdown(minHeap* PQ, slot** slot_matrix, int parent);
minHeap* exch(int a, int b,minHeap* PQ);
int less_pri(int a, int b,minHeap* PQ,slot** slot_matrix);




/*============= intsolver.c ==================*/

    /*data ops*/
int* Data_Process(int* vect, Lab* new_lab, FILE* fptr,int** mat);
void vect_to_File(int* vect, char * nome_file_out);
int teste_valid_mapa(int L_aux, int C_aux, int L1_aux, int C1_aux, char A_var, int var_aux, int L2_aux, int C2_aux, int P_aux);
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


int** mat_alloc(int** mat, int L, int C);
int* vect_alloc(int* vect, int size);
void free_mat(int** mat, int L);
/**/
#endif