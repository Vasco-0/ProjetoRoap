#include "roap_lib.h"

int main(int argc, char**argv){
    
    FILE* fptr;
    char* file_out = (char*)malloc(100);
    int fase_flag = check_args(argc,argv);

    //printf("flag is %d\n",fase_flag);

    fptr = open_file(argv,fase_flag);

    //if(fptr != NULL)
        //printf("file pointer check\n");

    strcpy(file_out,check_entension(argv,fase_flag));

    //printf("file out: %s",file_out);

    write_to_file(file_out);
    

    exit(0);
}