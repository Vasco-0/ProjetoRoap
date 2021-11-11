#include "roap_lib.h"

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


