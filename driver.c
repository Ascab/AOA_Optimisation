#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//ARGV[1] = n_warmup
//ARGV[2] = n_mesures
//ARGV[3] = n_repet
//ARGV[4] = taille tab
extern uint64_t rdtsc ();

void init_array(size_t size, float *tab);
void baseline ( unsigned n , float a [ n ] , float b [ n ] ,
float c [ n ] , float d [20]) ;
int main(int argc, char *argv[])
{
	if(argc != 5){
		exit(1);
	}
    size_t n;
    int i;
    float *a,*b,*c,d[20] ;
    
    int n_warmup = atoi(argv[1]);
	int n_mesures = atoi(argv[2]);
	int n_repet = atoi(argv[3]);
    n = atoi(argv[4]) ;
    a = (float*)malloc(n * sizeof(float));
    b = (float*)malloc(n * sizeof(float));
    c = (float*)malloc(n * sizeof(float));

	srand(42);
	init_array(n, a);
	init_array(n, b);
	init_array(n, c);
	init_array(20, d);
    //warmup
	for (int j ; j < n_warmup ; j++)
	{
		baseline(n, a,b,c,d);
	}

    for(i = 0 ; i < n_mesures ; i++)
    {
        srand(42);
        init_array(n, a);
        init_array(n, b);
        init_array(n, c);
        init_array(20, d);

        //performances mesures
        uint64_t t1 = rdtsc();
        for (int k = 0 ; k < n_repet ; k++)
            baseline(n, a,b,c,d);
        uint64_t t2 = rdtsc();
        //print performances
        printf("%.2f cycles/itération \n", (float)(t2-t1 ) / ((float) n *  n_repet));
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
