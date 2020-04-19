#include <math.h>
#include <omp.h>
/*
float a_i_exp( float b , float * restrict d)
{
	float a=0.0;
	for (int k =0; k < 20; k ++)
	{
		a += exp( b + d[k]);
    }
    return a;
}
float a_i_mul( float b ,float * restrict d)
{
	float a=0.0;
	for (int k =0; k < 20; k ++)
    {
      	a += b * d[k];
    }
    return a;
}
*/
/*
int reduc_k_exp( float b ,float c , float * restrict d)
{
	unsigned k;
	float r=0.0;
	#pragma ivdep
	#pragma vector aligned
	for ( k =0; k < 20; k ++) 
	{
		r  += exp ( b + d [ k ]); // c [ i ];
	}
	return r/c;
}

int reduc_k( float b ,float c , float * restrict d)
{
	unsigned k;
	float r=0.0;
	#pragma ivdep 
	#pragma vector aligned
	for ( k =0; k < 20; k ++) 
	{
		r  += d [ k ]; // c [ i ];
	}
	r=r*b;
	r=r/c;//
	return r;
}
/*
void baseline_vect_hoist_interchange( unsigned n , float * restrict a  , float * restrict b ,
float * restrict c , float * restrict d) //(const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d)
{
    // all elements in b are assumed positive
	unsigned k , i ;
	#pragma ivdep
	#pragma vector aligned
    for( i =0; i < n ; i ++)
    {
		if (b [ i ] < 1.0)
		{
			a[i]+=reduc_k_exp( b[i] , c[i] , d);
		}
		else
		{	
			a[i]+=reduc_k( b[i] , c[i] , d);
		}
    }
}
*/

void baseline_vect_hoist_interchange( unsigned n , float * restrict a  , float * restrict b ,
float * restrict c , float * restrict d) //(const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d)
{
    // all elements in b are assumed positive
	unsigned k , i ;
	#pragma ivdep
	#pragma vector aligned
	#pragma omp parallel for
    for( i =0; i < n ; i ++)
    {
		a[i]=a[i]*c[i];
		if (b [ i ] < 0.5)
		{
			#pragma ivdep
			#pragma vector aligned
			for ( k =0; k < 20; k ++) 
			{
				a [ i ] += exp ( b [ i ] + d [ k ]); // c [ i ];
			}
		}
		else
		{	
			#pragma ivdep
			#pragma vector aligned
			for ( k =0; k < 20; k ++) 
			{
					a [ i ] += ( b [ i ] * d [ k ]); // c [ i ];
			}
		}
		a[i]=a[i]/c[i];
    }
}

void baseline_vect ( unsigned n , float * restrict a  , float * restrict b ,
float * restrict c , float * restrict d) //(const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d)
{
    // all elements in b are assumed positive
    /*
	float *al=__builtin_assume_aligned(a,32);
	float *bl=__builtin_assume_aligned(b,32);
	float *cl=__builtin_assume_aligned(c,32);
	float *dl=__builtin_assume_aligned(d,32);
	
	*/ 
	unsigned k , i ;
    for ( k =0; k < 20; k ++)
    {
		#pragma ivdep
		#pragma  vector aligned
        for ( i =0; i < n ; i ++)
        {
            if (b [ i ] < 1.0)
            {
                a [ i ] += exp ( b [ i ] + d [ k ]) / c [ i ];
            } else
            {
                a [ i ] += ( b [ i ] * d [ k ]) / c [ i ];
            }
        }
    }
}


void baseline ( unsigned n , float a [ n ] , float b [ n ] ,
float c [ n ] , float d [20])
{
    unsigned k , i ;
    // all elements in b are assumed positive
    for ( k =0; k < 20; k ++)
    {
        for ( i =0; i < n ; i ++)
        {
            if ( b [ i ] >= 0.0 && b [ i ] < 1.0)
            {
                a [ i ] += exp ( b [ i ] + d [ k ]) / c [ i ];
            } else if ( b [ i ] >= 1.0)
            {
                a [ i ] += ( b [ i ] * d [ k ]) / c [ i ];
            }
        }
    }
}
