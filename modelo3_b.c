#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ARTICULO {
	int NUMART ;
	char DESCRIP[20];
	int STOCK ;
	char PROVE[15] ;
	float COSTO ;
};

int main()
{
	FILE * FP, * FPAUX;
	struct ARTICULO X;
	int TAM_ARCH ;
	char CAR, articulo[20] ;

	if ( (FP = fopen("BDPEREZ", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo \n\n");	
		exit(1);
	}; 
	
	if ( (FPAUX = fopen ("BDAUX","wb")) == NULL ) {
		printf("\n\n ERROR APERTURA DE ARCHIVO \n\n") ;
		exit(1);			
	};
		

		
	fread ( &X, sizeof(X), 1, FP ); // leo primer index
	while ( ! feof(FP) ){
		if (strcmp(X.PROVE, "PEREZ") == 0) {
			strcpy(articulo, X.DESCRIP);			
			fwrite ( &X , sizeof(X) , 1 , FPAUX );	
		}

		
		fread ( &X, sizeof(X), 1, FP ); // leo segundo index
	}
	fclose(FP);
	
	if ( (FP = fopen("BDPEREZ", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo \n\n");	
		exit(1);
	}; 
	
	fread ( &X, sizeof(X), 1, FP ); // leo primer index
	while ( ! feof(FP) ){
		if (strcmp(X.DESCRIP, articulo) != 0) {
		
			fwrite ( &X , sizeof(X) , 1 , FPAUX );	
		}
		fread ( &X, sizeof(X), 1, FP ); 
	}
		
	fclose(FP);
	fclose(FPAUX);
	
	remove ("BDPEREZ");
	rename ("BDAUX","BDPEREZ");
	

	
	printf("\n\n");
///////////////////////////////  tama?o archivo ////////////////////////////////////

	if ( (FP = fopen("BDPEREZ", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo \n\n");	
		exit(1);
	}; 	
	
	fseek(FP, sizeof(X)-1, SEEK_END);
	TAM_ARCH = ftell(FP)/sizeof(X);
	

	fclose(FP);
	
	printf ("\n\n\t\t CANTIDAD DE REGISTROS = %d" , TAM_ARCH);
	
	return 0;
}
