#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct venta {
	char vendedor[60];
	float monto;
	int codigoprovincia;
};

struct provincia {
	char nombre[40];
	int codigoprovincia;
};

int main (int argc, char **argv)
{
	FILE * FP, * FV, *FE;
	struct provincia p;
	struct venta v;
	char provaux[20];
	int contador = 1, buscado;
	

	///////////////////////////////////// ESCRITURA DE DATOS //////////////////////////////////////////////////
	if ( (FP = fopen("PROVINCIAS", "wb")) == NULL ) {
		printf("\n\n Error apertura de archivo PROVINCIAS \n\n");
		exit(1);
	};

	if ( (FV = fopen("VENTAS", "wb")) == NULL ) {
		printf("\n\n Error apertura de archivo VENTAS \n\n");
		exit(1);
	};

	// INGRESO DE DATOS
	// VENTA 1
	strcpy(v.vendedor, "CACHO");
	v.monto = 150.50;
	v.codigoprovincia = 1;

    fwrite(&v, sizeof(v), 1, FV);

	// VENTA 2
	strcpy(v.vendedor, "PEPE");
	v.monto = 120.40;
	v.codigoprovincia = 2;

    fwrite(&v, sizeof(v), 1, FV);

    // VENTA 3
	strcpy(v.vendedor, "MARITO");
	v.monto = 90.30;
	v.codigoprovincia = 3;

    fwrite(&v, sizeof(v), 1, FV);

    // VENTA 4
	strcpy(v.vendedor, "JOSE");
	v.monto = 70.20;
	v.codigoprovincia = 2;

    fwrite(&v, sizeof(v), 1, FV);

    // VENTA 5
	strcpy(v.vendedor, "LAUCHA");
	v.monto = 105.20;
	v.codigoprovincia = 3;

    fwrite(&v, sizeof(v), 1, FV);

    // VENTA 6
	strcpy(v.vendedor, "LUZ");
	v.monto = 180.50;
	v.codigoprovincia = 3;

    fwrite(&v, sizeof(v), 1, FV);


	strcpy(p.nombre, "TUCUMAN");
	p.codigoprovincia = 1;

    fwrite(&p, sizeof(p), 1, FP);

	strcpy(p.nombre, "SALTA");
	p.codigoprovincia = 2;

    fwrite(&p, sizeof(p), 1, FP);

	strcpy(p.nombre, "JUJUY");
	p.codigoprovincia = 3;
    fwrite(&p, sizeof(p), 1, FP);

	strcpy(p.nombre, "ENTRE RIOS");
	p.codigoprovincia = 4;

    fwrite(&p, sizeof(p), 1, FP);

	strcpy(p.nombre, "MISIONES");
	p.codigoprovincia = 5;

    fwrite(&p, sizeof(p), 1, FP);

	strcpy(p.nombre, "MENDOZA");
	p.codigoprovincia = 6;

    fwrite(&p, sizeof(p), 1, FP);


	fclose(FP);
	fclose(FV);

	///////////////////////////////////// LECTURA DE DATOS //////////////////////////////////////////////////

	if ( (FP = fopen("PROVINCIAS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo PROVINCIAS \n\n");	
		exit(1);
	}; 
	
	if ( (FV = fopen("VENTAS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo VENTAS \n\n");	
		exit(1);
	}; 
	
	printf("\n\n\t %-20s %10s %10s", "CODIGO", "PROVINCIA");
	fread ( &p, sizeof(p), 1, FP );
	while ( ! feof(FP) ){
		printf("\n\n\t %-20d %10s", p.codigoprovincia, p.nombre);
		fread ( &p, sizeof(p), 1, FP );
	}
	
	printf("\n\n\n");
		
	printf("\n\n\t %-20s %10s %10s", "VENDEDOR", "MONTO", "CODIGO");
	fread ( &v, sizeof(v), 1, FV );
	while ( ! feof(FV) ){
		printf("\n\n\t %-20s %10f %10d", v.vendedor, v.monto, v.codigoprovincia);
			
		fread ( &v, sizeof(v), 1, FV );
	}	
		
	fclose(FP);
	fclose(FV);	
	
	///////////////////////////////////// LECTURA DE VENTAS POR PROVINCIA  //////////////////////////////////////////////////	
	printf("\n\n\n");

	if ( (FP = fopen("PROVINCIAS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo PROVINCIAS \n\n");	
		exit(1);
	}; 
	
	if ( (FV = fopen("VENTAS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo VENTAS \n\n");	
		exit(1);
	}; 
	
	printf("\n\n\t %-20s %-10s", "PROVINCIA", "CANTIDAD DE VENTAS");
	fread ( &p, sizeof(p), 1, FP );
	while ( ! feof(FP) ){
		fread ( &v, sizeof(v), 1, FV );
		while ( ! feof(FV) ){
			if (p.codigoprovincia == v.codigoprovincia) {
				contador++;
			}

			fread ( &v, sizeof(v), 1, FV );
		}	
		printf("\n %-20s %10d", p.nombre, contador);
		contador = 0;
		rewind(FV);
		fread ( &p, sizeof(p), 1, FP );
		
	}
	
	fclose(FP);
	fclose(FV);	
	///////////////////////////////////// EXTRATO POR PROVINCIA  ////////////////////////////////
	

	if ( (FV = fopen("VENTAS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo VENTAS \n\n");	
		exit(1);
	}; 	
	
	if ( (FE = fopen("EXTRACTO.TXT", "w")) == NULL ) {
		printf("\n\n Error apertura de archivo PROVINCIAS \n\n");
		exit(1);
	};
	
	fread ( &v, sizeof(v), 1, FV );
	while ( ! feof(FV) ){
		if (v.codigoprovincia == atoi(argv[1]))  {
			fprintf(FE, "%.2f\n", v.monto);
		}
		fread ( &v, sizeof(v), 1, FV );
	}	
		
	
	fclose(FE);
	fclose(FV);	
	
	
	
	return 0;
}
