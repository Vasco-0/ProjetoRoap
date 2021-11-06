/*
    nota: agora cada função vai ter 3 estados

    ----Não Mexer - Nome ----       (quando a função estiver terminada e funcional) se quisermos alterar algo primeiro falar com o outro
    ----Em progresso - Nome ---     (não funcional mas a trabalhar nela) tmb é para não mexer
    ----Livre-----                  (trabalho por fazer não reclamado) 

    NOTA extra: código só vai para o git se não houver seg faults !!

    Nota extra extra: no main se mexer não é para mexer em funções que sejam NM ou EP do outro.

*/
#include "roap_lib.h"

/*-----------------Não mexer - Vasco ----------------*/
FILE* open_file(char** argv,int flag){

    FILE *fp = NULL;

	if(flag==2){
		fp = fopen(argv[1], "r");
		if (fp == NULL){
        	/*printf("\n fatal error: file not found \n");*/
			exit(0);
		}
	}

	if(flag==1){
		fp = fopen(argv[2], "r");
		if (fp == NULL){
        	/*printf("\n fatal error: file not found \n");*/
			exit(0);
		}
	}
	return fp;
}

/*-------------------------------------------------Não mexer - Vasco --------------------*/
int check_args(int argc, char**argv){ 

	int flag;

	if((argc<2)||(argc>=4)){
        /*printf("\n fatal error:  arguments error ");*/
        exit(0);
    }

    if(strcmp("-s", argv[1]) == 0){
        flag=1;
    }else{
		flag=2;
	}
	
	return flag;
}

/*------------------------------------------Não mexer - Vasco ---------------------*/
char* check_extension(char** argv, int fase_flag){

	char* output_file = NULL; 
	char* input_file = NULL;
	char* check_in1 = NULL;
	char ext_out[]= ".sol";
	char ext_out1[] = ".sol1";

	if(fase_flag==1){

		input_file=(char*)malloc(strlen(argv[2])+1);
		output_file=(char*)malloc(strlen(argv[2])+1);
		check_in1=(char*)malloc(4);

		input_file = strtok(argv[2], ".");
		check_in1 = strtok(NULL, ".");

		if(strcmp(check_in1,"in1")!=0){
        /*printf("\n fatal error: input file is not .in1 \n");*/
        exit(0);
		}

		if (input_file == NULL) {
        /*printf("\n fatal error: could not open file \n");*/
		exit(0);
    	}

		strcpy(output_file,input_file);
    	strcat(output_file,ext_out1);
	}

	if(fase_flag==2){

		input_file=(char*)malloc(strlen(argv[1])+1);
		output_file=(char*)malloc(strlen(argv[1])+1);
		check_in1=(char*)malloc(4);
		
		input_file = strtok(argv[1], ".");
		check_in1 = strtok(NULL, ".");

		if(strcmp(check_in1,"in")!=0){
        	/*printf("\n fatal error: input file is not .in \n");*/
        	exit(0);
		}

		if (input_file == NULL) {
        /*printf("\n fatal error: could not open file \n");*/
		exit(0);
    	}

		strcpy(output_file,input_file);
    	strcat(output_file,ext_out);
	}
	return output_file;
}

/*---------------Livre-----------*/
void write_to_file(char* nome_file_out){

	FILE* fpOut = NULL;
	fpOut= fopen(nome_file_out,"w");

	fprintf(fpOut,"TEST");

	fclose(fpOut);
	/*free(fpOut);*/
}

/*-------------Livre ---------------*/
void conceptual_matrix_printer(parede** wall, lab_info* lab){
/* for debug purposes only - Not working*/

	int i,j;

	for(i=1;i<lab->L;i++){
		for(j=1;j<lab->C;j++){
			printf("%d",get_weight(i,j,lab,wall));
		}
		printf("\n");
	}

}

/*----------------Não mexer - Vasco ----------*/
int is_lab_valid(lab_info* new){

	if(new->L<1 || new->C<1 || new->P<0)
	/* invalid map */
		return -1;
	
	if(new->L_target<1 || new->C_target <1 || new->L_target > new->L || new->C_target> new->C)
	/* target is out of bounds */
		return 1;
	
	return 0;
}

