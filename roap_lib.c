/*
	Library for auxilary functions

	->open_file
	->check_args 
	->check_extension

*/
#include "roap_lib.h"

//
FILE* open_file(char** argv,int flag){
    
    FILE *fp;

	if(flag==2){
		fp = fopen(argv[1], "r");
		if (fp == NULL){
        	//printf("\n fatal error: file not found \n");
			exit(0);
		}
	}

	if(flag==1){
		fp = fopen(argv[2], "r");
		if (fp == NULL){
        	//printf("\n fatal error: file not found \n");
			exit(0);
		}
	}
	return fp;
}

//
int check_args(int argc, char**argv){ 
	int flag;

	if((argc<2)||(argc>=4)){
        //printf("\n fatal error:  arguments error ");
        exit(0);
    }

    if(strcmp("-s", argv[1]) == 0){
        flag=1;
    }else{
		flag=2;
	}
	
	return flag;
}

//
char* check_entension(char** argv, int fase_flag){
	char* output_file; // Q: make proper alloc?
	char* input_file;
	char* check_in1;
	char ext_out[]= ".sol";
	char ext_out1[] = ".sol1";

	if(fase_flag==1){

		input_file=(char*)malloc(strlen(argv[2])+1);

		input_file = strtok(argv[2], ".");
		check_in1 = strtok(NULL, ".");

		if(strcmp(check_in1,"in1")!=0){
        //printf("\n fatal error: input file is not .in1 \n");
        exit(0);
		}
		if (input_file == NULL) {
        //printf("\n fatal error: could not open file \n");
		exit(0);
    	}

		output_file =  input_file;
    	strcat(output_file,ext_out1);
	}

	if(fase_flag==2){

		input_file=(char*)malloc(strlen(argv[1])+1);

		input_file = strtok(argv[1], ".");
		check_in1 = strtok(NULL, ".");

		if(strcmp(check_in1,"in")!=0){
        //printf("\n fatal error: input file is not .in \n");
        exit(0);
		}
		if (input_file == NULL) {
        //printf("\n fatal error: could not open file \n");
		exit(0);
    	}

		output_file =  input_file;
    	strcat(output_file,ext_out);
	}

	return output_file;
}

void write_to_file(char* nome_file_out){

	FILE* fpOut;
	fpOut= fopen(nome_file_out,"w");

	fprintf(fpOut,"TEST");

	fclose(fpOut);
	//free(fpOut);
}