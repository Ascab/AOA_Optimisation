#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <emmintrin.h>
#define NB_MESURES 31
#define NB_REPET 31
extern uint64_t rdtsc ();

void init_array(size_t size, float *tab);
void baseline ( unsigned n , float a [ n ] , float b [ n ] ,
float c [ n ] , float d [20]) ;
void baseline_vect (const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d);
int main()
{
    size_t n;
    int i;
    float *a,*b,*c,*d ;
	float *ap,*bp,*cp,*dp ;
    n = 600000 ;
    /*
		a = _mm_malloc(n*sizeof(float), 32);
		b = _mm_malloc(n*sizeof(float), 32);
		c = _mm_malloc(n*sizeof(float), 32);
		d = _mm_malloc(20*sizeof(float), 32);
		*/
		/*
		a = (float*)malloc(n * sizeof(float));
		b = (float*)malloc(n * sizeof(float));
		c = (float*)malloc(n * sizeof(float));
		*/
		
		ap = _mm_malloc(n*sizeof(float), 32);//(float*)malloc(n * sizeof(float));
		bp = _mm_malloc(n*sizeof(float), 32);//(float*)malloc(n * sizeof(float));
		cp = _mm_malloc(n*sizeof(float), 32);//(float*)malloc(n * sizeof(float));
		dp = _mm_malloc(20*sizeof(float), 32);
		
    for(i = 0 ; i < NB_MESURES ; i++)
    {
        srand(42);
        /*
        init_array(n, a);
        init_array(n, b);
        init_array(n, c);
        init_array(20, d);
        */
        init_array(n, ap);
        init_array(n, bp);
        init_array(n, cp);
        init_array(20, dp);
        
        /*
        for(int k=0;k<n;k++)
        {
			ap[i]=a[i];
			bp[i]=b[i];
			cp[i]=c[i];
		}
		for(int k=0;k<20;k++)
        {
			dp[i]=d[i];
		}
		printf("Check: %f %f \n",a[0],ap[0]);
		*/
    //warmup
        if(!i)
        {
            for (int j ; j < 10 ; j++)
            {
				//baseline(n, ap,bp,cp,dp);
				baseline_vect_hoist_interchange(n, ap,bp,cp,dp);
                //baseline_vect(n, ap,bp,cp,dp);
            }
        }
        else
        {
            //baseline(n, ap,bp,cp,dp);
            baseline_vect_hoist_interchange(n, ap,bp,cp,dp);
            //baseline_vect(n, ap,bp,cp,dp);
        }

        //performances mesures
        uint64_t t1 = rdtsc();
        for (int k = 0 ; k < NB_REPET ; k++)
        {
			//baseline(n, ap,bp,cp,dp);
			baseline_vect_hoist_interchange(n, ap,bp,cp,dp);
            //baseline_vect(n, ap,bp,cp,dp);
        }
        uint64_t t2 = rdtsc();
        //print performances
        printf("%.2f cycles/itération \n", (float)(t2-t1 ) / ((float) 20 * n *  NB_REPET));
        /*
        int valid=1;
        for(int k=0;k<n;k++)
        {
			if(ap[k]!=a[k])
			{
				valid=0;
			}
		}
		if(valid)
		{
			printf("Resultat valide : %f %f \n",a[0],ap[0]);
		}
		else
		{
			printf("Resultat non valide : %f %f \n",a[0],ap[0]);
		}
		*/

    }
		 //free tab
		/* 
		_mm_free(a);
		_mm_free(b);
		_mm_free(c);
		_mm_free(d);
		*/
		_mm_free(ap);
		_mm_free(bp);
		_mm_free(cp);
		_mm_free(dp);
		
		/*
		free(a);
		free(b);
		free(c);
		*/
		/* 
		//free(ap);
		//free(bp);
		//free(cp);
		*/ 
}
void init_array(size_t size, float *tab )
{
    int i ;
    for (i = 0 ; i < size ; i++)
    {
        tab[i] = 1.0; //(float)rand() / (float)RAND_MAX;
    }
}