/*--------------Em progresso-Vasco------------------*/
int get_weight(int l, int c, lab_info* lab, parede** wall){
	/* if branca returns 0
	   if cinza returns val
	   if preta returns -1 
	   if out of bounds returns -3
	   */
	int b=wall[2]->c;

	if(l>lab->L || c>lab->C || l<1 || c<1)
		return -3;

	/*for(int i=0;i<(lab->P);i++){  <- seg fault in here 
		if((wall[i]->l == l) && (wall[i]->c == c)){

				return wall[i]->val;
		}
		if (wall[i]->c>c)
			return 0;
		if (wall[i]->l>l)
			return 0;	
	}*/
	return 0;
}


/*Livre*/
lab_info* read_file(FILE* fptr, lab_info* head){

	lab_info* new = NULL;
	parede** wall_vector = NULL;
	int id = 0;
	int a, l_aux,c_aux,lt_aux,ct_aux,p_aux,b;

	while((a=fscanf(fptr," %d %d %d %d %d", &l_aux,&c_aux,&lt_aux,&ct_aux,&p_aux)==5)){
		
		id ++;
		new = malloc(sizeof(lab_info));
		new->id=id;
		new->L=l_aux;
		new->C=c_aux;
		new->L_target=lt_aux;
		new->C_target=ct_aux;
		new->P=p_aux;

		if((b=is_lab_valid(new))==-1) /* invalid map */
		{
			new->B = -2; /*prob -1*/
		}
		if(b==1) /* out of bounds */
		{
			new->B = -1;
		}
		if (b==0)
		{
			wall_vector=init_wall_vect(wall_vector,new);
			//print_wall_vector(wall_vector,new);

			/*for(int j=1;j>=new->P;j++)
			{
				int lp,cp,vp,c;
				if ((c= fscanf(fptr,"%d %d %d",&lp,&cp,&vp))==3){

					if(is_wall_valid(lp,cp,vp)==0)
					{
						wall_vector[lp]=insert_col(lp,cp,vp,wall_vector,new);
					}
				}

			}*/

		}
	}
	printf("alive");
	return new;

}

/*----------------------------Não Mexer - Vasco--------------------*/
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

/*-----------------Não Mexer- Vasco------------------*/
void print_wall_vector(parede** wall_vect,lab_info* lab){

	for(int i=1;i<lab->L;i++){
		while(1)
		{
			printf(" L: %d",i);
			printf(" C: %d ",wall_vect[i]->c);
			printf(" VAL: %d ",wall_vect[i]->val);
			if(wall_vect[i]->next==NULL)
				break;
		}
		
	}

}

/*Em progresso - Vasco - nota: enquanto o read file não está pronto posso ir testando o algoritmo*/
lab_info* read_file_beta(lab_info* lab){

	lab = malloc(sizeof(lab_info));
		lab->L=8;
		lab->C=6;
		lab->L_target=5;
		lab->C_target=4;
		lab->P=8;

	 parede** wall=(parede**)malloc(sizeof(parede*)* (lab->P + 1));
	
	 	wall[1]->c=1;
	 	wall[1]->val=308;
	 	
	 	wall[2]->c=4;
	 	wall[2]->val=10;

	 	wall[3]->c=6;
	 	wall[3]->val=7;

	 	/*wall[1]->l;
	 	wall[1]->c;
	 	wall[1]->val;

		wall[1]->l;
	 	wall[1]->c;
	 	wall[1]->val;

	 	wall[1]->l;
	 	wall[1]->c;
	 	wall[1]->val;

	 	wall[1]->l;
	 	wall[1]->c;
	 	wall[1]->val;

	 	wall[1]->l;
	 	wall[1]->c;
	 	wall[1]->val;*/

		printf("%d\n",get_weight(3,4,lab,wall));

		/*conceptual_matrix_printer(wall,lab); */ 

		/*solve(lab,wall);*/
		return lab;
}