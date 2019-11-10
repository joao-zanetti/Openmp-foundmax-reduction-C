/*
    Developed by João Zanetti
    https://github.com/joao-zanetti
*/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define nt 10
#define N 100
#define seed 10000

int main(int argc,char **argv){
    double wtime;
    int i,max,v[N];

    //generate the numbers of vector with seed
	for (i = 0; i < N; i++) {
        v[i] = rand()%seed;
        //printf("%d ",v[i]);
	}

    //initialize global min
    max=v[0];
    
    //initialize the clock
    wtime = omp_get_wtime();
    //parallel for, with reduction operation(logN) of result from each thread
    #pragma omp parallel for private(i) shared(v) reduction(max: max) num_threads(nt)
        for(i =0; i <N; i++)
        {
            if(v[i]>max){
                max=v[i];
            }
        }

    //finalize the clock
    wtime = omp_get_wtime()-wtime;
    printf("time: %lf\nmax:%d \n",wtime,max);
    return 0;
}
