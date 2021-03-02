#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

//////////////////////////////////////////////////////////////////////////////

typedef struct entrada_ { //Ni idea de por qué se llama entrada_
		int ocupada; //Como un booleano
		char clave [LONGITUD_CLAVE]; //Esto son dos arrays de chars
		char sinonimos [LONGITUD_SINONIMOS];
	} entrada;

typedef struct item_{
		char clave [LONGITUD_CLAVE];
		char sinonimos [LONGITUD_SINONIMOS];
	} item;

	typedef int pos;
	typedef entrada *tabla_cerrada;

//////////////////////////////////////////////////////////////////////////////	

void inicializar_semilla() {
	srand(time(NULL));
}

//////////////////////////////////////////////////////////////////////////////

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

//////////////////////////////////////////////////////////////////////////////

int dispersionA(char *clave, int tamTabla) {//Equivalente a la funcion Hash();
	int i, valor = clave[0], n = MIN(8, strlen(clave));
	for (i = 1; i < n; i++)
		valor += clave[i];
	return valor % tamTabla;
}

int dispersionB(char *clave, int tamTabla) {
	int i, n = MIN(8, strlen(clave));
	unsigned int valor = clave[0];
	for (i = 1; i < n; i++)
		valor = (valor<<5) + clave[i]; 
		/* el desplazamiento de 5 bits equivale a */
	return valor % tamTabla;        /* multipicar por 32 */
}

//////////////////////////////////////////////////////////////////////////////

int leer_sinonimos(item datos[]) {
	char c;
	int i, j;
	FILE *archivo;
	if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
		printf("Error al abrir ’sinonimos.txt’\n");
		return(EXIT_FAILURE);
	}
	for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
		if ((c = fgetc(archivo)) != '\t') {
			printf("Error al leer el tabulador\n");
			return(EXIT_FAILURE);
		}
		for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
			if (j < LONGITUD_SINONIMOS - 1)
				datos[i].sinonimos[j] = c;
		}
		datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS -1)] = '\0';
	}
	if (fclose(archivo) != 0) {
		printf("Error al cerrar el fichero\n");
		return(EXIT_FAILURE);
	}
	return(i);
}

//////////////////////////////////////////////////////////////////////////////

int ndispersion(char *clave, int tamTabla) {
	if (strcmp(clave, "ANA")==0) return 7;
	if (strcmp(clave, "JOSE")==0) return 7;	
	if (strcmp(clave, "OLGA")==0) return 7;
	return 6;
}

//////////////////////////////////////////////////////////////////////////////

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
		int *colisiones, int (*dispersion)(char *, int),
		unsigned int (*resol_colision)(int pos_ini, int num_intento)){
	int aux_ini, posicion, i = 0;
	posicion = dispersion(clave,tam); aux_ini = posicion;
	while ((diccionario[posicion].clave != clave) && 
              (diccionario[posicion].ocupada != 0)) {
		i++;
		posicion = (resol_colision(aux_ini,i)) % tam;
	}				
	*colisiones = i;
	return posicion;
}

void inicializar_cerrada(tabla_cerrada *diccionario, int tam) {
	pos i;
	for (i = 0; i < tam; i++) {
		(*diccionario)[i].ocupada = 0;
	}
}

int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario,
		int tam, int (*dispersion)(char *, int), 
		unsigned int (*resol_colision)(int pos_ini, int num_intento)){
	int pos_insercion, colisiones = 0;
    	pos_insercion = buscar_cerrada(clave, *diccionario,
                    	tam, &colisiones, dispersion, resol_colision);
    	if ((*diccionario)[pos_insercion].ocupada != 1) {
        	strcpy((*diccionario)[pos_insercion].clave, clave);
        	strcpy((*diccionario)[pos_insercion].sinonimos, sinonimos);
		(*diccionario)[pos_insercion].ocupada = 1;
    	}
    	return colisiones;
}

