#include "roap_lib.h"

void print_slot_matrix_w(slot** slot_matrix,lab_info* lab){

	for(int j=0; j<lab->L; j++){

		for(int k=0;k<lab->C; k++){
			printf("%d",slot_matrix[j][k].w);
		}
		printf("\n");
	}
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

void PQ_print(minHeap* PQ, slot** slot_matix)
{
	int i;

	printf("\nin print, size %d\n", PQ->size); fflush(stdout);
	printf("PQ: [\n");
	for(i=0; i<PQ->size; i++){
		printf("(%d %d %d)\n", PQ->minHeap_array[i]->l, PQ->minHeap_array[i]->c,
		slot_matix[PQ->minHeap_array[i]->l][PQ->minHeap_array[i]->c].w);
	}
		printf("]\n");
}


/*
int part(minHeap *PQ, slot** slot_matrix, int l, int r)
{
    int i, j;
    int v = PQ->minHeap_array[r]; 
	i = l-1; 
	j = r;  
    for (;;) {
        while (lesspri(++i, v))
        
        while (less(v, --j)){
           if (j == l) break;
        }
        if (i >= j) break;
        exch(i, j);
    }
    exch(a[i], a[r]);
    return i;
}
void quicksort(Item a[], int l, int r, int (*less) (Item, Item))
{
   
    int i;
    if (r <= l) return;
    i = part(a, l, r, less_pri());
    quicksort(a, l, i-1, less_pri());
    quicksort(a, i+1, r, less);
}
*/