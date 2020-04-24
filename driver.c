#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "common.h"

extern uint64_t rdtsc ();

void baseline ( unsigned n , float a [ n ] , float b [ n ] , float c [ n ] , float d [20]) ;
void baseline_loop_swap ( unsigned n , float a [ n ] , float b [ n ] , float c [ n ] , float d [20]) ;
void baseline_unroll ( unsigned n , float a [ n ] , float b [ n ] , float c [ n ] , float d [20]) ;

int main(int argc, char *argv[])
{
    int i;
    float *a,*b,*c,d[20] ;
    f64 cycles[N_MESURES];
    uint64_t nb_bytes = N_REPET * TAILLE_TAB * 20;

    a = (float*)malloc(TAILLE_TAB * sizeof(float));
    b = (float*)malloc(TAILLE_TAB * sizeof(float));
    c = (float*)malloc(TAILLE_TAB * sizeof(float));

	srand(42);
	init_array(TAILLE_TAB, a);
	init_array(TAILLE_TAB, b);
	init_array(TAILLE_TAB, c);
	init_array(20, d);
    //warmup
	for (int j = 0 ; j < N_WARMUP ; j++)
	{
		baseline(TAILLE_TAB, a,b,c,d);
	}
	
    //free tab
    free(a);
    free(b);
    free(c);

    for(i = 0 ; i < N_MESURES ; i++)
    {
		a = (float*)malloc(TAILLE_TAB * sizeof(float));
		b = (float*)malloc(TAILLE_TAB * sizeof(float));
		c = (float*)malloc(TAILLE_TAB * sizeof(float));
		
        srand(42);
        init_array(TAILLE_TAB, a);
        init_array(TAILLE_TAB, b);
        init_array(TAILLE_TAB, c);
        init_array(20, d);

        //performances mesures
        uint64_t t1 = rdtsc();
        for (int k = 0 ; k < N_REPET ; k++)
			#if BASELINE == 2
				baseline_unroll(TAILLE_TAB, a,b,c,d);
			#elif BASELINE == 1
				baseline_loop_swap(TAILLE_TAB, a,b,c,d);
			#else
				baseline(TAILLE_TAB, a,b,c,d);
			#endif
        uint64_t t2 = rdtsc();
        
        uint64_t time = t2 - t1;
		cycles[i] = (f64)(time) / (f64)(nb_bytes);
		
        //measures; number of elements; elapsed cycles; cycles per element
        fprintf(stdout, "%20llu; %20llu; %20llu; %15.3lf\n", i, nb_bytes, time, (f64)(time) / (f64)(nb_bytes));
        
		//free tab
		free(a);
		free(b);
		free(c);
    }
    
    //
	sort(cycles, i);

	//
	f64 min, max, avg, mea, dev;

	//
	mea = mean(cycles, i);
	  
	//
	dev = stddev(cycles, i);

	//
	min = cycles[0];
	max = cycles[i - 1];
	avg = (min + max) / 2.0;

	//
	fprintf(stderr, "\n\t\t\tmin: %5.3lf; max: %5.3lf; avg: %5.3lf; moy: %5.3lf; dev: %5.3lf %%;\n",
		min,
		max,
		avg,
		mea,
		(dev * 100.0 / mea));
	
	return 0;
}

