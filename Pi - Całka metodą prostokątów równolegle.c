/*
Liczenie wartości Pi za pomocą metody prostokątów z użyciem biblioteki OpenMP
Autor: Marcin Hinc
*/

#include <stdio.h>
#include <omp.h>
#include <math.h>

double funkcja(double x){
    return (double)(1/(1 + x*x));
}

int main(){

    int prostokaty;
    double a, b;
    double wynik = 0;
    printf("Podaj liczbe protokatow: ");
    scanf("%d",&prostokaty);

    printf("\nPodaj a: ");
    scanf("%lf",&a);

    printf("\nPodaj a: ");
    scanf("%lf",&a);

    #pragma omp parallel reduction(+:wynik) firstprivate(prostokaty,a,b)
    {
        #pragma omp for
            for(int i=1; i<=prostokaty; i++){
                wynik += funkcja(a+i*((b-a)/(double)prostokaty));
            }

    }
    wynik *= (b-a)/(double)prostokaty;

    printf("wynik: %lf", wynik);


    return 0;
}
