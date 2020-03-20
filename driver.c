#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define NB_MESURES 2
#define NB_REPET 100
extern uint64_t rdtsc ();

void init_array(size_t size, float *tab);
void baseline ( unsigned n , float a [ n ] , float b [ n ] ,
float c [ n ] , float d [20]) ;
int main()
{
    size_t n;
    int i;
    float *a,*b,*c,d[20] ;

    n = 500000 ;
    a = (float*)malloc(n * sizeof(float));
    b = (float*)malloc(n * sizeof(float));
    c = (float*)malloc(n * sizeof(float));

    for(i = 0 ; i < NB_MESURES ; i++)
    {
        srand(42);
        init_array(n, a);
        init_array(n, b);
        init_array(n, c);
        init_array(20, d);
    //warmup
        if(!i)
        {
            for (int j ; j < 10 ; j++)
            {
                baseline(n, a,b,c,d);
            }
        }
        else
            baseline(n, a,b,c,d);

        //performances mesures
        uint64_t t1 = rdtsc();
        for (int k = 0 ; k < NB_REPET ; k++)
            baseline(n, a,b,c,d);
        uint64_t t2 = rdtsc();
        //print performances
        printf("%.2f cycles/itération \n", (float)(t2-t1 ) / ((float) n *  NB_REPET));
    }
    //free tab
    free(a);
    free(b);
    free(c);
}
void init_array(size_t size, float *tab )
{
    int i ;
    for (i = 0 ; i < size ; i++)
    {
        tab[i] = rand() / RAND_MAX;
    }
}
