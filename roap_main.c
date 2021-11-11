#include "roap_lib.h"

/*
    
*/

int main(int argc, char**argv){
    
    FILE* fptr_in=NULL;
    FILE* fptr_out=NULL;
    
    char* nome_file_out=NULL;
    int fase_flag;
    int C_max;
    int L_max;

    /*vars inter*/
    lab_info* head= NULL;
    Lab* new_lab = NULL;
    int** mat=NULL;
    int* respostas=NULL;
    vect_insert_pos=0;

    /*vars final*/
    int P_max;
    int V;
    minHeap* PQ=NULL;


    fase_flag = check_args(argc, argv);
    /*flag 1-> inter, flag 2-> final*/

    if(fase_flag==1){
        nome_file_out = check_extension (nome_file_out, argv[2], fase_flag);
        fptr_in = open_file_in(argv[2]);
        /*  
            main inter
                ->    
                *(solver: falta A6)*  
        */
        fptr_in = maior_mapa (fptr_in, &L_max, &C_max, &P_max, fase_flag); 
        respostas = vect_alloc (respostas, N_mapas);
	    mat = mat_alloc (mat, L_max+2, C_max+2);

        respostas = Data_Process(respostas, new_lab, fptr_in, mat);
        vect_to_File(respostas, nome_file_out); 

        fclose(fptr_in);
        free_mat(mat, L_max);
        free(respostas);
    }


    if(fase_flag==2){
        nome_file_out = check_extension (nome_file_out, argv[1], fase_flag);
        fptr_in = open_file_in(argv[1]);
        fptr_out = open_file_out(nome_file_out);
        /*  
            main final
                ->      
        */
        fptr_in = maior_mapa (fptr_in, &L_max, &C_max, &P_max, fase_flag);
        V=(C_max)*(L_max);   
        /*printf("V: %d\n", V); fflush(stdout);*/
        PQ=PQ_init(PQ, V);

        Data_Process_final(fptr_in, fptr_out, PQ);

        free_PQ(PQ, V);
        /*free head;*/
        
    }
    free(nome_file_out);
    fclose(fptr_in);
    fclose(fptr_out);

    exit(0);
}