#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <inttypes.h>

int fib1(int n) {
	if (n < 2) {
		return n;
	}
	else {
		return (fib1(n-1) + fib1(n-2));
	}

}

int fib2(int n) {
	int i = 1;
	int j = 0;
	int k;
	for(k = 0; k < n; k++) {
		j = i + j;
		i = j - i;
	}
	return j;
}

int fib3(int n)
{
	int i = 1;
	int j = 0;
	int k = 0;
	int h = 1;
	int t = 0;
	while(n > 0) {
		if ((n % 2)==1) {
			t = j * h;
			j = (i * h) + (j * k) + t;
			i = (i * k) + t;
		}
		t = h * h;
		h = (2 * k * h) +t;
		k = (k * k) + t;
		n = n / 2;
	}
	return j;	
}

void testSecuencia() {
	printf("%7s %7s %7s %7s", "n", "fib1(n)", "fib2(n)", "fib3(n) \n");
      printf("     ---------------------------\n");
		for (int n=0; n<16; n++) {
			printf("%7d %7d %7d %7d \n", n, fib1(n), fib2(n), fib3(n));
		}
}

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
	}

void test_fib3(int n, int b_control) {
	double t1, t2, t, x, y, z;
	int i;
	char asterisco = ' ';
	t1 = microsegundos();
 	fib3(n);
	t2 = microsegundos();
	t = t2-t1;
	if (t<500){
		for(i = 0; i < 10000; i++) {
			fib3(n);
		}
		asterisco = '*';
		t2 = microsegundos();
		t = (t2-t1) / i;
	} 
	x = t / sqrt(log(n));
	y = t / log(n);
	z = t / pow(n, 0.5);
	if (b_control == 2) {
		printf("%28d %15f %c %18f %15f %19f\n", n, t, asterisco, x, y, z);
	}
}

void test_fib2(int n, int b_control) {
	double t1, t2, t, x, y, z;
	int i;
	char asterisco = ' ';
	t1 = microsegundos();
 	fib2(n);
	t2 = microsegundos();
	t = t2-t1;	
	if (t<500){
		for(i = 0; i < 10000; i++) {
			fib2(n);
		}
		asterisco = '*';
		t2 = microsegundos();
		t = (t2-t1) / i;
	} 
	x = t / pow(n, 0.8);
	y = t / n;
	z = t /( n * log(n) );
	if (b_control == 2) {
		printf("%28d %15f %c %18f %15f %19f\n", n, t, asterisco, x, y, z);
	}
}
 
void test_fib1(int n, int b_control) {
	double t1, t2, t, x, y, z;
	int i;
	char asterisco = ' ';
	t1 = microsegundos();
 	fib1(n);
	t2 = microsegundos();
	t = t2-t1;
	if (t<500){
		for(i = 0; i < 10000; i++) {
			fib1(n);	
		}
		asterisco = '*';
		t2 = microsegundos();
		t = (t2-t1) / i;
	} 
	x = t / pow(1.1, n);
	y = t / pow((1+sqrt(5))/2, n);
	z = t / pow(2, n);
	if (b_control == 2) {
		printf("%28d %15f %c %18f %15f %19f\n", n, t, asterisco, x, y, z);
	}
}

void sacarTablas() {
	int i;
	int j;
	int guiones;	
	printf("\n     TEST SECUENCIA: \n\n");
	testSecuencia();	
	printf("\nTiempos fib1(n) %12s %15s %20s %15s %19s \n", "n","Tiempo" ,
	"Cota subestimada","Cota ajustada","Cota sobreestimada" );
	for (guiones = 0; guiones < 101; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (j = 0; j < 3; j++ ) {
		for (i = 2;i < 33; i = i * 2) { 
			test_fib1(i, j);
		}
	}
	printf("\nTiempos fib2(n) %12s %15s %20s %15s %19s \n", "n","Tiempo" ,
	"Cota subestimada","Cota ajustada","Cota sobreestimada" );
	for (guiones = 0; guiones < 101; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (j = 0; j < 3; j++ ) {
		for (i = 1000;i < 10000001; i = i * 10) {
			test_fib2(i, j);
		}
	}
	printf("\nTiempos fib3(n) %12s %15s %20s %15s %19s \n", "n","Tiempo" ,
	"Cota subestimada","Cota ajustada","Cota sobreestimada" );
	for (guiones = 0; guiones < 101; guiones++) {
		printf("-");
	}	
	printf("\n");
	for (j = 0; j < 3; j++ )for (i = 1000;i < 10000001; i = i * 10)test_fib3(i, j);
	printf("\nLos tiempos acompañados de un asterisco (*) han sido medidos como la media de 10000 iteraciones en un bucle\n");
}


int main() {
	sacarTablas();
}
