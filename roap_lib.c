/*
	93199 Vasco Oliveira
	92957 Rodrigo Murta
*/
#include "roap_lib.h"

/*
*	Description: opens file to read
*
*	Arguments: name of file to open
*
*	Return: pointer to file
*
*/
FILE* open_file_in (char* filename){
/* self explanatory */
    FILE *fp;  
	fp = fopen(filename, "r");
	if (fp == NULL){
		exit(0);
	}
	return fp;
}


/*
*	Description: opens file to read
*
*	Arguments: name of file to open
*
*	Return: pointer to file
*
*/
FILE* open_file_out (char* filename){
/* self explanatory */
    FILE *fp;

	fp = fopen(filename, "w");
	if (fp == NULL){
		
		exit(0);
	}

	return fp;
}


/*
*	Description: checks arguments of argv and indicates project fase
*
*	Arguments: argc, argv
*
*	Return: flag for project fase
*
*/
int check_args(int argc, char**argv){ 
/* self explanatory */
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


/*
*	Description: checks extention of file to read and generates name of file to write
*
*	Arguments: name of file to write, to change, name of file to read, flag for project fase
*
*	Return:
*
*/
char* check_extension (char* nome_file_out, char* filename, int fase_flag)
{
	/* self explanatory */
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


/*
*	Description: reads file onde and checks largest dimensions to allocate data structures once 
*
*	Arguments: pointers to update peak map dimensions, pointer to file to read, fase flag
*
*	Return: file pointer (rewinded)
*
*/
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



/*
*	Description: writes solution to file
*
*	Arguments: solution vector, flag if the source is the same as target, file pointer
*
*	Return: void
*
*/
void write_to_file(FILE* fptr, traceback* traceback, int notvalid)
{
	/*self explanatory */
	int i=0;

	if(notvalid==2){
		fprintf(fptr,"0\n\n");
		return;
	}

	if(notvalid==0){
		fprintf(fptr,"-1\n\n");
		return;
	}

	fprintf(fptr,"%d\n", traceback->total_cost);
	if(traceback->total_cost>0){
		fprintf(fptr,"%d\n", traceback->steps);
		for(i=traceback->steps;i>=1;i--){
			fprintf(fptr,"%d %d %d\n", (traceback->path[i].l+1), traceback->path[i].c+1, traceback->path[i].w);
		}

	}
	fprintf(fptr,"\n\n");
}


/*
*	Description: Processes file. for each map: reads map data to fill structures, sovles map with dijkstra and writes to file
*
*	Arguments: file pointers, pointer to PQ inicialized in main
*
*	Return: void
*
*/
void Data_Process_final(FILE* fptr_in, FILE* fptr_out, minHeap* PQ){
 /*like a secondary main function that executes once and produces the output*/
    int i;
    int lin, col, val;
    int i_P;
    int a, L_aux, L1_aux, C1_aux, P_aux;
	traceback* final_path = NULL;
	lab_info* new=NULL;
	slot** slot_matrix = NULL;
	int not_valid_flag=1;
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

        not_valid_flag=isMapValid(L_aux, C_aux, L1_aux+1, C1_aux+1,P_aux);

        if(not_valid_flag==0){
            /*situação mapa inválido*/
            while (i_P<P_aux){ /* salta o resto da leitura do mapa*/
                if((fscanf(fptr_in, "%*d %*d %*d"))==0)
                    i_P++;
            }  
            i_P=0;
			write_to_file(fptr_out, final_path,not_valid_flag);
        }

		if(not_valid_flag==2)
		{
			 while (i_P<P_aux){ /* salta o resto da leitura do mapa*/
                if((fscanf(fptr_in, "%*d %*d %*d"))==0)
                    i_P++;
            }  
            i_P=0;
			write_to_file(fptr_out, final_path,not_valid_flag);

		}

        if(not_valid_flag==1)
		{
            /*mapa válido */
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
			final_path = dijsktra(new, PQ,slot_matrix); 

			write_to_file(fptr_out, final_path,not_valid_flag);

			for(i=0;i<new->L;i++){ 
        		free(slot_matrix[i]);
    		}

    		free(slot_matrix);
			free(final_path->path);
			free(final_path);
	    }

    }
	free(new);
    return;
}



/*
*	Description: gets cost(weight) of cell
*
*	Arguments: matrix, cell coordinates and lab info
*
*	Return: returns wall weight
*
*/
int get_weight (int L, int C, lab_info* lab, slot** slot_matrix)
{
	if(L>=lab->L || C>=lab->C || L<0 || C<0)
		return -2; /*out of bounds*/

	return slot_matrix[L][C].p;
}


/*
*	Description: allocates initializes priority queue of size of largest map
*
*	Arguments: pointer to PQ, size
*
*	Return: PQ
*
*/
minHeap* PQ_init(minHeap* PQ, int V)
{
	int i;
	PQ = (minHeap*)malloc(sizeof(minHeap));
	PQ->idx_vect=(int*)malloc(V*sizeof(int));
	PQ->minHeap_array = (coord**) malloc(V*sizeof(coord*));
	for(i=0; i<V;i++){
		PQ->minHeap_array[i] = (coord*) malloc(sizeof(coord));
	}
	PQ->size=V;

	return PQ;
}


/*
*	Description: restarts priority queue for every map
*
*	Arguments: (pointers to) priority queue and to map info
*
*	Return:
*
*/
minHeap* PQ_restart(lab_info* lab, minHeap* PQ)
{
	int i, j, k=0;
	int size_of_new;

	size_of_new = (lab->L)*(lab->C);
	PQ->size=size_of_new;

	for(i=0; i<lab->L; i++){
		for(j=0; j<lab->C; j++){
			PQ->minHeap_array[k]->l=i;
			PQ->minHeap_array[k]->c=j;
			PQ->idx_vect[i*C_aux+j]=k;
			k++;
		}
	}

	return PQ;
}


/*
*	Description: receber coordenada que recebeu atualização (menor custo) e reordena heap
*
*	Arguments: pointer to PQ, matrix, coordinates
*
*	Return: PQ
*
*/
minHeap* PQ_update(minHeap* PQ, slot** slot_matrix, int l, int c) 
{
	int i=PQ->idx_vect[l*C_aux+c];
	
	if((PQ->minHeap_array[i]->l==l) && (PQ->minHeap_array[i]->c==c)){	
		PQ = fixup(i, PQ, slot_matrix);
	}

	return PQ;
}

/*
*	Description: pop of less cost (highest priority) element at top of heap. Switch node with last and fixdown
*
*	Arguments: pointer to PQ, matrix, coordinates of top element
*
*	Return:
*
*/
coord* PQ_pop(minHeap* PQ, slot** slot_matrix, coord* top)
{	
	top->l=PQ->minHeap_array[0]->l;
	top->c=PQ->minHeap_array[0]->c;
	
	exch(0, PQ->size-1, PQ);
	PQ->size--;
	PQ=fixdown(PQ, slot_matrix, 0);	
	
	return top;
}


/*
*	Description: fixes heap after element priority is decreased (pop): recursively swaps element with child while child priority is higher 
*
*	Arguments: *PQ, matrix, position in PQ of element to fix (parent)
*
*	Return: PQ
*
*/
minHeap* fixdown(minHeap* PQ, slot** slot_matrix, int parent)
{	
	int left = 2*parent+1;
    int right = 2*parent+2;
	int min;

	if (PQ->size>1)
  	{
		if ((left >= PQ->size) ||  left < 0){
      		left = -1;

			}
    	if ((right >= PQ->size) || right < 0){
      		right = -1;
			
			}

    	if (left != -1  &&  less_pri(left, parent, PQ, slot_matrix)==0){
			min=left;
		
		}
		else{
			min = parent;
			
		}
		if (right != -1  &&  less_pri(right, min, PQ, slot_matrix)==0)
      		min=right;

		if(min!=parent){
			
			exch(parent, min, PQ);
      		PQ=fixdown(PQ, slot_matrix, min);
    	}
  	}
	
	return PQ;
}


/*
*	Description: fixes heap after element priority is increased (update): recursively swaps element with parent while parent priority is lower or becomes node 
*
*
*	Arguments: *PQ, matrix, position in PQ of element to fix 
*
*	Return:
*
*/
minHeap* fixup(int idx, minHeap* PQ, slot** slot_matrix)
{
	int parent=(idx-1)/2;

	if(less_pri(parent, idx, PQ, slot_matrix)==1){
		
		PQ = exch(parent, idx, PQ);
		
		PQ = fixup(parent, PQ, slot_matrix);
	}
	
	return PQ;
}


/*
*	Description: checks if cell is in PQ
*
*	Arguments: cell coordinates
*
*	Return: 1 if yes, 0 if not
*
*/
int PQ_find(minHeap* PQ, int l, int c) 
{
	int i=PQ->idx_vect[l*C_aux+c];

	if(PQ->minHeap_array[i]->l==l && PQ->minHeap_array[i]->c==c)
		return 1;


	return 0;
}


/*
*	Description: compares the costs of two elements a, b (if k(a)>k(b))
*
*	Arguments: indexes of elements a, b
*
*	Return: 1 if yes (k(a)>k(b)), 0 if not
*
*/
int less_pri(int a, int b, minHeap* PQ, slot** slot_matrix)
{	
	if(slot_matrix[PQ->minHeap_array[a]->l][PQ->minHeap_array[a]->c].w
		> slot_matrix[PQ->minHeap_array[b]->l][PQ->minHeap_array[b]->c].w)
		return 1;
	else
		return 0;
}


/*
*	Description: swaps two elements of heap (PQ) and respective indexes in mapping vector
*
*	Arguments: indexes of a, b
*
*	Return: PQ
*
*/
minHeap* exch(int a, int b, minHeap* PQ)
{	
	coord *aux;

	PQ->idx_vect[PQ->minHeap_array[a]->l * C_aux + PQ->minHeap_array[a]->c]=b;
	PQ->idx_vect[PQ->minHeap_array[b]->l * C_aux + PQ->minHeap_array[b]->c]=a;
	
	aux=PQ->minHeap_array[a];
	PQ->minHeap_array[a]=PQ->minHeap_array[b];
	PQ->minHeap_array[b]=aux;

	return PQ;
}


/*
*	Description: frees allocated memory of PQ
*
*	Arguments: PQ, size 
*
*	Return: void
*
*/
void free_PQ(minHeap *PQ, int V)
{
	int i;
	for(i=0; i<V; i++){
		free(PQ->minHeap_array[i]);
	}
	free(PQ->minHeap_array);
	free(PQ->idx_vect);
	free(PQ);
}


/*
*	Description: checks if map is valid duh
*
*	Arguments: map information
*
*	Return: 1 if yes 0 if no
*
*/
int isMapValid(int l,int c,int l1,int c1,int p){

	if((l>0)&&(c>0)&&(l1==1)&&(c1==1)&&(p>=0)){
		/* situação específica de source = target*/
		return 2;
	}
	if((l>0)&&(c>0)&&(l1>0)&&(l1<=l)&&(c1>0)&&(c1<=c)&&(p>=0)){
		return 1;
	}else{
		
		return 0;
	}
	return 0;
}
