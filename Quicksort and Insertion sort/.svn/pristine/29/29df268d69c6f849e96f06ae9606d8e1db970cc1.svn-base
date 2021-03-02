//ALGROTIMOS P2 - Melisa Dimitry Beltrán 

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define UMBRAL 1


double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}


void inicializar_semilla() {
        srand(time(NULL));
}


//Se generan números pseudoaleatorio entre -n y +n y vector de longitud n 
void aleatorio(int v [], int n) {
        int i, m = 2*n + 1;
        for (i = 0; i < n; i++){
                v[i] = (rand() % m) - n;
        }
}


void ascendente(int v [], int n) {
        int i;
        for (i = 0; i < n; i++){
                v[i] = i;
        }
}


void descendente(int v [], int n) {
        int i;
        for (i = 0; i < n; i++){
                v[i] = n - i;
        }
}


void imprimir_vector(int v [], int n) {
        int i;
        for (i = 0; i < n; i++){
        	printf("%d ",v[i]);
        }
}


void ord_ins (int v [], int n) {
        int i, j, x;
        for (i = 1; i < n; i++) {
                x = v[i];
                j = i - 1;
                while (j >= 0 && v[j] > x) {
                        v[j+1] = v[j];;
                        j--;
                }
        v[j+1] = x;
        }
}


void intercambiar (int v1[],int i, int j){
        int v0;
        v0 = v1[i];
        v1[i] = v1[j];                
        v1[j] = v0;
}


void Mediana3 (int v [],int i, int j) {
        int k;
        k = ((i + j)/ 2);
        if (v[k] > v[j]) {
                intercambiar(v,k,j);     
        }
        if (v[k] > v[i]) {
                intercambiar(v,k,i);
        }
        if (v[i] > v[j]) {
                intercambiar(v,i,j);
        }
}


void rapida_aux (int v [], int izq, int der) {
	int i, j, pivote;
	if (izq + UMBRAL <= der) {
		Mediana3 (v, izq, der);
		pivote = v[izq];
		i = izq;
		j = der;
		do {
			do {
				i = i + 1;
			} while (v[i] < pivote);
	
			do {
				j = j - 1;
			} while (v[j] > pivote);

			intercambiar(v, i, j);

		} while (i < j);
		intercambiar(v, i, j);
		intercambiar(v, izq, j);
		rapida_aux(v, izq, j - 1);
		rapida_aux(v, j + 1, der);
	}			
}

void ord_rapida(int v [], int n) {
	rapida_aux(v, 0, n - 1);
	if (UMBRAL > 1) {
		ord_ins(v, n);
	}
}

void test_a1 (int n){
        int * v, i, it = 1;
        char asterisco = ' '; 
	double t,t1,t2,t3,x,y,z; 
	for (i = 0; i < 3; i++) {
		v = (int *) malloc (sizeof(int)*n); ascendente(v,n);
		t1 = microsegundos(); ord_ins (v,n); t2 = microsegundos();
		t = t2 - t1;
		free(v);
		if (t<500){
			it = 1000;
		        do {
		                t1 = microsegundos();
		                for(i = 0; i < it; i++) {
		                        v = (int *) malloc (sizeof(int)*n);
		                        ascendente(v,n);
		                        free(v);
				}
		                t2 = microsegundos();
		                t3 = (t2-t1) / i; //Guardamos ese tiempo
		        	t1 = microsegundos();
				for(i = 0; i < it; i++) {
		               	        v = (int *) malloc (sizeof(int)*n);
		                        ascendente(v,n);
					ord_ins(v,n);
					free(v);
				}
				t2 = microsegundos();
		                asterisco = '*';
				t = ((t2-t1) / i) - t3; 
		                it = it*10;
		        } while (((t2-t1) - t3 * i) < 500);
		}
	}
	x = t / pow(n,0.6); y = t / pow(n,1.0); z = t / pow(n,1.2);
	printf("%30d %15f %c %18f %15f %19f %15d\n", n, t, 
	asterisco, x, y, z, it);	
}

