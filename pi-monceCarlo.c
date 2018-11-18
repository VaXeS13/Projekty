#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){

    long long ile = 10000000000000000;
    long long suma = 0;
    #pragma omp parallel firstprivate(ile) reduction(+:suma)
    {
        long long ile_weszlo = 0;
        #pragma omp for
        for(long long i=0; i<ile; i++){
            double x = (double)rand()/RAND_MAX;
            double y = (double)rand()/RAND_MAX;

            if(x*x + y*y <= 1.0){
                ile_weszlo++;

            }
        }

        suma += ile_weszlo;
    }

    printf("%lf", 4.0*(double)suma/ile);
    return 0;
}
