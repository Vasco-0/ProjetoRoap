/*

 93199 Vasco Oliveira 
 92957 Rodrigo Murta
GR104

*/

#include "roap_lib.h"

/*
*	Description: allocates and initalizes a matrix to store some necessary values to the algorithm like the current distance (weight) of a cell to the source
*
*	Arguments: pointer to struct lab_info containing matrix dimentions to allocate
*
*	Return: slot_matrix
*
*/
slot** init_slot_matrix(lab_info* lab)
{
	int i,j,k;

	slot** slot_matrix = (slot**)malloc((lab->L)*sizeof(slot*));

	for( i=0; i<(lab->L) ;i++)
	{
		slot_matrix[i]=(slot*)malloc(lab->C*sizeof(slot));
	}

	for( j=0; j<(lab->L); j++){

		for( k=0;k<(lab->C); k++){
			slot_matrix[j][k].w=INF;
			slot_matrix[j][k].p=0;
			slot_matrix[j][k].flag=0;
		}
	}
	return slot_matrix;
}



/*
*	Description: Runs a Dijkstra's algorithm to find shortest path by cost, 
				using a priority queue PQ and matrix containing the information for 
				wall cost, current path cost, parent position and other flags
*
*	Arguments: pointer to struct lab_info containing matrix various information, priority queue PQ, slot_matrix
*
*	Return: vector with current map's "breached" walls, to be inserted in file 
*
*/
traceback* dijsktra(lab_info* lab, minHeap* PQ, slot** slot_matrix)
{
	traceback* final_path=NULL;
	int dir_flag; /*right 1 left 2 down 3 up 4*/
	int target_flag=0;
	int cost_n; /*cost of neighbour path*/
	int alt; /*to compare weights*/
	coord* v = NULL; 
	coord* u_pop = NULL;

	PQ = PQ_restart(lab,PQ);


	v = (coord*)malloc(sizeof(coord)); 
	u_pop = (coord*)malloc(sizeof(coord));

	slot_matrix[0][0].w=0; /*src*/
	slot_matrix[0][0].parent_position.l=0;
	slot_matrix[0][0].parent_position.c=0;
	PQ = PQ_update(PQ,slot_matrix,0,0);


	while(!isEmpty(PQ))
	{
		u_pop = PQ_pop(PQ,slot_matrix,u_pop);
		slot_matrix[u_pop->l][u_pop->c].flag=1;


		if(slot_matrix[u_pop->l][u_pop->c].w==INF){
			break;
		}

		/*printf("\n\n popped (%d,%d)",u_pop->l,u_pop->c);*/

		if(isTarget(u_pop,lab)==1)
		{
			target_flag=1; 
			break;
		}

		/*for right neighbour*/
		v->l=u_pop->l;
		v->c=u_pop->c+1;
		dir_flag=1;
		if((cost_n = is_neighbour_valid(v,u_pop,slot_matrix,lab,PQ,dir_flag))>=0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; 
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
		if((cost_n = is_neighbour_valid(v,u_pop,slot_matrix,lab,PQ,dir_flag))>=0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w;
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
		if((cost_n = is_neighbour_valid(v,u_pop,slot_matrix,lab,PQ,dir_flag))>=0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; 
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
		if((cost_n = is_neighbour_valid(v,u_pop,slot_matrix,lab,PQ,dir_flag))>=0)
		{
			alt = cost_n + slot_matrix[u_pop->l][u_pop->c].w; 
			if (alt < slot_matrix[v->l][v->c].w ){
				slot_matrix[v->l][v->c].w = alt;
				slot_matrix[v->l][v->c].parent_position.l=u_pop->l;
				slot_matrix[v->l][v->c].parent_position.c=u_pop->c;
				PQ = PQ_update(PQ,slot_matrix,v->l,v->c);
			}
		}

	}/*end and time for traceback*/
	
	if(target_flag==1)
	{
		final_path=tracebackaroni(slot_matrix,final_path,lab,target_flag,u_pop);
	}
	else
	{
		final_path=tracebackaroni(slot_matrix,final_path,lab,target_flag,u_pop);
	}
	

	free(v);
	free(u_pop);
	return final_path;

}


/*
	Description: checks empty priority queue

	Arguments: PQ

	Return: 0 if PQ is empty

*/
int isEmpty(minHeap* PQ){
	/*checks if priority queue is empty*/
	return PQ->size == 0;
}


/*
	Description: checks if current neighbour being analysed of current position is a valid path

	Arguments: coordenates of current cell and neighbour being analysed, direction indicator, and data structures

	Return: cost of neighbour (0 if white) if is valid or -1 if not

*/
int is_neighbour_valid(coord* v, coord* atual, slot** slot_matrix, lab_info* lab, minHeap* PQ, int dir_flag){

	int atual_weight;
	int neighbour_weight;
	int next_neighbour_same_dir_w;

	/*is out of bounds*/
	if((v->l>=lab->L) || (v->c>=lab->C) || (v->l<0) || (v->c<0)) 
		return-1;

	if(slot_matrix[v->l][v->c].flag==1) 
	/*is not in the priority queue*/
	{
			return -1;
	} 
	
	atual_weight=slot_matrix[atual->l][atual->c].p;

	if (atual_weight>0)
	{ /*crossing a wall*/
		int l_dir_atual_parent = atual->l - slot_matrix[atual->l][atual->c].parent_position.l;
		int c_dir_atual_parent = atual->c - slot_matrix[atual->l][atual->c].parent_position.c;

		int l_dir_neigh_atual = v->l - atual->l;
		int c_dir_neigh_atual = v->c - atual->c;

		if((l_dir_atual_parent==l_dir_neigh_atual) && (c_dir_atual_parent==c_dir_neigh_atual))
		{ /* same direction*/ 
			neighbour_weight=slot_matrix[v->l][v->c].p;

			if(neighbour_weight==0)
			{ /*crosses to white*/
				return 0;
			}
			else
			{/*crosses to not white*/
				return-1;
			}
		}
		else /*not same direction when crossing*/
		{
			return -1;
		}
	}
	else 
	{ /*not crossing*/
		neighbour_weight=slot_matrix[v->l][v->c].p;

		if(neighbour_weight==0)
		{/*white to white*/
			return 0;
		}
		if(neighbour_weight<0)
		{ /*black tile*/
			return -1;
		}
		if(neighbour_weight>0)
		{ /*checks if next neighbour of grey tile in same direction is white - a bit redundant with crossing logics*/ 
			next_neighbour_same_dir_w=next_neighbour_same_dir(v,dir_flag,lab,slot_matrix);

			if(next_neighbour_same_dir_w==0)
			{
				return neighbour_weight;
			}else{
				return -1;
			}
		}
	}
	return -3; 
}


/*
	Description: checks if popped cell is the target.

	Arguments: coordinates of popped cell, pointer to struct lab_info containing coordinates of target .

	Return: 1 if is target, 0 if not.

*/
int isTarget(coord* u,lab_info* lab){

	if((u->l == lab->L_target) && (u->c == lab->C_target)){
		return 1;
	}
	else
	{
		return 0;
	}
}


/*
	Description: builds the path back to source once it Dijkstra found the target

	Arguments: vector of breached walls, target flag, target coordinates, map  and lab_info  to check boundaries

	Return:

*/
traceback* tracebackaroni(slot** slot_matrix, traceback* final_path, lab_info* lab, int target_flag, coord* target)
{
	int break_walls=0;
	int a;
	int step_count = 0; /*to include starting point*/
	int crawler_l = target->l;
	int crawler_c = target->c;
	int total_cost;

	if(target_flag==0)
	{
		final_path=(traceback*)malloc(sizeof(traceback));
		final_path->path=(coord*)malloc(sizeof(coord));
		final_path->total_cost=-1;
		final_path->steps=1;

		return final_path;
	}

	int aux_l=slot_matrix[crawler_l][crawler_c].parent_position.l;
	int aux_c=slot_matrix[crawler_l][crawler_c].parent_position.c;
	total_cost=slot_matrix[aux_l][aux_c].w;

	while(1)
	{
		if((crawler_l==0) && (crawler_c==0))
			break;

		if((crawler_l < 0)||(crawler_l>=lab->L)||(crawler_c < 0)||(crawler_c>=lab->C))
			break;

		step_count++;
		crawler_l=slot_matrix[crawler_l][crawler_c].parent_position.l;
		crawler_c=slot_matrix[crawler_l][crawler_c].parent_position.c;
	}

	final_path=(traceback*)malloc(sizeof(traceback));
	final_path->path=(coord*)malloc(step_count*sizeof(coord));

	crawler_l=target->l;
	crawler_c=target->c;

	while(1)
	{
		if((crawler_l==0) && (crawler_c==0))
			break;	

		if((crawler_l < 0)||(crawler_l>=lab->L)||(crawler_c < 0)||(crawler_c>=lab->C))
			break;

		crawler_l=slot_matrix[crawler_l][crawler_c].parent_position.l;
		crawler_c=slot_matrix[crawler_l][crawler_c].parent_position.c;
		if((a=slot_matrix[crawler_l][crawler_c].p)>0)
		{
			break_walls++;
			final_path->path[break_walls].l=crawler_l;
			final_path->path[break_walls].c=crawler_c;
			final_path->path[break_walls].w=a;

		}
	}
	final_path->steps=break_walls;
	final_path->total_cost=total_cost;
	return final_path;
}



/*
	Description: checks neighbour after grey cell colour

	Arguments: cell coordinates, direction flag, map and lab_info to check boundaries

	Return:

*/
int next_neighbour_same_dir(coord* v, int dir, lab_info* lab,slot** slot_matrix)
{
	int w;
	int l_next;
	int c_next;

	switch (dir)
	{
	case 1: /*right c+1*/
		c_next = v->c+1;
		l_next = v->l;
		if((l_next>=lab->L) || (c_next>=lab->C) || (c_next<0) || (l_next<0))
			return -1;

		w = slot_matrix[l_next][c_next].p;
		return w;
	case 2: /*left*/
		c_next = v->c-1;
		l_next = v->l;
		if((l_next>=lab->L) || (c_next>=lab->C) || (c_next<0) || (l_next<0))
			return -1;
			
		w = slot_matrix[l_next][c_next].p;
		return w;
	case 3: /*down*/
		c_next = v->c;
		l_next = v->l+1;
		if((l_next>=lab->L) || (c_next>=lab->C) || (c_next<0) || (l_next<0))
			return -1;
			
		w = slot_matrix[l_next][c_next].p;
		return w;
	case 4: /**/
		c_next = v->c;
		l_next = v->l-1;
		if((l_next>=lab->L) || (c_next>=lab->C) || (c_next<0) || (l_next<0))
			return -1;
			
		w = slot_matrix[l_next][c_next].p;
		return w;
	default:
		return -2;
	}

}
