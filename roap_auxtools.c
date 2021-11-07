#include "roap_lib.h"

void print_slot_matrix_w(slot** slot_matrix,lab_info* lab){

	for(int j=0; j<lab->L; j++){

		for(int k=0;k<lab->C; k++){
			printf("%d",slot_matrix[j][k].w);
		}
		printf("\n");
	}
}

/*-------------Livre ---------------*/
void conceptual_matrix_printer(lab_info* lab){
/* for debug purposes only - Not working*/

	int i,j;

	for(i=1;i<lab->L;i++){
		for(j=1;j<lab->C;j++){
			printf("%d",get_weight(i,j,lab));
		}
		printf("\n");
	}

}


int get_weight_beta(int l,int c, lab_info* lab){

	if(l>lab->L || c>lab->C || l<1 || c<1)
		return -2; /*out of bounds*/
	if((l=1) && (c==3)) 				
		return 10;
	if((l=2) && (c==2))
		return 3; 
	if(l=2 && c==1)
		return 2; 
	if(l=2 && c==3)
		return 2; 
	if(l=3 && c==3)
		return 3; 
	if((l=2) && (c==4))
		return 1; 
	if((l=4) && (c==2))
		return 5; 
	if(l=5 && c==2)
		return 6; 
	if(l=4 && c==3)
		return 2; 
	if(l=3 && c==1)
		return 1; 
	return 0;

}



/*Em progresso - Vasco - nota: enquanto o read file não está pronto posso ir testando o algoritmo*/
lab_info* read_file_beta(lab_info* new){

		new=malloc(sizeof(lab_info));
		new->L=5;
		new->C=5;
		new->L_target=3;
		new->C_target=4;
		new->P=10;
	printf("read file beta");
	slot** slot_matrix=init_slot_matrix(new);
	print_slot_matrix_w(slot_matrix,new);


	return new;

}

void hash_print(parede** vect)
{
	int i;

	printf("hash:\n[");
	for(i=0; i<hash_size; i++){
		if(vect[i]!=NULL)
			printf(", (%d %d %d)", vect[i]->L, vect[i]->C, vect[i]->custo);
	}
		printf("]\n\n");
}