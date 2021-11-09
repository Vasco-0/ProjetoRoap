/*

*/

#include "roap_lib.h"


slot** init_slot_matrix(lab_info* lab)
{

	slot** slot_matrix = (slot**)malloc(((lab->L)+1)*sizeof(slot*));

	for(int i=0; i<((lab->C)+1) ;i++)
	{
		slot_matrix[i]=(slot*)malloc(sizeof(slot));
	}

	for(int j=0; j<((lab->L)+1); j++){

		for(int k=0;k<((lab->C)+1); k++){
			slot_matrix[j][k].w=INF;
		}
	}

	return slot_matrix;
}

traceback* dijsktra(parede** walls, lab_info* lab, minHeap* PQ)
{

	traceback* final_path;
	int dir_flag; /*right 1 left 2 down 3 up 4*/
	int target_flag=0;
	int cost_at_end;
	int cost_n; /*cost of neighbour path*/
	int alt; /*to compare weights*/
	coord* v;  /*do i need to alloc this pointers to structs ??*/
	coord* u_pop;
	slot** slot_matrix = init_slot_matrix(lab);
	PQ = restart_PQ(lab,PQ);

	slot_matrix[1][1].w=0; /*src*/
	slot_matrix[1][1].parent_position.l=1;
	slot_matrix[1][1].parent_position.c=1;
	PQ = PQ_update(PQ,slot_matrix,1,1);

	while(!isEmpty(PQ))
	{
	
		u_pop = PQ_pop(PQ); /*in first iteration must be src*/ 
		
		if(isTarget(u_pop,lab)==1)
		{
			target_flag=1;
			cost_at_end = slot_matrix[u_pop->l][u_pop->c].w; 
			break;
		}

		/*for right neighbour*/
		v->l=u_pop->l;
		v->c=u_pop->c+1;
		dir_flag=1;
		if((cost_n = is_neighbour_valid(walls,v,slot_matrix,lab,PQ,dir_flag))>0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; /*custo neighbour + custo caminho até agora percorrido*/
			if (alt < slot_matrix[v->l][v->c].w ){
				slot_matrix[v->l][v->c].w = alt;
				slot_matrix[v->l][v->c].parent_position.l=u_pop->l;
				slot_matrix[v->l][v->c].parent_position.c=u_pop->c;
				PQ = PQ_update(PQ,slot_matrix,v->l,v->c);
			}
		}
		else
		{

		}
		/*for left neighbour*/
		v->l=u_pop->l;
		v->c=u_pop->c-1;
		dir_flag=2;
		if((cost_n = is_neighbour_valid(walls,v,slot_matrix,lab,PQ,dir_flag))>0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; /*custo neighbour + custo caminho até agora percorrido*/
			if (alt < slot_matrix[v->l][v->c].w ){
				slot_matrix[v->l][v->c].w = alt;
				slot_matrix[v->l][v->c].parent_position.l=u_pop->l;
				slot_matrix[v->l][v->c].parent_position.c=u_pop->c;
				PQ = PQ_update(PQ,slot_matrix,v->l,v->c);
			}
		}
		else
		{

		}
		/*for down neighbour*/
		v->l=u_pop->l +1;
		v->c=u_pop->c;
		dir_flag=3;
		if((cost_n = is_neighbour_valid(walls,v,slot_matrix,lab,PQ,dir_flag))>0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; /*custo neighbour + custo caminho até agora percorrido*/
			if (alt < slot_matrix[v->l][v->c].w ){
				slot_matrix[v->l][v->c].w = alt;
				slot_matrix[v->l][v->c].parent_position.l=u_pop->l;
				slot_matrix[v->l][v->c].parent_position.c=u_pop->c;
				PQ = PQ_update(PQ,slot_matrix,v->l,v->c);
			}
		}
		else
		{

		}
		/*for up neighbour*/
		v->l=u_pop->l-1;
		v->c=u_pop->c;
		dir_flag=4;
		if((cost_n = is_neighbour_valid(walls,v,slot_matrix,lab,PQ,dir_flag))>0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; /*custo neighbour + custo caminho até agora percorrido*/
			if (alt < slot_matrix[v->l][v->c].w ){
				slot_matrix[v->l][v->c].w = alt;
				slot_matrix[v->l][v->c].parent_position.l=u_pop->l;
				slot_matrix[v->l][v->c].parent_position.c=u_pop->c;
				PQ = PQ_update(PQ,slot_matrix,v->l,v->c);
			}
		}
		else
		{

		}
	}/*end and time for traceback*/
	
	if(target_flag==1)
	{

	}else
	{
		final_path=init_trace(final_path,0,-1);
		/*return traceback with flag of not found*/
	}
	

}

minHeap* PQ_restart(lab_info* lab,minHeap* PQ){

	int size_of_new = (lab->L)*(lab->C);
 	/*TO DO meter por ordem de adjacentes*/
	PQ->size=size_of_new;
	PQ->dim=size_of_new;

	return PQ;
}

int isEmpty(minHeap* PQ){
	return PQ->size == 0;
}

int is_neighbour_valid(parede** walls, coord* v,slot** slot_matrix,lab_info* lab,minHeap* PQ,int dir_flag){
	/*inside map*/
	int b;

	if((v->l>lab->L) || (v->c>lab->C) || (v->l<1) || (v->l<1))
		return-1;

	if(PQ_find(v->l,v->c,PQ)!=1) /*if it isnt in PQ is not valid*/
		return -1;
		
	int a = get_weight(walls, v->l, v->c, lab);

	if(a==-1){ /*casa preta*/
		return -1;
	}

	int lp = slot_matrix[v->l][v->c].parent_position.l; /*não pode vir de casa cinza*/
	int cp = slot_matrix[v->l][v->c].parent_position.c;

	b=get_weight(walls, lp, cp, lab); /*peso do pai*/

	if(a>0) /*if casa cinza a prox na mm direção não pode ser cinza !*/
	{
		if(b>0)
		{
			b=get_weight(walls, lp, cp, lab);
			return -1;
		}else{
			return a; /*se cinza e veio de branca retorna valor de cinza*/
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
			int lg=slot_matrix[lp][cp].parent_position.l; /*peso do avô*/
			int cg=slot_matrix[lp][cp].parent_position.c;

			if (((v->l)-lp == lp-lg) && ((v->c)-cp == cp-cg)){

				return a;
			}
			else
			{
				return -1;
			}

		}
	}
	/*returns weight or zero or -2 if invalid neighbour*/ 
	return 0;
}

int isTarget(coord* u,lab_info* lab){

	if(u->l == lab->L_target || u->c == lab->C_target){
		return 1;
	}
	else
	{
		return 0;
	}
}

traceback* tracebackaroni(slot** slot_matrix,traceback* final_path)
{
	int step_count;
	final_path=init_trace(final_path,step_count,1);

}

traceback* init_trace(traceback* final_path,int step_count,int found_flag)
{
	if(found_flag==-1) /*map has no solution*/
	{
		final_path=(traceback*)malloc(sizeof(traceback));
		final_path->steps=-1;
		final_path->total_cost=-1;
	}

	if(found_flag==1)
	{




	}

	return final_path;
}
