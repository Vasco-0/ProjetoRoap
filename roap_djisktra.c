/*
    nota: agora cada função vai ter 3 estados

    ----Não Mexer - Nome ----       (quando a função estiver terminada e funcional) se quisermos alterar algo primeiro falar com o outro
    ----Em progresso - Nome ---     (não funcional mas a trabalhar nela) tmb é para não mexer
    ----Livre-----                  (trabalho por fazer não reclamado) 

    NOTA extra: código só vai para o git se não houver seg faults !!

    Nota extra extra: no main se mexer não é para mexer em funções que sejam NM ou EP do outro.

*/

#include "roap_lib.h"


slot** init_slot_matrix(lab_info* lab)
{

	slot** slot_matrix = (slot**)malloc(((lab->L)+1)*sizeof(slot*));

	for(int i=0; i<((lab->C)+1) ;i++)
	{
		slot_matrix[i]=(slot*)malloc(sizeof(slot));
	}
	printf("%d",lab->L);
	for(int j=0; j<(lab->L); j++){

		for(int k=0;k<(lab->C); k++){
			slot_matrix[j][k].w=INF;
		}
	}

	return slot_matrix;
}

/*void swap(coord** a, coord** b)
{
	coord **aux = **a;
	**a = **b;
	**b = **aux;
}*/

void dijsktra(lab_info* lab){

	int l_cursor, c_cursor;
	restart_PQ(lab);
	

	
	
}

void restart_PQ(lab_info* lab){

	int size_of_new = (lab->L)*(lab->C);

	PQ.size=size_of_new;

	for(int i=0;i<size_of_new;i++)
	{
		PQ.minHeap_array[i]->cost=INF;
	}
}

int isEmpty(){
	return PQ.size == 0;
}

int is_neighbour_valid(int l, int c){
	/*inside map*/
	/*is in minH ? no ? PQ_find -> not valid*/
	/*get_weight = black -> not valid*/
	/*get_weight = cinza -> slot parent cinza ? not valid*/
	/*returns weight or zero or -2 if invalid neighbour*/ 
	}

void explore_neighbours(slot** slot_matrix, int l, int c){
	
	/*check all directions */
	/* 3 x is neighbour valid -> comparação de weights -> PQ_update or not  */

}