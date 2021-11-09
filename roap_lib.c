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
		printf("exit\n"); fflush(stdout);
		exit(0);
	}
	return fp;
}

FILE* open_file_out (char* filename){
    
    FILE *fp;

	fp = fopen(filename, "w");
	if (fp == NULL)
		exit(0);

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
	/*chato, eu sei, só por causa do A*/
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


void write_to_file(char* nome_file_out){

	FILE* fpOut;
	fpOut= fopen(nome_file_out,"w");

	fprintf(fpOut,"TEST");

	fclose(fpOut);

}


lab_info* Data_Process_final(FILE* fptr, parede** walls, lab_info* head){

    
    int lin, col, val;
    int i_P;
    int a, L_aux, /*C_aux,*/ L1_aux, C1_aux, P_aux;
	parede* new_wall;
	lab_info* new;
	int idx;

	/*para teste*/
	int custo;
	
	/*int (*hash_key_ptr)(int, int, int, int);
	hash_key_ptr=&hash_key;*/

    while (((a=fscanf(fptr, "%d %d %d %d %d", 
                &L_aux, &C_aux, &L1_aux, &C1_aux,&P_aux)) == 5)){

		new = malloc(sizeof(lab_info));
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
                if((fscanf(fptr, "%*d %*d %*d"))==0)
                    i_P++;
            }  
            i_P=0;
        }

        else{
            //mapa válido 
            while (i_P<P_aux){
                if(fscanf(fptr,"%d %d %d", &lin, &col, &val)==3){
                    if(((lin>=0)&&(lin<=L_aux)&&(col>=0)&&(col<=C_aux)) && ((val>0) || (val=-1))){
						new_wall=struct_wall_init(new_wall, lin, col, val);
						idx = hash_key(lin, col, C_aux);
                        walls = hash_insert(walls, new_wall, idx);
                    }
                    i_P++;                    
                }
            }  
            i_P=0;
	    }
		/*hash_print(walls);*/
		printf("\n L %d C %d P %d \n ", new->L, new->C,new->P);
		printf("\n l %d c %d \n", lin,col);
		custo=get_weight(walls, lin, col, new);
		printf("custo: %d\n\n", custo);

		/*dijsktra(walls, new);*/
		/* insere resolvido na lista */ 

		walls=hash_clear(walls);
    }
    return head;
}



parede** walls_vect_init(parede** vect, int P_max)
{	
	/*aloca com tamnaho P do maior mapa pela mesma razão do intermédio 
	e porque todas as outras hash beneficiam, quanto mais pequeno for o seu mapa*/

	/*continua-se a considerar o fator de compensação (80%, a ajustar) para o maior mapa*/
	hash_size=P_max/0.8; 
	vect = (parede**) malloc(hash_size*sizeof(parede*));
	hash_clear(vect);

	return vect;
}

parede** hash_clear(parede** vect)
{
	int i;

	for(i=0; i<hash_size; i++){
		vect[i]=NULL;
	}
	return vect;
}

parede** hash_insert(parede** vect, parede* p, int idx)
{

	/*se o slot dado por key(idx) estiver vazio, inserir*/
	if(vect[idx]==NULL){
		vect[idx]=p;
	}
		

	else{
		/*se nao, procura linear, de salto 1*/
		while(vect[idx]!=NULL){
			if(vect[idx]==NULL)
				vect[idx]=p;	

			idx++;
			if (idx>=hash_size)
				/*dar a volta*/
				idx=0;
		}
	}
	return vect;
}


int hash_get(parede** vect, int idx, int L, int C)
{
	if (vect[idx]==NULL)
		return 0;

	if((vect[idx]->L==L) && (vect[idx]->C==C))
		return vect[idx]->custo;

	else{
		/*se nao, procura linear, de salto 1*/
		while((vect[idx]==NULL) || (vect[idx]->L!=L) || (vect[idx]->C!=C)){	
			if (vect[idx]==NULL)
				return 0;
			
			if((vect[idx]->L==L) && (vect[idx]->C==C))
				return vect[idx]->custo;
			idx++;
			if (idx>=hash_size)
				/*dar a volta*/
				idx=0;
		}
		return vect[idx]->custo;
	}
	return 0;
}



int hash_key(int L, int C, int C_dim)
{
	int key, idx;

	key=L*C_dim+C;
	idx=key%hash_size;

	return idx;
}


int get_weight (parede** walls, int L, int C, lab_info* lab)
{
	if(L>lab->L || C>lab->C || L<1 || C<1)
		return -2; /*out of bounds*/

	int idx;

	idx=hash_key(L, C, C_aux);

	return hash_get(walls, idx, L, C);
}



parede* struct_wall_init(parede* new_wall, int l, int c, int val)
{
	new_wall= (parede*) malloc(sizeof(parede));

	new_wall->L=l;
	new_wall->C=c;
	new_wall->custo=val;

	return new_wall;
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

coord* PQ_pop(minHeap* PQ)
{
	PQ->minHeap_array[0]=NULL;
	PQ->size--;
	/*PQ_resort();*/
}

coord* PQ_find(int l, int c,minHeap* PQ) /*recebe coordenada e vê se está no PQ*/
{

}


minHeap* PQ_update(minHeap* PQ, slot** slot_matrix, int l, int c) /*receber coordenada que recebeu atualização (menor custo) e reordena heap*/
{
	int i;
	int a; 

	for(i=0; i<PQ->size;i++){
		if((l==PQ->minHeap_array[i]->l) && (c==PQ->minHeap_array[i]->c)){	
			while((a=less_pri(i, (i-1)/2,PQ,slot_matrix)) == 1)
			{
				PQ = exch(i, (i-1)/2, PQ);
				PQ = fixup(i, PQ, slot_matrix);
				i=(i-1)/2;
			}
			break;
		} 
	}

	return PQ;
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

	return PQ;
}

minHeap* fixup(int idx, minHeap* PQ, slot** slot_matrix)
{
	while(idx>0 && less_pri((idx-1)/2, idx, PQ, slot_matrix)==1){
		exch(idx, (idx-1)/2, PQ);
		idx=(idx-1)/2;
	}

	return PQ;
}