void test_a2(int n){
        int * v, i, it = 1;
        char asterisco = ' '; 
	double t,t1,t2,t3,x,y,z; 
	for (i = 0; i < 2; i++) {
	        v = (int *) malloc (sizeof(int)*n); descendente(v,n);
		t1 = microsegundos(); 
		ord_ins (v,n); 
		t2 = microsegundos();
		t = t2 - t1;
		free(v);
		if (t < 500){
			it = 1000;
		        do {
		                t1 = microsegundos();
		                for(i = 0; i < it; i++) {
		                        v = (int *) malloc (sizeof(int)*n);
		                        descendente(v,n);
		                        free(v);
				}
		                t2 = microsegundos();
		                t3 = (t2-t1) / i; //Guardamos ese tiempo		     
		        	t1 = microsegundos();
				for(i = 0; i < it; i++) {
		               	        v = (int *) malloc (sizeof(int)*n);
		                        descendente(v,n);
					ord_ins(v,n);
					free(v);
				}
				t2 = microsegundos();
		                asterisco = '*';
				t = ((t2-t1) / i) - t3; 
		                it = it*10;
		        } while (((t2-t1) - t3 * i) < 500);
		}
	}
	x = t / pow(n,1.8); y = t / pow(n,2.0); z = t / pow(n,2.2);
	printf("%30d %15f %c %18f %15f %19f %15d\n", n, t, 
	asterisco, x, y, z, it);
}


void test_a3 (int n){
        int * v, i, it = 1;
        char asterisco = ' '; 
	double t,t1,t2,t3,x,y,z;         
	for (i = 0; i < 2; i++) {	
		v = (int *) malloc (sizeof(int)*n); aleatorio(v,n);		
		t1 = microsegundos(); 
		ord_ins (v,n); 
		t2 = microsegundos();
		t = t2 - t1;
		free(v);
		if (t < 500){
			it = 1000;
		        do {
		                t1 = microsegundos();
		                for(i = 0; i < it; i++) {
		                        v = (int *) malloc (sizeof(int)*n);
		                        aleatorio(v,n);
		                        free(v);
				}
		                t2 = microsegundos();
		                t3 = (t2-t1) / i; //Guardamos ese tiempo
		        	t1 = microsegundos();
				for(i = 0; i < it; i++) {
		               	        v = (int *) malloc (sizeof(int)*n);
		                        aleatorio(v,n);
					ord_ins(v,n);
					free(v);
				}
				t2 = microsegundos();
		                asterisco = '*';
				t = ((t2-t1) / i) - t3; 
		                it = it*10;
		        } while (((t2-t1) - t3 * i) < 500);
		}
	}
	x = t / pow(n,1.8); y = t / pow(n,2.0); z = t / pow(n,2.2);
	printf("%30d %15f %c %18f %15f %19.7f %15d\n", n, t, 
	asterisco, x, y, z, it);
}

void test_b1 (int n){
        int * v, i, it = 1;
        char asterisco = ' '; 
	double t,t1,t2,t3,x,y,z;         
	for (i = 0; i < 2; i++) {
		v = (int *) malloc (sizeof(int)*n); ascendente(v,n);	
		t1 = microsegundos(); 
		ord_rapida(v,n); 
		t2 = microsegundos();
		t = t2 - t1;
		free(v);
		if (t < 500){
			it = 1000;
		        do {
		                t1 = microsegundos();
		                for(i = 0; i < it; i++) {
		                        v = (int *) malloc (sizeof(int)*n);
		                        ascendente(v,n);
		                        free(v);
				}
		                t2 = microsegundos();
		                t3 = (t2-t1) / i; //Guardamos ese tiempo
		        	t1 = microsegundos();
				for(i = 0; i < it; i++) {
		               	        v = (int *) malloc (sizeof(int)*n);
		                        ascendente(v,n);
					ord_rapida(v,n);
					free(v);
				}
				t2 = microsegundos();
		                asterisco = '*';
				t = ((t2-t1) / i) - t3; 
		                it = it*10;
		        } while (((t2-t1) - t3 * i) < 500);
		}
	}
	x = t / n; y = t / (n*log(n)); z = t / pow(n,2);
	printf("%30d %15f %c %18f %15f %19.9f %15d\n", n, t, 
	asterisco, x, y, z, it);
}


