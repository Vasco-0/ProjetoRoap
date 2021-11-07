#include "roap_lib.h"

parede** init_wall_vect(parede** wall_vector,lab_info* new){
	wall_vector=(parede**)malloc(sizeof(parede*)*new->L);
			/*for(int i=1;i<4;i++)
			{
				//to avoid trying to acess non alloced memory
				//wall_vector[i]->next=(parede*)malloc(sizeof(parede));
				wall_vector[i]->c=0;
				wall_vector[i]->val=-4;
			}*/
			printf("hello");
			printf("%d",new->L);
	return wall_vector;
}

/*---------------------- Livre ----------------*/
parede* insert_col(int l,int c,int v,parede** wall_vector,lab_info* lab){ /*insere na lista organizado*/ 
	parede* new_col;
	wall_vector[l]->next=(parede*)malloc(sizeof(parede));

	return wall_vector[l]->next;
}

/*------------------Não Mexer - Vasco ----------------------*/
int is_wall_valid(int l,int c,int val, lab_info* lab){
	if(l>lab->L || c>lab->C || l<1 || c<1 || val<-1 || val==0)
		return -1;
	
	return 0;
}
