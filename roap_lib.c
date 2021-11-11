/*
	Library for auxilary functions
	->open_file
	->check_args 
	->check_extension
*/
#include "roap_lib.h"


FILE* open_file_in (char* filename){
    
    FILE *fp;  
	fp = fopen(filename, "r");
	if (fp == NULL){
		exit(0);
	}
	return fp;
}

FILE* open_file_out (char* filename){
    
    FILE *fp;

	fp = fopen(filename, "w");
	if (fp == NULL){
		printf("EXIT out\n"); fflush(stdout);
		exit(0);
	}

	return fp;
}

int check_args(int argc, char**argv){ 

	int flag;

	if((argc<2)||(argc>=4)){
        exit(0);
    }

    if(strcmp("-s", argv[1]) == 0){
        flag=1;
    }else{
		flag=2;
	}
	
	return flag;
}


char* check_extension (char* nome_file_out, char* filename, int fase_flag)
{
	char* check_ext;
	char ext_out1[] = ".sol1";
	char ext_out[]= ".sol";


	if (fase_flag==1)
    	nome_file_out=(char*) malloc(strlen(filename)+strlen(ext_out1)+1);
	
	if (fase_flag==2)
    	nome_file_out=(char*) malloc(strlen(filename)+strlen(ext_out)+1);

    strcpy(nome_file_out, filename);
    strtok(nome_file_out, ".");
    check_ext = strtok(NULL, ".");

	if (nome_file_out == NULL){
		exit(0);
	}
		
	if (fase_flag==1){
    	if(strcmp(check_ext, "in1")!=0){
        	exit(0);
		}
		strcat(nome_file_out, ext_out1); 
	}

	if (fase_flag==2){
    	if(strcmp(check_ext, "in")!=0){
        	exit(0);
		}
		strcat(nome_file_out, ext_out); 
	}
	return nome_file_out;
}

FILE* maior_mapa(FILE* fptr, int* C_max, int* L_max, int* P_max, int fase_flag){

    int i_P=0;

    int L_aux_m, C_aux_m, L1_aux_m, C1_aux_m, var_aux_m, P_aux_m;
    char A_var_m;

    N_mapas=0;
	*L_max=0;
	*C_max=0;
    *P_max=0;


	if(fase_flag==1){
    	while (((fscanf(fptr, "%d %d %d %d %c%d", 
                &L_aux_m, &C_aux_m, &L1_aux_m, &C1_aux_m, &A_var_m, &var_aux_m)) == 6) 
                && (A_var_m=='A')){

        	if(var_aux_m==6){
            	if(fscanf(fptr,"%*d %*d")!=0)
            	    exit(0);
        	}	

        	if(fscanf(fptr,"%d", &P_aux_m)!=1)
    	        exit(0);

        	if (C_aux_m > *C_max)
            	*C_max = C_aux_m;

        	if (L_aux_m > *L_max)
            	*L_max = L_aux_m;

        	while (i_P<P_aux_m){
            	if((fscanf(fptr, "%*d %*d %*d"))==0)
            	    i_P++;                 
        	}
        	i_P=0;
        	N_mapas++;
    	}
	}

	if(fase_flag==2){
    	while (((fscanf(fptr, "%d %d %d %d", 
                &L_aux_m, &C_aux_m, &L1_aux_m, &C1_aux_m)) == 4)){
			
        	if(fscanf(fptr,"%d", &P_aux_m)!=1)
    	        exit(0);

        	if (C_aux_m > *C_max)
            	*C_max = C_aux_m;

        	if (L_aux_m > *L_max)
            	*L_max = L_aux_m;

	        if(P_aux_m>*P_max)
            	*P_max=P_aux_m;			

        	while (i_P<P_aux_m){
            	if((fscanf(fptr, "%*d %*d %*d"))==0)
            	    i_P++;                 
        	}
        	i_P=0;
        	N_mapas++;
    	}
	}	


    rewind(fptr);
    return fptr;
}


void write_to_file(FILE* fptr, traceback* traceback)
{
	int i=0;

	fprintf(fptr,"\n\n%d", traceback->total_cost);
	if(traceback->total_cost>0){
		fprintf(fptr,"\n%d", traceback->steps);
		for(i=1;i<=traceback->steps;i++){
			fprintf(fptr,"\n%d %d %d", (traceback->path[i].l+1), traceback->path[i].c+1, traceback->path[i].w);
		}
	}
}