void test_b2 (int n){
        int * v, i, it = 1;
        char asterisco = ' '; 
	double t,t1,t2,t3,x,y,z; 
	for (i = 0; i < 2; i++) {	
		v = (int *) malloc (sizeof(int)*n); descendente(v,n);	
		t1 = microsegundos(); 
		ord_rapida(v,n); 
		t2 = microsegundos();
		t = t2 - t1;
		free(v);
		if (t<500){
			it = 1000;
		        do {
		                t1 = microsegundos();
		                for(i = 0; i < it; i++) {
		                        v = (int *) malloc (sizeof(int)*n);
		                        descendente(v,n);
		                        free(v);
				}
		                t2 = microsegundos();
		                t3 = (t2-t1) / i; //Guardamos ese tiempo
		        	t1 = microsegundos();
				for(i = 0; i < it; i++) {
		               	        v = (int *) malloc (sizeof(int)*n);
		                        descendente(v,n);
					ord_rapida(v,n);
		                        free(v);
				}
				t2 = microsegundos();
		                asterisco = '*';
				t = ((t2-t1) / i) - t3; 
		                it = it*10;
		        } while (((t2-t1) - t3 * i) < 500);
		}
	}
	x = t / n; y = t / (n*log(n)); z = t / pow(n,2);
	printf("%30d %15f %c %18f %15f %19.9f %15d\n", n, t, 
	asterisco, x, y, z, it);
}


void test_b3 (int n){
        int * v, i, it = 1;
        char asterisco = ' '; 
	double t,t1,t2,t3,x,y,z; 
	for (i = 0; i < 2; i++) {	
		v = (int *) malloc (sizeof(int)*n); 	aleatorio(v,n);
		t1 = microsegundos(); 
		ord_rapida(v,n); 
		t2 = microsegundos();
		t = t2 - t1;
		free(v);
		if (t<500){
			it = 1000;
		        do {
		                t1 = microsegundos();
		                for(i = 0; i < it; i++) {
		                        v = (int *) malloc (sizeof(int)*n);
		                        aleatorio(v,n);
		                        free(v);
				}
		                t2 = microsegundos();
		                t3 = (t2-t1) / i; //Guardamos ese tiempo
		        	t1 = microsegundos();
				for(i = 0; i < it; i++) {
		               	        v = (int *) malloc (sizeof(int)*n);
		                        aleatorio(v,n);
					ord_rapida(v,n);
					free(v);
				}
				t2 = microsegundos();
		                asterisco = '*';
				t = ((t2-t1) / i) - t3; 
		                it = it*10;
		        } while (((t2-t1) - t3 * i) < 500);
		}
	}
	x = t / n; y = t / (n*log(n)); z = t / pow(n,2.0);
	printf("%30d %15f %c %18f %15f %19.8f %15d\n", n, t, 
	asterisco, x, y, z, it);
}


int test_0 (){
        int n=15;
        int * v = malloc (sizeof(int)*n);
        printf ("\n...TEST ORDENACION POR INSERCION...\n\n");
        printf("Ordenacion por insercion con inicializacion aleatoria: \n");
        inicializar_semilla();
        aleatorio(v,n);
        imprimir_vector(v,n);
        printf("\n");
        ord_ins(v,n);
        imprimir_vector(v,n);
        printf("\n\n");

        printf("Ordenacion por insercion con inicializacion descendente: \n");
        descendente(v,n);
        imprimir_vector(v,n);
        printf("\n");
        ord_ins(v,n);
        imprimir_vector(v,n);
	free(v);
        printf("\n\n");

        return 0;
}


