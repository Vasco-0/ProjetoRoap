#include "roap_lib.h"
/*
    nota: agora cada função vai ter 3 estados

    ----Não Mexer - Nome ----       (quando a função estiver terminada e funcional) se quisermos alterar algo primeiro falar com o outro
    ----Em progresso - Nome ---     (não funcional mas a trabalhar nela) tmb é para não mexer
    ----Livre-----                  (trabalho por fazer não reclamado) 

    NOTA extra: código só vai para o git se não houver seg faults !!

    Nota extra extra: no main se mexer não é para mexer em funções que sejam NM ou EP do outro.

*/

int main(int argc, char**argv){
    
    FILE* fptr;
    lab_info* head = NULL;
    char* file_out = NULL;

    int fase_flag = check_args(argc,argv);

    fptr = open_file(argv,fase_flag);

    if(fase_flag==1)
        file_out=(char*)malloc(strlen(argv[2])+1);

    if(fase_flag==2){

        file_out=(char*)malloc(strlen(argv[1])+1);
       
    }

    strcpy(file_out,(check_extension(argv,fase_flag)));

    //printf("read file door");
    //-> seg fault read_file(fptr,head);

    //read_file_beta(head);

    printf("\nOK\n");

    write_to_file(file_out);
    
    //free(fptr);
    exit(0);
}