void Data_Process_final(FILE* fptr_in, FILE* fptr_out, minHeap* PQ){

    int i;
    int lin, col, val;
    int i_P;
    int a, L_aux, /*C_aux,*/ L1_aux, C1_aux, P_aux;
	traceback* final_path = NULL;
	lab_info* new=NULL;
	slot** slot_matrix = NULL;

	new = (lab_info*)malloc(sizeof(lab_info));

    while (((a=fscanf(fptr_in, "%d %d %d %d %d", 
                &L_aux, &C_aux, &L1_aux, &C1_aux,&P_aux)) == 5)){

		L1_aux=L1_aux-1;
		C1_aux=C1_aux-1;

		new->L=L_aux;
		new->C=C_aux;
		new->L_target=L1_aux;
		new->C_target=C1_aux;
		new->P=P_aux;

        a=teste_valid_mapa(L_aux, C_aux, L1_aux, C1_aux, 'A', 1, 0, 0, P_aux);

        if(a!=0){
            /*situação mapa inválido*/
            if (a==-3)
                exit(0);

            while (i_P<P_aux){ /* salta o resto da leitura do mapa*/
                if((fscanf(fptr_in, "%*d %*d %*d"))==0)
                    i_P++;
            }  
            i_P=0;
        }

        else{
            //mapa válido 
			slot_matrix=init_slot_matrix(new);

            while (i_P<P_aux){
                if(fscanf(fptr_in,"%d %d %d", &lin, &col, &val)==3){
					lin = lin-1;
					col = col-1;
                    if(((lin>=0)&&(lin<L_aux)&&(col>=0)&&(col<C_aux)) && ((val>0) || (val=-1)))
					{
						slot_matrix[lin][col].p=val;
                    }
                    i_P++;                    
                }
            }  
            i_P=0;
	    }

		final_path = dijsktra(new, PQ,slot_matrix); 

		for(i=1;i<=final_path->steps;i++){
			printf("\n (%d,%d)",final_path->path[i].l,final_path->path[i].c);
		}
		printf("\n broke %d",final_path->steps);

		write_to_file(fptr_out, final_path);

		free(final_path->path);
		free(final_path);
		
    }
	free(new);
    return;
}

int get_weight (int L, int C, lab_info* lab,slot** slot_matrix)
{
	if(L>=lab->L || C>=lab->C || L<0 || C<0)
		return -2; /*out of bounds*/

	return slot_matrix[L][C].p;
}

minHeap* PQ_init(minHeap* PQ, int V)
{
	int i;
	PQ = (minHeap*)malloc(sizeof(minHeap));
	PQ->minHeap_array = (coord**) malloc(V*sizeof(coord*));
	for(i=0; i<V;i++){
		PQ->minHeap_array[i] = (coord*) malloc(sizeof(coord));
	}
	PQ->size=V;

	return PQ;
}


minHeap* PQ_restart(lab_info* lab, minHeap* PQ)
{
	int i, j, k=0;
	int size_of_new;

	size_of_new = (lab->L)*(lab->C);
	PQ->size=size_of_new;
	/*PQ->idx_vect=(int*)malloc(PQ->size*sizeof(int));*/

	printf("L %d, C %d\n", lab->L, lab->C); fflush(stdout);
	for(i=0; i<lab->L; i++){
		for(j=0; j<lab->C; j++){
			PQ->minHeap_array[k]->l=i;
			PQ->minHeap_array[k]->c=j;
			/*PQ->idx_vect[l*C_max+c]=k;*/
			k++;
		}
	}

	/*
	int l, c, z;
	for(i=0; i<lab->L; i++){
		l=i;
		c=i;
		PQ->minHeap_array[k]->l=l;
		PQ->minHeap_array[k]->c=c;
		k++;
		printf("k=%d l=%d c=%d\n", k, l, c); fflush(stdout);
		for (j=l, z=c; j>=0 || z>=0; j--, z--){
			PQ->minHeap_array[k]->l=l;
			PQ->minHeap_array[k]->c=k-1;
			k++;
			printf("->k=%d l=%d c=%d\n", k, l, c); fflush(stdout);
			PQ->minHeap_array[k]->l=j-1;
			PQ->minHeap_array[k]->c=c;	
			k++;
			printf("->k=%d l=%d c=%d\n", k, l, c); fflush(stdout);
		}
	}
	*/
	
	return PQ;
}


minHeap* PQ_update(minHeap* PQ, slot** slot_matrix, int l, int c) /*receber coordenada que recebeu atualização (menor custo) e reordena heap*/
{
	int i;
	//printf("\nin update\n"); fflush(stdout);
	for(i=0; i<PQ->size; i++){
		if((l==PQ->minHeap_array[i]->l) && (c==PQ->minHeap_array[i]->c)){	

			PQ = fixup(i, PQ, slot_matrix);
		}
	}

	return PQ;
}


coord* PQ_pop(minHeap* PQ, slot** slot_matrix, coord* top)
{	
	//printf("in pop\n"); fflush(stdout);
	top->l=PQ->minHeap_array[0]->l;
	top->c=PQ->minHeap_array[0]->c;
	
	exch(0, PQ->size-1, PQ);
	PQ->size--;
	PQ=fixdown(PQ, slot_matrix, 0);	
	
	return top;
}