int test_1 (){

        int n=15;
        int * v = malloc (sizeof(int)*n);
        printf ("\n...TEST ORDENACION RAPIDA...\n\n");
        printf("Ordenacion rápida con inicializacion aleatoria: \n");
        inicializar_semilla();
        aleatorio(v,n);
        imprimir_vector(v,n);
        printf("\n");
        ord_rapida(v,n);
        imprimir_vector(v,n);
        printf("\n\n");
	
        printf("Ordenacion rápida con inicializacion descendente: \n");
        descendente(v,n);
        imprimir_vector(v,n);
        printf("\n");
        ord_rapida(v,n);
        imprimir_vector(v,n);	
        printf("\n\n");
	free(v);
	
        return 0;
}


void sacarTablas_parte1() {
	int n;
	int guiones;
	printf("\n\nALGORITMO DE ORDENACIÓN POR INSERCIÓN: \n");	
	printf("\nTiempos v. asc(n) %12s %15s %20s %15s %19s %15s\n", "n",
        "Tiempo", "sub.  n^0.6","ajust.  n","sobre.  n^1.2", "Iter(*)");
	for (guiones = 0; guiones < 121; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (n = 500;n < 32001; n = n * 2) { 
		test_a1(n);
	}
	printf("\nTiempos v. desc(n) %12s %15s %20s %15s %19s %15s\n", "n", 
        "Tiempo", "sub.  n^1.8","ajust.  n^2","sobre.  n^2.2", "Iter(*)" );
	for (guiones = 0; guiones < 121; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (n = 500;n < 32001; n = n * 2) {
		test_a2(n);
	}
	printf("\nTiempos v. al(n) %14s %15s %20s %15s %19s %15s\n", "n",
	"Tiempo", "sub.  n^1.8","ajust.  n^2","sobre.  n^2.2", "Iter(*)" );
	for (guiones = 0; guiones < 121; guiones++) {
		printf("-");
	}	
	printf("\n");
        for (n = 500;n < 32001; n = n * 2){
        	test_a3(n);
        }
	printf("\nLos tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable en un bucle\n");
}


void sacarTablas_parte2() {
        int n, guiones;	
	printf("\n\nALGORITMO DE ORDENACiÓN RÁPIDA: \n");
	printf("(El umbral utilizado ha sido %d)\n",UMBRAL);	
	printf("\nTiempos v. asc(n) %12s %15s %20s %18s %19s %13s\n", "n",
	"Tiempo", "sub.  n  ","ajust. n(log n)","sobre.  n^2", "Iter(*)" );
	for (guiones = 0; guiones < 121; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (n = 500;n < 32001; n = n * 2) { 
		test_b1(n);
	}
	printf("\nTiempos v. desc(n) %12s %12s %20s %20s %16s %15s\n", "n",
        "Tiempo", "sub.  n","ajust. n(log n)","sobre.  n^2", "Iter(*)");
	for (guiones = 0; guiones < 121; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (n = 500;n < 32001; n = n * 2) { 
		test_b2(n);
	}
	printf("\nTiempos v. al(n) %12s %15s %21s %18s %19s %13s\n", "n",
	"Tiempo", "sub.  n  ","ajust. n(log n)","sobre.  n^2", "Iter(*)");
	for (guiones = 0; guiones < 121; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (n = 500;n < 32001; n = n * 2) { 
		test_b3(n);
	}
	printf("\nLos tiempos acompañados de un asterisco (*) han sido ");
        printf("medidos con un numero de iteraciones variable en un bucle\n");
}

void test() {
	test_0();
	test_1();
}

void sacar_Tablas() {
	sacarTablas_parte1();
	sacarTablas_parte2();
}

int main() {        
	test();
        sacar_Tablas();
	return 0;
}

