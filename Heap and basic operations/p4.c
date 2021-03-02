// Beltrán Aceves, Dimitry Demyanov y Melisa Barro - 2º-2.2 Algoritmos P4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#define TAM 128000

typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;

///////////////////////////////////////////////////////////////////////////////

void inicializar_semilla() {
	srand(time(NULL));
}

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

///////////////////////////////////////////////////////////////////////////////

int PARENT(int i) {
	return ((i-1) / 2);
}


void insertar_Array(monticulo *M, int *v, int n) {
	int i;
	for (i = 0; i < n; i++) {
		(*M).vector[i] = v[i];
	}
	(*M).ultimo = n - 1;	
}

void copiar_en_Array(monticulo *M, int *v) {
	int i;
	for (i = 0; i < (*M).ultimo + 1; i++) {
		v[i] = (*M).vector[i];
	}
}

void mostrar_monticulo(monticulo *M) {
	int i;
	if ((*M).ultimo == 0) {
		printf("El montículo está vacío. \n\n");
	} else {
		printf("Montículo: ");
		for (i = 0; i < (*M).ultimo + 1; i++) {
			printf("%d  ", (*M).vector[i]);
		}
		printf("\n\n");
	}
}

void mostrar_vector(int v[], int n) {
	int i;
	printf("Vector:");
	for (i = 0; i < n; i++) {
		printf("%d  ", v[i]);
	}
	printf("\n\n");
}

void aleatorio(int *v, int n, int bit_c) {
	int i, m = 2*n+1;
	for (i = 0; i < n; i++) {
		v[i] = (rand() % m) - n;
	}
	if (bit_c == 1) {
		printf("Vector aleatorio: ");
		for (i = 0; i < n; i++) {
			printf("%d   ", v[i]);			
		}
	}
}

void ascendente(int *v, int n, int bit_c) {
        int i;
        for (i = 0; i < n; i++){
                v[i] = i;
        }
	if (bit_c == 1) {
		printf("Vector ascendente: ");
		for (i = 0; i < n; i++) {
			printf("%d   ", v[i]);			
		}
	}
}


void descendente(int *v, int n, int bit_c) {
        int i;
        for (i = 0; i < n; i++){
                v[i] = n - i;
        }
	if (bit_c == 1) {
		printf("Vector descendente: ");
		for (i = 0; i < n; i++) {
			printf("%d   ", v[i]);			
		}
	}
}

void aleatorio_Monticulo(monticulo *M, int n) { 
	int i, m=2*n+1;
	for (i=0; i < n; i++) {
		(*M).vector[i] = (rand() % m) - n;
	}
	(*M).ultimo = n - 1;
}

///////////////////////////////////////////////////////////////////////////////

void intercambiar(monticulo *M, int i, int j) {	        
	int aux;
	aux = (*M).vector[i];
	(*M).vector[i] = (*M).vector[j];
	(*M).vector[j] = aux;
}

int monticulo_vacio(monticulo *M) {			
	if ((*M).ultimo == -1) {
		return -1;
	} else {
		return 0;
	}
}

void Hundir(monticulo *M, int i) {	
	int HijoIzq, HijoDer, j;
	do {
		HijoIzq = 2*i + 1;
		HijoDer = 2*i + 2;
		j = i;
		if ((HijoDer <= (*M).ultimo) &&
			((*M).vector[HijoDer] > (*M).vector[i])) {
			i = HijoDer;
		}
		if ((HijoIzq <= (*M).ultimo) && 
			((*M).vector[HijoIzq] > (*M).vector[i])) {
			i = HijoIzq;
		}
		intercambiar(M, i, j);
	} while (j != i);
}

///////////////////////////////////////////////////////////////////////////////

void ini_monticulo(monticulo *M) {
	(*M).ultimo = 0;
}

void crear_monticulo(int *vec, monticulo *M, int n) {
	int i;		
	insertar_Array(M, vec, n);
	for (i = (*M).ultimo / 2; i > -1 ; i--) {
		Hundir(M, i);
	}

}

int eliminar_mayor(monticulo *M) {
	int x;	
	if (monticulo_vacio(M)) {
		printf("Error al eliminar el máximo: el montículo está vacío");
		return -1; 
	} else {
		x = (*M).vector[0];
		(*M).vector[0] = (*M).vector[(*M).ultimo];
		(*M).ultimo--;
		if ((*M).ultimo > -1) {
			Hundir(M, 0);
		}
		return x;
	}
}

void ord_monticulo(int *v, int n) {
	int i;
	monticulo *M = (monticulo*) malloc(sizeof(monticulo));		
	crear_monticulo(v, M, n);
	for (i = n - 1; i > -1; i--) {
		v[i] = eliminar_mayor(M);
	}
	free(M);
}

////////////////////////////////////////////////////////////////////////////////

void imprimir_vector(int *tree, int nodos) {
	int print_pos[nodos];
    	int i, j, k, pos, x=1, level=0, LINE_WIDTH = 70;
    	print_pos[0] = 0;
    	for(i=0,j=1; i<nodos; i++,j++) {
        	pos = print_pos[PARENT(i)] + 
		      (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);
        	for (k=0; k<pos-x; k++) {
			printf("%c",i==0||i%2?' ':'-');
		}
		printf("[%d]",tree[i]);
		print_pos[i] = x = pos+1;
		if (j==pow(2,level)) {
		    printf("\n");
		    level++;
		    x = 1;
		    j = 0;
		}
    	}
	printf("\n");
}

