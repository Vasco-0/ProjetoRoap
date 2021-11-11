#ifndef ROAP_HEADER_H_INCLUDED
#define ROAP_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct coord{ /*mesma função de um node name num grafo*/
    int l;
    int c;
    int w;
    
}coord;

typedef struct slot{
    int w;
    int p; 
    coord parent_position;

}slot;

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

typedef struct traceback{

    int flag_found;
    int steps; /*size of path */
    int total_cost;
    coord* path;

}traceback;

int N_mapas;
int vect_insert_pos;
int C_aux;


/*  inf->custo "infinito"
    out->não pertence ao grafo (visto que 0 já é um custo valido)*/
#define INF INT_MAX

/*================= lib.c ====================*/ 
FILE* open_file_in(char* filename);
FILE* open_file_out(char* filename);
int check_args(int argc, char**argv);
char* check_extension (char* nome_file_out, char* filename, int fase_flag);
void write_to_file(FILE* fptr,traceback* path,int flag);
void Data_Process_final(FILE* fptr, FILE* fptr_out,minHeap* PQ);
int isMapValid(int l,int c,int l1,int c1,int p);
FILE* maior_mapa(FILE* fptr, int* C_max, int* L_max, int* P_max, int fase_flag);

/*djisktra*/
traceback* dijsktra(lab_info* lab, minHeap* PQ,slot** slot_matrix);
int get_weight (int L, int C, lab_info* lab,slot** slot_matrix);
slot** init_slot_matrix(lab_info* lab);
int isEmpty(minHeap* PQ);
int is_neighbour_valid(coord* v,coord* atual,slot** slot_matrix,lab_info* lab,minHeap* PQ,int dir_flag);
int next_neighbour_same_dir(coord* v, int dir, lab_info* lab,slot** slot_matrix);
int isTarget(coord* u,lab_info* lab);
traceback* tracebackaroni(slot** slot_matrix,traceback* final_path,lab_info* lab,int target_flag,coord* u);
int mapAsNoSolution(slot** slot_matrix,coord* u_pop);

/*aux tools*/
void print_slot_matrix_w(slot** slot_matrix,lab_info* lab);
void conceptual_matrix_printer(lab_info* lab);
void PQ_print(minHeap* PQ, slot** slot_matix);


/*PQ*/
minHeap* PQ_init(minHeap* PQ, int V);
int PQ_find(minHeap* PQ, int l,int c); /*verifica se existe na queue o par (l,c) e retorna um apontador para a estrutura */
coord* PQ_pop(minHeap* PQ,slot** slo_matrix,coord* top);/*pop do valor do topo da queue*/
minHeap* PQ_restart(lab_info* lab, minHeap* PQ);
minHeap* PQ_update(minHeap* PQ, slot** slot_matrix, int l, int c);
minHeap* fixup(int idx,minHeap* PQ,slot** slot_matrix);
minHeap* fixdown(minHeap* PQ, slot** slot_matrix, int parent);
minHeap* exch(int a, int b,minHeap* PQ);
int less_pri(int a, int b,minHeap* PQ,slot** slot_matrix);
void free_PQ(minHeap *PQ, int V);




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