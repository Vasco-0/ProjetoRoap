#include "roap_lib.h"

/*
    
*/

int main(int argc, char**argv){
    
    FILE* fptr;
    nome_file_out = NULL;
    int fase_flag;

    /*vars inter*/
    lab_info* head= NULL;
    Lab* new_lab = NULL;
    int** mat=NULL;
    int* respostas=NULL;
    vect_insert_pos=0;

    /*vars final*/
    int P_max=0;


    fase_flag = check_args(argc, argv);
    /*flag 1-> inter, flag 2-> final*/

    if(fase_flag==1){
        check_extension (argv[2], fase_flag);
        fptr = open_file_in(argv[2]);
        /*  
            main inter
                ->    
                *(solver: falta A6)*  
        */
        fptr = maior_mapa (fptr); 
        respostas = vect_alloc (respostas, N_mapas);
	    mat = mat_alloc (mat, L_max+2, C_max+2);

        respostas = Data_Process(respostas, new_lab, fptr, mat);
        vect_to_File(respostas, nome_file_out); 

        fclose(fptr);
        free_mat(mat, L_max);
        free(respostas);
        free (nome_file_out);
    }


    if(fase_flag==2){
        check_extension (argv[1], fase_flag);
        fptr = open_file_in(argv[1]);
        /*  
            main final
                ->      
        */
        fptr = maior_P (fptr, &P_max);             
        walls=walls_vect_init(walls, P_max);
                printf("hash size: %d\n", hash_size);

        head = Data_Process_final(fptr, walls,head);

        /*
        free_walls(walls, hash_size);
        free_PQ();
        free(st);
        free(wt);
        */
    }

    /*write_to_file(nome_file_out);*/

    exit(0);
}