void imprimir_monticulo(monticulo *M) {
	int nodos = (*M).ultimo + 1;	
	int print_pos[nodos], tree[nodos];
    	int i, j, k, pos, x=1, level=0, LINE_WIDTH = 70;
	copiar_en_Array(M, tree);
    	print_pos[0] = 0;
	mostrar_monticulo(M);
	printf("\n");
    	for(i=0,j=1; i<nodos; i++,j++) {
        	pos = print_pos[PARENT(i)] +
		      (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);
        	for (k=0; k<pos-x; k++) {
			printf("%c",i==0||i%2?' ':'-');
		}
		printf("[%d]",tree[i]);
		print_pos[i] = x = pos+1;
		if (j==pow(2,level)) {
		    printf("\n");
		    level++;
		    x = 1;
		    j = 0;
		}
    	}
	printf("\n\n");
}

///////////////////////////////////////////////////////////////////////////////

void medicion_heapsort(void (*get_vector)(int *v, int n, int bit_c)) {
	double x, y, z, t1, t2, tiempo, calculos = 0;
	int n, i, iter = 1, *vec = (int*) malloc(sizeof(int) * TAM);
	char asterisco = ' ';
	printf("\n%14s %15s %20s %15s %19s %15s\n", "n",
	       "t(n)", "t(n)/n*log(n)^0.6",
	       "    t(n)/n*log(n)","t(n)/n*log(n)^1.2", "Iter(*)" );
	for (i = 0; i < 104; i++) {
		printf("-");
	}
	printf("\n");
	for (n = 1000; n < TAM+1; n = n*2) {
		get_vector(vec, n, 0); t1 = microsegundos();
                ord_monticulo(vec, n); t2 = microsegundos(); tiempo = t2 - t1;	
		if (tiempo < 500) {
			asterisco = '*'; iter = 500;
			do {	
                                iter = iter * 2; t1 = microsegundos();
				for (i = 0; i < iter; i++) {
					get_vector(vec, n, 0);
                                        ord_monticulo(vec, n);
				}
				t2 = microsegundos(); tiempo = t2 - t1; 
			} while (tiempo < 500);
			t1 = microsegundos();
			for (i = 0; i < iter; i++) {
				get_vector(vec, n, 0);
			}
			t2 = microsegundos(); calculos = t2 - t1;
			tiempo = (tiempo - calculos) / iter;
		} 
		x = tiempo / (n*pow(log(n),0.6)); 
		y = tiempo / (n * log(n));  z = tiempo / (n * pow(log(n),1.2));
		printf("%14d %19f %c %14f %16f %17.8f %15d \n",
		n, tiempo, asterisco, x, y, z, iter); asterisco=' '; 
		calculos = 0; iter = 1;
	}	
	free(vec);
	printf("\n\n");
}

void medicion_crear_monticulo() {
	double x, y, z, t1, t2, t, calculos = 0;
	int n, i, iter = 1, *vec = (int*) malloc(sizeof(int) * TAM);
	char asterisco = ' ';
	monticulo *M = (monticulo*) malloc(sizeof(monticulo));
	printf("\n%14s %15s %20s %15s %19s %15s\n", "n",
	"t(n)", "t(n)/n^0.9",
		"    t(n)/n","t(n)/n^1.1", "Iter(*)" );
	for (i = 0; i < 104; i++) {
		printf("-");
	}
	printf("\n");
	for (n = 1000; n < TAM+1; n = n*2) {		
		ascendente(vec, n, 0); t1 = microsegundos();
		crear_monticulo(vec, M, n); t2 = microsegundos(); t = t2 - t1;
		if (t < 500) {
			asterisco = '*'; iter = 500;
			do {	
                                iter = iter * 2; t1 = microsegundos();
				for (i =0; i < iter; i++) {
					ascendente(vec, n, 0);
					crear_monticulo(vec, M, n);
				}
				t2 = microsegundos(); t = t2 - t1; 
			} while (t < 500);
			t1 = microsegundos();
			for (i = 0; i < iter; i++) {
				ascendente(vec, n, 0);
			}
			t2 = microsegundos(); calculos = t2 - t1;
			t = (t - calculos) / iter;	
		}
		x = t / pow(n,0.9); 
		y = t / (n);  z = t / pow(n,1.1); 
                printf("%14d %19f %c %14f %16f %17.8f %15d \n",
		n, t, asterisco, x, y, z, iter); asterisco=' '; 
		calculos = 0; iter = 1;
	}
	free(vec); free(M); printf("\n\n");	
}

void test() {
	monticulo *M = (monticulo*) malloc(sizeof(monticulo));
	int vec[12];
	printf("\n               Test: \n");
	printf("____________________________________\n\n\n");
	aleatorio(vec, 12, 1); printf("\n");
	crear_monticulo(vec, M, 12);
	imprimir_monticulo(M);
	ord_monticulo(vec, 12);
	printf("\nOrdenacion por montículos\n");
	mostrar_vector(vec, 12);
	free(M);
}

void calentar(){
        int i;
        for (i=0;i<10000000;i++){
                i=i+1-1;
        }
}

void sacarTablas() {
        calentar();
	test();
	printf("Creación de monticulos a partir de vectores ascendentes\n");
	medicion_crear_monticulo();
	printf("Los tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable"
	       " en un bucle\n\n");
	printf("Ordenación por montículos con vector aleatorio: \n\n");
	medicion_heapsort(aleatorio);
	printf("Los tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable"
	       " en un bucle\n\n");
	printf("Ordenación por montículos con vector descendente: \n\n");
	medicion_heapsort(descendente);
	printf("Los tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable"
	       " en un bucle\n\n");
	printf("Ordenación por montículos con vector ascendente: \n\n");
	medicion_heapsort(ascendente);
	printf("Los tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable"
	       " en un bucle\n\n");
}

///////////////////////////////////////////////////////////////////////////////

int main() {
	inicializar_semilla();
	sacarTablas();
}	