void mostrar_cerrada(tabla_cerrada diccionario, int tam) {
	int j;
	printf(" {      \n");	
	for (j = 0; j < tam; j++) {
		printf("%3d- ", j);
		if (diccionario[j].ocupada) {
			printf(" (%s)", diccionario[j].clave);
		}
		printf("\n");
	}
  	printf("}     \n\n");
}

//////////////////////////////////////////////////////////////////////////////

unsigned int resolucionLineal(int i, int j) { 
	return (i + j);
}

unsigned int resolucionCuadratica(int i, int j) { 
	return (i + j*j);
}

unsigned int resolucionDoble (int i, int j) { 
	return (i + j * (10007 - i % 10007));
}

unsigned int resolucionDobleTest (int i, int j) { 
	return (i + j * (5 - i % 5));
}

//////////////////////////////////////////////////////////////////////////////

pos TestBuscar(char *clave, tabla_cerrada tabla, 
	int *colisions, int *col_aux, 
	unsigned int (*resol_colision)(int pos_ini, int num_intento)) {
	
	int aux_ini, posicion, i = 0;
	posicion = ndispersion(clave, 11);
	aux_ini = posicion;
    	while(strcmp(tabla[posicion].clave, clave) &&
	             tabla[posicion].ocupada) {
        	i++;
		(*colisions)++;
        	(*col_aux)++;
		posicion = (resol_colision(aux_ini,i)) % 11;        	
    	}
    	return posicion;
}

//////////////////////////////////////////////////////////////////////////////

void test(unsigned int (*resol_colision)(int pos_ini, int num_intento)) {
		tabla_cerrada tabla =  malloc (11 * sizeof(entrada));
	int i, posicion, colisiones = 0, col_aux[6];
	item elem;
	char *claves[7] = {"ANA","LUIS","JOSE","OLGA","ROSA","IVAN","CARLOS"};
	inicializar_cerrada(&tabla, 11);
	printf(" \n ");
	for (i = 0; i < 6; i++) {
		strcpy(elem.clave, claves[i]); 
		col_aux[i]= insertar_cerrada( elem.clave, elem.clave, 
			    &tabla, 11, ndispersion, resol_colision);
		colisiones = colisiones + col_aux[i];
    	}
    	if (resol_colision == resolucionLineal) {
    		printf("***TABLA CERRADA LINEAL\n");
    	} else {
		if (resol_colision == resolucionCuadratica) {
    			printf("***TABLA CERRADA CUADRATICA\n");
		} else {
			printf("***TABLA CERRADA DOBLE\n");
		}
   	}
	mostrar_cerrada(tabla, 11);
    	printf("Colisiones al insertar elementos: %i\n\n", colisiones);
    	for (i = 0; i < 7; i++) {
    		col_aux[i] = 0;
    		posicion = TestBuscar(claves[i],tabla, &colisiones,
			   &col_aux[i], resol_colision);
    		if (tabla[posicion].ocupada) {
    			printf(" Al buscar: %4s, encuentro: %4s, colisiones:"
			" %4d", claves[i], tabla[posicion].clave, col_aux[i]);
        	} else {
        		printf(" No encuentro: %s, colisiones %d", 
				claves[i], col_aux[i]);
        	}
    		printf("\n");
    	}
    	printf(" \n\n\n "); free(tabla);
}

//////////////////////////////////////////////////////////////////////////////

double mR(item Datos[], int modulo, int iteraciones) {
	double t1, t2;
	int n;	
	t1 = microsegundos();
	for(n = 0; n < iteraciones; n++){		
		Datos[rand() % modulo];					
	}
	t2 = microsegundos();
	return (t2 - t1);
}

