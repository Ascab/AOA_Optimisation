#include <math.h>
#include <omp.h>

void baseline_vect_hoist_interchange_mem( unsigned n , float * restrict a  , float * restrict b ,
float * restrict c , float * restrict d) //(const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d)
{
    // all elements in b are assumed positive
	unsigned k , i ;
	float bi=0.0,ci=0.0,ai=0.0;
	#pragma ivdep
	#pragma vector aligned
  #if PARALLEL
	#pragma omp parallel for
  #endif
    for( i =0; i < n ; i ++)
    {
    ci=c[i];
		ai=a[i]*ci;
		bi=b[i];
		if (bi < 1.0)
		{
			#pragma ivdep
			#pragma vector aligned
			for ( k =0; k < 20; k ++)
			{
				ai += expf (d [ k ]); // c [ i ];
			}
			#pragma unroll_and_jam (5)
			a[i]=ai*expf(bi)/ci;
		}
		else
		{
			#pragma ivdep
			#pragma vector aligned
			for ( k =0; k < 20; k ++)
			{
				ai+= (d [ k ]); // c [ i ];
			}
			#pragma unroll_and_jam (5)
			a[i]=ai*bi/ci;
		}
    }
}

void baseline_vect_hoist_interchange( unsigned n , float * restrict a  , float * restrict b ,
float * restrict c , float * restrict d) //(const unsigned n , float * restrict a , float * restrict b , float * restrict c ,float * restrict d)
{
    // all elements in b are assumed positive
	unsigned k , i ;
	#pragma ivdep
	#pragma vector aligned
  #if PARALLEL
	#pragma omp parallel for
  #endif
    for( i =0; i < n ; i ++)
    {
		a[i]=a[i]*c[i];
		if (b [ i ] < 1)
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
