#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PAISES {
	int CODIGO;
	char PAIS[20];
};

struct VENTAS {
	int STOCK;
	char APELLIDO[20];
	int CODIGO;
};

int main ()
{

	FILE * FP, * FV;
	struct PAISES P;
	struct VENTAS V;
	int I, CANTIDAD = 0, FLAG = 0, CONTADOR = 1;
	char PAISAUX[20];

	if ( (FP = fopen("PAISES", "w+b")) == NULL ) {
		printf("\n\n Error apertura de archivo PAISES \n\n");
		exit(1);
	};

	if ( (FV = fopen("VENTAS", "w+b")) == NULL ) {
		printf("\n\n Error apertura de archivo VENTAS \n\n");
		exit(1);
	};

	while ( CANTIDAD != -1 ){
		// INGRESO DE DATOS
		fflush(stdin);
		printf("\n\n\t UNIDADES VENDIDAS: ");
		scanf("%d", &(V.STOCK));
		CANTIDAD = V.STOCK;
		if (CANTIDAD != -1)	{
			fflush(stdin);
			printf("\n\n\t VENDEDOR: ");
			gets(V.APELLIDO);
			if ( FLAG == 0 ){
                printf("\n\n\t PAIS: ");
				fflush(stdin);
				gets(PAISAUX);

				// COMPARACION DE PAISES
				fseek(FP, 0L, SEEK_SET); // rewind(FP)
				fread(&P, sizeof(P), 1, FP);
				while(!feof(FP)){
					if (strcmp(PAISAUX, P.PAIS) == 0) {
						FLAG = 1;
						V.CODIGO = P.CODIGO;
					}
					fread(&P, sizeof(P), 1, FP);
				}

				// ESCRITURA DE NUEVO PAIS SI NO ESTA

				if (FLAG == 0) {
                    fseek(FP, 0L, SEEK_END); // rewind(FP)
					strcpy(P.PAIS, PAISAUX);
					P.CODIGO = CONTADOR++;
					V.CODIGO = P.CODIGO;
                    fwrite(&P, sizeof(P), 1, FP);
				}
				// Escritura archivo VENTAS
				fseek(FV, 0L, SEEK_END);
				fwrite(&V, sizeof(V), 1, FV);

			}
		}
	}


	fclose(FP);
	fclose(FV);
	
// LECTURAAAAAAAA
	if ( (FP = fopen("PAISES", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo PAISES \n\n");	
		exit(1);
	}; 
	
	if ( (FV = fopen("VENTAS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo VENTAS \n\n");	
		exit(1);
	}; 
	
	printf("\n\n\t %-20s %10s %10s", "CODIGO", "PAIS");
	fread ( &P, sizeof(P), 1, FP );
	while ( ! feof(FP) ){
		printf("\n\n\t %-20d %10s", P.CODIGO, P.PAIS);
			
		fread ( &P, sizeof(P), 1, FP );
	}
	
	printf("\n\n\n");
		
	printf("\n\n\t %-20s %10s %10s", "STOCK", "VENDEDOR", "CODIGO");
	fread ( &V, sizeof(V), 1, FV );
	while ( ! feof(FV) ){
		printf("\n\n\t %-20d %10s %10d", V.STOCK, V.APELLIDO, V.CODIGO);
			
		fread ( &V, sizeof(V), 1, FV );
	}	
		
	fclose(FP);
	fclose(FV);		
	
	
	return 0;
}