void medicion(item Datos[], tabla_cerrada *diccionario, int tam,
		int (*dispersion)(char *, int),unsigned int (*resol_colision)
		(int pos_ini, int num_intento)) {
	double t1, t2, tiempo, x,y,z,final; int n,i,k, iter, m = 19062;
	char asterisco = ' '; int colisiones = 0; int elem = 125;
	for (k=0;k<8;k++){
		iter = 1; final= 0; t1 = microsegundos();
		for(n=0; n<elem; n++){		
			buscar_cerrada(Datos[rand() % m].clave,
			*diccionario, tam, &colisiones, dispersion,
			resol_colision);					
		}
		t2 = microsegundos(); 
		tiempo = t2 - t1 - mR(Datos, m, elem); final = tiempo;
		if (tiempo < 500) {
			asterisco = '*'; iter = 1000;
			do {
				t1 = microsegundos();
				for (i = 0; i < iter; i++) {		
					for(n = 0; n < elem; n++){		
						buscar_cerrada(
						Datos[rand() % m ].clave,
						*diccionario,tam, &colisiones,
						dispersion,resol_colision);
					}	
				}		
				t2 = microsegundos(); tiempo = t2 - t1; 
				final = (tiempo - mR(Datos, m, elem))/1000; 
				iter = iter *10;
			} while (tiempo < 500);
		}	
		elem = elem*2; x = (final/pow(elem,0.8)); 
		y = (final/n); z = (final/(elem*log(elem)));
		printf("%14d %19f %c %14f %16f %17.8f %15d \n",
		n, final, asterisco, x, y, z, iter); asterisco=' '; final=0;
	}
	printf("\n\nLos tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable"
	       " en un bucle\n\n");
}

//////////////////////////////////////////////////////////////////////////////

void sacar (int numDatos, item Datos[],int tam,
		int (*dispersion)(char *, int), 
		unsigned int (*resol_colision)(int pos_ini, int num_intento)){
	int guiones, i = 0;
	int coli = 0;
	tabla_cerrada d = malloc (38197 * sizeof(entrada));
	inicializar_cerrada(&d, 38197);
	for(i = 0; i < numDatos; i++){
		coli += insertar_cerrada(Datos[i].clave, 
			Datos[i].sinonimos, &d, tam,
			dispersion, resol_colision);
	}
	printf("Insertando %i elementos... ",numDatos);
	printf("Numero total de colisiones: %i\n", coli);
	printf("\n%14s %15s %20s %15s %19s %15s\n", "n",
	"t(n)", "t(n)/n^0.8","    t(n)/n","t(n)/n*log(n)", "Iter(*)" );
	for (guiones = 0; guiones < 104; guiones++) {
		printf("-");
	}
	printf("\n");
	medicion(Datos, &d, tam, dispersion, resol_colision);
	free(d);
}

void calentar() {
	int i;
	for (i = 0; i < 10000000; i++);
}

void tablas (int numDatos, item datos[]) {
	calentar();
	printf("***Dispersion cerrada lineal con dispersion A \n");
	sacar(numDatos, datos, 38197, dispersionA, resolucionLineal);
	printf("***Dispersion cerrada lineal con dispersion B \n");
	sacar(numDatos, datos, 38197, dispersionB, resolucionLineal);
	printf("***Dispersion cerrada cuadratica con dispersion A \n");
	sacar(numDatos, datos, 38197, dispersionA, resolucionCuadratica);
	printf("***Dispersion cerrada cuadratica con dispersion B\n");
	sacar(numDatos, datos, 38197, dispersionB, resolucionCuadratica);
	printf("***Dispersion cerrada doble con dispersion A\n");
	sacar(numDatos, datos, 38197, dispersionA, resolucionDoble);
	printf("***Dispersion cerrada doble con dispersion B \n");
	sacar(numDatos, datos, 38197, dispersionB, resolucionDoble);
}	
//////////////////////////////////////////////////////////////////////////////

int main() {
	inicializar_semilla();
    	int numDatos = 19062;
	item datos[numDatos];
	leer_sinonimos(datos);
	
	test(resolucionLineal);
	test(resolucionCuadratica);
	test(resolucionDobleTest);

	tablas(numDatos,datos);
	return 0;
}
