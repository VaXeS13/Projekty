#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(){

    int N = 100000000;

    int suma = 0;

    for(int i=1; i<5; i++){

    #pragma omp parallel reduction(+:suma) num_threads(i)
    {
        int in = 0;
        int id = omp_get_thread_num();
        srand(time(NULL));

        #pragma omp for

            for(int i=0; i< N; i++){
                double x = (double)rand ()/RAND_MAX;
                double y = (double)rand ()/RAND_MAX;

                if(x*x + y*y <= 1.0){
                    in++;
                }
            }


        suma += in;

        printf("%d -> %d\n", id, in);

    }

    printf("Pi ~ %lf\n\n",4.0*suma/N);
    suma=0;
    }
    return 0;
}
