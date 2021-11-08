/*

*/

#include "roap_lib.h"


slot** init_slot_matrix(lab_info* lab)
{

	slot** slot_matrix = (slot**)malloc((lab->L)*sizeof(slot*));

	for(int i=0; i<(lab->C) ;i++)
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

void dijsktra(parede** walls, lab_info* lab, minHeap* PQ){

	int rn, ln, dn, un;  /*right left down and up neighbours*/

	PQ = restart_PQ(lab,PQ);

	int rn, ln, dn, un;  /*right left down and up neighbours*/

	

	slot** slot_matrix = init_slot_matrix(lab);

	int l_cursor, c_cursor;
	/*restart_PQ(lab);*/
	
}

minHeap* restart_PQ(lab_info* lab,minHeap* PQ){

	int size_of_new = (lab->L)*(lab->C);
 	/*TO DO meter por ordem de adjacentes*/
	PQ->size=size_of_new;

	return PQ;
}

int isEmpty(minHeap* PQ){
	return PQ->size == 0;
}

int is_neighbour_valid(parede** walls, int ln, int cn,slot** slot_matrix,lab_info* lab){
	/*inside map*/
	int b;

	if((ln>lab->L) || (cn>lab->C) || (ln<1) || (cn<1))
		return-1;

	if(PQ_find(ln,cn)!=1) /*if it isnt in PQ is not valid*/
		return -1;
		
	int a = get_weight(walls, ln, cn, lab);

	if(a==-1){ /*casa preta*/
		return -1;
	}

	int lp = slot_matrix[ln][cn].parent_position.l; /*não pode vir de casa cinza*/
	int cp = slot_matrix[ln][cn].parent_position.l;

	b=get_weight(walls, lp, cp, lab); /*peso do pai*/

	if(a>0) /*if casa cinza*/
	{
		if(b>0)
		{
			return -1;
		}else{
			return b; /*se cinza e veio de branca retorna valor de cinza*/
		}
	}
	if(a==0) /*se for branca*/
	{
		if(b==0) /* vinda de branca its all good*/
		{
			return 0;
		}
		else /*branca vinda de cinza tem de vir de branca na mm direção   B->C->B */
		{
			int gpl=slot_matrix[lp][cp].parent_position.l;
			int gpc=slot_matrix[lp][cp].parent_position.c;

		}
	}
	/*returns weight or zero or -2 if invalid neighbour*/ 
	return 0;
}


void explore_neighbours(slot** slot_matrix, int l, int c){
	
	/*check all directions */
	/* 3 x is neighbour valid -> comparação de weights -> PQ_update or not  */

}