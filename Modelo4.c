#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct INGRESO{
	int legajo;
	char carrera[20];
};

struct EXAMEN{
	int legajo;
	int nota;
};

int main()
{
	FILE * FI, * FE;
	struct INGRESO I;
	struct EXAMEN E;
	char carrera[20];
	int inscriptos = 0, presentes = 0, aprobados = 0;
	
	///////////////////////////////////////////// ESCRITURA DE DATOS //////////////////////////////
	if ( (FI = fopen("INGRESOS", "wb")) == NULL ) {
		printf("\n\n Error apertura de archivo INGRESOS \n\n");
		exit(1);
	};

	if ( (FE = fopen("EXAMEN", "wb")) == NULL ) {
		printf("\n\n Error apertura de archivo EXAMEN \n\n");
		exit(1);
	};

	// INGRESO DE DATOS "INGRESOS"

	// ALMUNO 1
	I.legajo = 26607;
	strcpy(I.carrera, "ARQUITECTURA");

    fwrite(&I, sizeof(I), 1, FI);

	// ALUMNO 2
	I.legajo = 27333;
	strcpy(I.carrera, "MEDICINA");

  	fwrite(&I, sizeof(I), 1, FI);

    // ALUMNO 3
	I.legajo = 28501;
	strcpy(I.carrera, "INFORMATICA");
    fwrite(&I, sizeof(I), 1, FI);
 
     // ALUMNO 4
	I.legajo = 29555;
	strcpy(I.carrera, "INFORMATICA");
    fwrite(&I, sizeof(I), 1, FI);   
    
    // ALUMNO 5
	I.legajo = 21555;
	strcpy(I.carrera, "INFORMATICA");
    fwrite(&I, sizeof(I), 1, FI);    
	
	// ALUMNO 6
	I.legajo = 39555;
	strcpy(I.carrera, "INFORMATICA");
    fwrite(&I, sizeof(I), 1, FI);   
    
    // ALUMNO 7
	I.legajo = 51555;
	strcpy(I.carrera, "INFORMATICA");
    fwrite(&I, sizeof(I), 1, FI);     
        
    
	// INGRESO DE DATOS "EXAMEN"    
	// ALMUNO 1
	E.legajo = 26607;
	E.nota = 9;

    fwrite(&E, sizeof(E), 1, FE);

	// ALUMNO 2
	E.legajo = 27333;
	E.nota = 5;

    fwrite(&E, sizeof(E), 1, FE);

    // ALUMNO 3
	E.legajo = 28501;
	E.nota = 7;
    fwrite(&E, sizeof(E), 1, FE);
    
    
    // ALUMNO 4
	E.legajo = 29555;
	E.nota = 2;
    fwrite(&E, sizeof(E), 1, FE);  
    
    // ALUMNO 5
	E.legajo = 21555;
	E.nota = 0;
    fwrite(&E, sizeof(E), 1, FE);    
        
  	fclose(FI);
	fclose(FE);  
	
///////////////////////////////////////////// INGRESO POR TECLADO //////////////////////////////
    printf("\nIngrese el nombre de la carrera buscada:");
    fflush(stdin);
    gets(carrera);
    
    //////////////////////////////////// ABRO LAS BASES DE DATOS PARA BUSCAR CUANTOS ALUMNOS TIENE LA CARRERA
	if ( (FI = fopen("INGRESOS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo INGRESO\n\n");	
		exit(1);
	}; 

	fread ( &I, sizeof(I), 1, FI );
	while ( ! feof(FI) ) {
		if (strcmpi(I.carrera, carrera) == 0) {
			inscriptos++;
		}	
		fread ( &I, sizeof(I), 1, FI );			
	}
	fclose(FI);
	printf("\n\nSe inscribieron: %d alumnos", inscriptos);
	
    /////////////////////////////// ABRO LAS BASES DE DATOS PARA BUSCAR CUANTOS SE PRESENTARON AL EXAMEN Y CUANTOS APROBARON
	if ( (FI = fopen("INGRESOS", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo INGRESO\n\n");	
		exit(1);
	}; 

    if ( (FE = fopen("EXAMEN", "rb")) == NULL ) {
		printf("\n\n Error apertura de archivo EXAMEN\n\n");	
		exit(1);
	}; 
	
	fread ( &I, sizeof(I), 1, FI );
	while ( ! feof(FI )) {
		if (strcmpi(I.carrera, carrera) == 0) {
			fread ( &E, sizeof(E), 1, FE );	
			while ( ! feof(FE )) {
				if (I.legajo == E.legajo ) {
					presentes++;
					if(E.nota >= 6) 
						aprobados++;
				}
					fread ( &E, sizeof(E), 1, FE );	
			}
		}
		fread ( &I, sizeof(I), 1, FI );	
		rewind(FE);		
	}
	
	printf("\n\nSe presentaron: %d alumnos", presentes);
	printf("\n\nAprobados: %d alumnos", aprobados);
	
	fclose(FI);
	fclose(FE);
		
	
	
	return 0;
}
