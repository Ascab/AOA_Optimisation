#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <emmintrin.h>
#include <xmmintrin.h>
#include <mmintrin.h>
#include "common.h"

extern uint64_t rdtsc ();

void baseline ( unsigned n , float a [ n ] , float b [ n ] ,
float c [ n ] , float d [20]) ;
void baseline_vect (const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d);
void baseline_vect_hoist_interchange( unsigned n , float * restrict a  , float * restrict b ,float * restrict c , float * restrict d);
void baseline_vect_hoist_interchange_mem( unsigned n , float * restrict a  , float * restrict b ,float * restrict c , float * restrict d);

int main(int argc, char *argv[])
{
    int i;
    float *a,*b,*c,d[20] ;
    f64 cycles[N_MESURES];
    uint64_t nb_bytes = N_REPET * TAILLE_TAB * 20;

    a = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);
    b = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);
    c = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);

	srand(42);
	init_array(TAILLE_TAB, a);
	init_array(TAILLE_TAB, b);
	init_array(TAILLE_TAB, c);
	init_array(20, d);
    //warmup
	for (int j = 0 ; j < N_WARMUP ; j++)
	{
    #if BASELINE
    baseline(TAILLE_TAB, a,b,c,d);
    #endif
    #if VECT_HOIST_INTERCHANGE
    baseline_vect_hoist_interchange(TAILLE_TAB, a,b,c,d);
    #endif
    #if VECT
    baseline_vect(TAILLE_TAB, a,b,c,d);
    #endif
    #if VECT_HOIST_INTERCHANGE_MEM
    baseline_vect_hoist_interchange_mem(TAILLE_TAB, a,b,c,d);
    #endif
	}

    //free tab
    _mm_free(a);
    _mm_free(b);
    _mm_free(c);

    for(i = 0 ; i < N_MESURES ; i++)
    {
      #if ALT_DRIVER
      #include <unistd.h>
      uint64_t diff[N_MESURES] ;

      a = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);
      b = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);
      c = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);

      srand(42);
      init_array(TAILLE_TAB, a);
      init_array(TAILLE_TAB, b);
      init_array(TAILLE_TAB, c);
      for (int r=0 ; r < N_MESURES ; r++)
      {
        uint64_t start = rdtsc();
        #if BASELINE
          baseline(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT_HOIST_INTERCHANGE
          baseline_vect_hoist_interchange(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT
          baseline_vect(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT_HOIST_INTERCHANGE_MEM
          baseline_vect_hoist_interchange_mem(TAILLE_TAB, a,b,c,d);
        #endif

        uint64_t stop = rdtsc();
        diff[r] = stop - start;
        for (int r = 0 ; r < N_REPET ; r++)
        {
          printf("%.3f\n", (float)diff[r] / (float)(TAILLE_TAB * 20);
        }
          _mm_free(a);
          _mm_free(b);
          _mm_free(c);
      }
     #else
		a = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);
		b = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);
		c = (float*)_mm_malloc(TAILLE_TAB*sizeof(float), 32);

        srand(42);
        init_array(TAILLE_TAB, a);
        init_array(TAILLE_TAB, b);
        init_array(TAILLE_TAB, c);
        init_array(20, d);

        //performances mesures
        uint64_t t1 = rdtsc();
        for (int k = 0 ; k < N_REPET ; k++)
        {
        #if BASELINE
        baseline(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT_HOIST_INTERCHANGE
        baseline_vect_hoist_interchange(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT
        baseline_vect(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT_HOIST_INTERCHANGE_MEM
        baseline_vect_hoist_interchange_mem(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT_HOIST_INTERCHANGE_MEM_PARALLEL
        baseline_vect_hoist_interchange_mem(TAILLE_TAB, a,b,c,d);
        #endif
        #if VECT_HOIST_INTERCHANGE_PARALLEL
        baseline_vect_hoist_interchange(TAILLE_TAB, a,b,c,d);
        #endif
      }
        uint64_t t2 = rdtsc();

        uint64_t time = t2 - t1;
		cycles[i] = (f64)(time) / (f64)(nb_bytes);

        //measures; number of elements; elapsed cycles; cycles per element
        fprintf(stdout, "%20llu; %20llu; %20llu; %15.3lf\n", i, nb_bytes, time, (f64)(time) / (f64)(nb_bytes));

		//free tab
		_mm_free(a);
		_mm_free(b);
		_mm_free(c);
    #endif
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
// void init_array(size_t size, float *tab )
// {
//     int i ;
//     for (i = 0 ; i < size ; i++)
//     {
//         tab[i] = (float)rand() / (float)RAND_MAX;
//     }
// }