minHeap* fixdown(minHeap* PQ, slot** slot_matrix, int parent)
{	
	int left = 2*parent+1;
    int right = 2*parent+2;
	int min;


	/*printf("\nin fixdown\n"); fflush(stdout);
	printf("size: %d\nparent: %d, left: %d, right: %d\n", PQ->size, parent, left, right); fflush(stdout);
	printf("w_parent %d, w_left %d, w_right %d\n", 
				slot_matrix[PQ->minHeap_array[parent]->l][PQ->minHeap_array[parent]->c].w,
				slot_matrix[PQ->minHeap_array[left]->l][PQ->minHeap_array[left]->c].w,
				slot_matrix[PQ->minHeap_array[right]->l][PQ->minHeap_array[right]->c].w); fflush(stdout);
	*/
	if (PQ->size>1)
  	{
		if ((left >= PQ->size) ||  left < 0){
      		left = -1;
			//printf("left>\n"); fflush(stdout);
			}
    	if ((right >= PQ->size) || right < 0){
      		right = -1;
			//printf("right>\n"); fflush(stdout);
			}

    	if (left != -1  &&  less_pri(left, parent, PQ, slot_matrix)==0){
			min=left;
			//printf("min= left\n"); fflush(stdout);
		}
		else{
			min = parent;
			//printf("min=parent\n"); fflush(stdout);
		}
		if (right != -1  &&  less_pri(right, min, PQ, slot_matrix)==0)
      		min=right;

		if(min!=parent){
			//printf("exch\n"); fflush(stdout);
			exch(parent, min, PQ);
      		PQ=fixdown(PQ, slot_matrix, min);
    	}
  	}
	//printf("out fixdown\n"); fflush(stdout);
	return PQ;
}


minHeap* fixup(int idx, minHeap* PQ, slot** slot_matrix)
{
	int parent=(idx-1)/2;
	//printf("->in fixup\n"); fflush(stdout);
	/*printf("w_parent %d, w_idx %d\n", 
				slot_matrix[PQ->minHeap_array[parent]->l][PQ->minHeap_array[parent]->c].w,
				slot_matrix[PQ->minHeap_array[idx]->l][PQ->minHeap_array[idx]->c].w); fflush(stdout);
*/
	if(less_pri(parent, idx, PQ, slot_matrix)==1){
		//printf("swap\n"); fflush(stdout);
		//printf("pre exch: prt l=%d prt c=%d, idx l=%d, idx c=%d\n", PQ->minHeap_array[parent]->l, PQ->minHeap_array[parent]->c,
		 //		PQ->minHeap_array[idx]->l, PQ->minHeap_array[idx]->c); fflush(stdout);
		PQ = exch(parent, idx, PQ);
		//printf("pos exch: prt l=%d prt c=%d, idx l=%d, idx c=%d\n", PQ->minHeap_array[parent]->l, PQ->minHeap_array[parent]->c,
		 //		PQ->minHeap_array[idx]->l, PQ->minHeap_array[idx]->c); fflush(stdout);
		PQ = fixup(parent, PQ, slot_matrix);
	}
	//printf("->out fixup\n"); fflush(stdout);
	return PQ;
}



int PQ_find(minHeap* PQ, int l, int c) /*recebe coordenada e vê se está no PQ*/
{
	int i;

	for(i=0; i<PQ->size; i++){
		if((l==PQ->minHeap_array[i]->l) && (c==PQ->minHeap_array[i]->c)){
			return 1;
		}
	}		
	return 0;
}


int less_pri(int a, int b, minHeap* PQ, slot** slot_matrix)
{	
	/*
	para i=a,b:
	mat_coord_l= heap[i].l
	mat_coord_c= heap[i].c
	custo= mat[mat_coord_l][mat_coord_c].w
	=>if custo_a < custo_b...
	*/
	if(slot_matrix[PQ->minHeap_array[a]->l][PQ->minHeap_array[a]->c].w
		> slot_matrix[PQ->minHeap_array[b]->l][PQ->minHeap_array[b]->c].w)
		return 1;
	else
		return 0;
}

minHeap* exch(int a, int b, minHeap* PQ)
{	
	coord *aux;

	aux=PQ->minHeap_array[a];
	PQ->minHeap_array[a]=PQ->minHeap_array[b];
	PQ->minHeap_array[b]=aux;

	
	/*idx_vect: vetor de tamnaho V, cujos indices sao a celula 
	(convertida para notação de vertice), que contem o indice atual da celula em heap*/
	/*
	int i_a=PQ->idx_vect->[PQ->minHeap_array[a]->l * C_max + PQ->minHeap_array[a]->c;
	int i_b=PQ->idx_vect->[PQ->minHeap_array[b]->l * C_max + PQ->minHeap_array[b]->c]
	int temp = i_a;
	i_a=i_b;
	i_b=temp;
	*/

	return PQ;
}


void free_PQ(minHeap *PQ, int V)
{
	int i;
	for(i=0; i<V; i++){
		free(PQ->minHeap_array[i]);
	}
	free(PQ->minHeap_array);
	free(PQ);
}