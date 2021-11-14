/*
	Solver for "Fase intermédia"
	->
*/

#include "roap_lib.h"


int* Data_Process(int* respostas, Lab* new_lab, FILE* fptr, int** mat){

    
    int lin, col, val;
    int L2_aux = 0, C2_aux = 0;
    int i_P;

    int a, L_aux, C_aux, L1_aux, C1_aux, var_aux, P_aux;
    char A_var;
    int resposta=0;


    new_lab = (Lab*) malloc(sizeof(Lab));

    while (((a=fscanf(fptr, "%d %d %d %d %c%d", 
                &L_aux, &C_aux, &L1_aux, &C1_aux, &A_var, &var_aux)) == 6) 
                && (A_var=='A')){

        if(var_aux==6){
            a=fscanf(fptr,"%d %d",&L2_aux,&C2_aux);
            L2_aux=L2_aux-1;
            C2_aux=C2_aux-1;
        }

        a=fscanf(fptr,"%d",&P_aux);

        new_lab= struct_insert (new_lab, L_aux, C_aux, L1_aux, C1_aux, L2_aux, C2_aux, 
                                A_var, var_aux, P_aux);


        a=teste_valid_mapa(L_aux, C_aux, L1_aux, C1_aux, A_var, var_aux, L2_aux, C2_aux,P_aux);

        if(a!=0){
            /*situação mapa inválido*/
            if (a==-3)
                exit(0);

        
            if(a==-2){ 
                resposta = -2;
            }
            while (i_P<P_aux){
                if((fscanf(fptr, "%*d %*d %*d"))==0)
                    i_P++;
            }  
            i_P=0;
        }

        else{
             
            while (i_P<P_aux){
                if(fscanf(fptr,"%d %d %d", &lin, &col, &val)==3){
                    if((lin>=0)&&(lin<=L_aux)&&(col>=0)&&(col<=C_aux)){
                        mat[lin][col]=val;
                    }
                    i_P++;                    
                }
            }  
            i_P=0;

            resposta=solver(new_lab,mat);
	    }
        respostas = insere_resposta_vect (respostas, resposta);

    }
    return respostas;
}


/***********************************************************************/
int* insere_resposta_vect(int* vect, int resposta)
{
    vect[vect_insert_pos] = resposta;
    vect_insert_pos++;
    return vect;
}


/***********************************************************************/
/* l1 e c1 podem ser maiores que C e L e dá -2*/
int teste_valid_mapa(int L_aux,int C_aux, int L1_aux , int C1_aux, char A_var, int var_aux, int L2_aux, int C2_aux, int P_aux){ 

    if ((C_aux < 0) || (L_aux < 0))
        return -3;
    if ((L1_aux < 1) || (C1_aux < 1) || (L1_aux)>L_aux || (C1_aux)>C_aux) 
        return -2;
    if ((var_aux <1) || (var_aux >6) || (P_aux<0))
        return -1;

    if (var_aux==6){
        if((L2_aux<1)||(C2_aux<1))
            return-1;
    }
    
    return 0;
}




/***********************************************************************/
Lab* struct_insert (Lab* new_lab,
		int L_aux,int C_aux, int L1_aux , int C1_aux, int L2_aux , int C2_aux,
		char A_var, int var_aux, int P_aux)
{

    new_lab->L = L_aux;
    new_lab->C = C_aux;
    new_lab->L1 = L1_aux;
    new_lab->C1 = C1_aux;
    new_lab->variante = var_aux;
	new_lab->L2= L2_aux;
    new_lab->C2= C2_aux;
	new_lab->P = P_aux;

	return new_lab;
}


/***********************************************************************/
void vect_to_File(int* vect, char * nome_file_out)
{
	int i=0;
    FILE* point_file;

    point_file = open_file_out (nome_file_out);
	
    for(i=0; i<N_mapas; i++){
		fprintf (point_file,"%d \n\n", vect[i]);
	}

	fclose(point_file);
}

/***********************************************************************/


int solver(Lab* new_lab, int** mat){
    
    if(new_lab->variante==1)
        return solver_1(new_lab, mat);

    if(new_lab->variante==2)
        return solver_2(new_lab, mat);

    if(new_lab->variante==3)
        return solver_3(new_lab, mat);

    if(new_lab->variante==4)
        return solver_4(new_lab, mat);

    if(new_lab->variante==5)
        return solver_5(new_lab, mat);

    if(new_lab->variante==6)
        return solver_6(new_lab, mat);

    return 0;
}


/***********************************************************************/
int solver_1 (Lab* new_lab, int** mat)
{
    if ((new_lab->L1 > new_lab->L) || (new_lab->C1 > new_lab->C))
            return -2;
    if(mat[new_lab->L1][new_lab->C1]==0)
            return 0;
    if(mat[new_lab->L1][new_lab->C1]==-1)
            return -1;
    return mat[new_lab->L1][new_lab->C1];
}

