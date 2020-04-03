#include <math.h>

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