/***********************************************************************/
int solver_2 (Lab* new_lab, int** mat)
{
    int vizinho1=-3;
    int vizinho2=-3;
    int vizinho3=-3;
    int vizinho4=-3;
    if ((new_lab->L1 > new_lab->L) || (new_lab->C1 > new_lab->C))
            return -2;
    if((new_lab->L1)+1 <= new_lab->L)
        vizinho1 = mat[(new_lab->L1)+1][new_lab->C1];
    if((new_lab->C1)+1 <= new_lab->C)
        vizinho2 = mat[(new_lab->L1)][(new_lab->C1)+1];
    if((new_lab->L1)-1 >= 1)
        vizinho3 = mat[(new_lab->L1)-1][(new_lab->C1)];
    if((new_lab->C1)-1 >= 1)
        vizinho4 = mat[(new_lab->L1)][(new_lab->C1)-1];
    if((vizinho1==0)||(vizinho2==0)||(vizinho3==0)||(vizinho4==0))
        return 1;
    return 0;
}

/***********************************************************************/
int solver_3 (Lab* new_lab, int** mat)
{
    int vizinho1=-3;
    int vizinho2=-3;
    int vizinho3=-3;
    int vizinho4=-3;

    if ((new_lab->L1 > new_lab->L) || (new_lab->C1 > new_lab->C))
        return -2;
        
    if((new_lab->L1)+1 <= new_lab->L){
        vizinho1 = mat[(new_lab->L1)+1][new_lab->C1];

        if ((vizinho1!=0) && (vizinho1!=-1))
            vizinho1=99;
    }
    if((new_lab->C1)+1 <= new_lab->C){

        vizinho2 = mat[(new_lab->L1)][(new_lab->C1)+1];

        if ((vizinho2!=0) && (vizinho2!=-1))
            vizinho2=99;
    }

    if((new_lab->L1)-1 >= 1){
            vizinho3 = mat[(new_lab->L1)-1][(new_lab->C1)];
         if ((vizinho3!=0) && (vizinho3!=-1))
            vizinho3=99;
    }

    if((new_lab->C1)-1 >= 1){

        vizinho4 = mat[(new_lab->L1)][(new_lab->C1)-1];
        if ((vizinho4!=0) && (vizinho4!=-1))
            vizinho4=99;
    } 

    if((vizinho1==99)||(vizinho2==99)||(vizinho3==99)||(vizinho4==99))
        return 1;
    return 0;
}

/***********************************************************************/
int solver_4 (Lab* new_lab, int** mat)
{
    int vizinho1=-3;
    int vizinho2=-3;
    int vizinho3=-3;
    int vizinho4=-3;

    if ((new_lab->L1 > new_lab->L) || (new_lab->C1 > new_lab->C))
        return -2;

    if((new_lab->L1)+1 <= new_lab->L)
        vizinho1 = mat[(new_lab->L1)+1][new_lab->C1];

    if((new_lab->C1)+1 <= new_lab->C)
        vizinho2 = mat[(new_lab->L1)][(new_lab->C1)+1];

    if((new_lab->L1)-1 >= 1)
        vizinho3 = mat[(new_lab->L1)-1][(new_lab->C1)];

    if((new_lab->C1)-1 >= 1)
        vizinho4 = mat[(new_lab->L1)][(new_lab->C1)-1];

    if((vizinho1==-1)||(vizinho2==-1)||(vizinho3==-1)||(vizinho4==-1))
        return 1;

    return 0;
}

/***********************************************************************/
int solver_5 (Lab* new_lab, int** mat)
{
    if ((new_lab->L1 > new_lab->L) || (new_lab->C1 > new_lab->C)) 
        return -2;
    if(mat[new_lab->L1][new_lab->C1]==0)
        return -1;
    if(mat[new_lab->L1][new_lab->C1]==-1)
        return -1;
        
    if(mat[new_lab->L1][new_lab->C1]>0){
        
        int vizinho1=-3;
        int vizinho2=-3;
        int vizinho3=-3;
        int vizinho4=-3;

        if((new_lab->L1)+1 <= new_lab->L)
            vizinho1 = mat[(new_lab->L1)+1][new_lab->C1];

        if((new_lab->C1)+1 <= new_lab->C)
            vizinho2 = mat[(new_lab->L1)][(new_lab->C1)+1];

        if((new_lab->L1)-1 >= 1)
            vizinho3 = mat[(new_lab->L1)-1][(new_lab->C1)];

        if((new_lab->C1)-1 >= 1)
            vizinho4 = mat[(new_lab->L1)][(new_lab->C1)-1];

        if((vizinho1==0)&&(vizinho3==0))
            return 1;

        if((vizinho2==0)&&(vizinho4==0))
            return 1;
    }
    return 0;
}

/***********************************************************************/
int solver_6 (Lab* new_lab, int** mat)
{
    return 0;
}

int** mat_alloc(int** mat, int L, int C)
{
	int i;

	/*inicializa a 0*/
	mat = (int**)calloc(L, sizeof(int*));
    for (i=0;i<L-1;i++){
        mat[i]=(int*)calloc(C, sizeof(int));
    }
	return mat;
}


/***********************************************************************/
int* vect_alloc(int* vect, int size)
{
	vect= (int*) malloc (size * sizeof (int));
	return vect;
}

void free_mat(int** mat, int L)
{
	int i;
	for(i=0;i<L-1;i++){  /*mas alloc L_MAX+2?*/
		free(mat[i]);
	}
	free(mat);
	/* rest in peace champ */
}