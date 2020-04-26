#include <math.h>
#include <omp.h>
void baseline ( unsigned n , float a [ n ] , float b [ n ] ,
float c [ n ] , float d [20])
{
	#if BASELINE == 2
		unsigned k , i ;
		// all elements in b are assumed positive
		#if THREADS > 1
			omp_set_num_threads(THREADS);
			#pragma omp parallel for
		#endif
		for ( i =0; i < n ; i ++)
		{
			float temp = 0;
			#ifndef SIMPLECOND
				if ( b [ i ] >= 0.0 && b [ i ] < 1.0)
			#else
				if ( b [ i ] < 1.0)
			#endif
			{
				temp += exp ( b [ i ] + d [ 0 ]);
				temp += exp ( b [ i ] + d [ 1 ]);
				temp += exp ( b [ i ] + d [ 2 ]);
				temp += exp ( b [ i ] + d [ 3 ]);
				temp += exp ( b [ i ] + d [ 4 ]);
				temp += exp ( b [ i ] + d [ 5 ]);
				temp += exp ( b [ i ] + d [ 6 ]);
				temp += exp ( b [ i ] + d [ 7 ]);
				temp += exp ( b [ i ] + d [ 8 ]);
				temp += exp ( b [ i ] + d [ 9 ]);
				temp += exp ( b [ i ] + d [ 10 ]);
				temp += exp ( b [ i ] + d [ 11 ]);
				temp += exp ( b [ i ] + d [ 12 ]);
				temp += exp ( b [ i ] + d [ 13 ]);
				temp += exp ( b [ i ] + d [ 14 ]);
				temp += exp ( b [ i ] + d [ 15 ]);
				temp += exp ( b [ i ] + d [ 16 ]);
				temp += exp ( b [ i ] + d [ 17 ]);
				temp += exp ( b [ i ] + d [ 18 ]);
				temp += exp ( b [ i ] + d [ 19 ]);
			}
			#ifndef SIMPLECOND
				else if ( b [ i ] >= 1.0)
			#else
				else
			#endif
			{
				temp += ( b [ i ] * d [ 0 ]);
				temp += ( b [ i ] * d [ 1 ]);
				temp += ( b [ i ] * d [ 2 ]);
				temp += ( b [ i ] * d [ 3 ]);
				temp += ( b [ i ] * d [ 4 ]);
				temp += ( b [ i ] * d [ 5 ]);
				temp += ( b [ i ] * d [ 6 ]);
				temp += ( b [ i ] * d [ 7 ]);
				temp += ( b [ i ] * d [ 8 ]);
				temp += ( b [ i ] * d [ 9 ]);
				temp += ( b [ i ] * d [ 10 ]);
				temp += ( b [ i ] * d [ 11 ]);
				temp += ( b [ i ] * d [ 12 ]);
				temp += ( b [ i ] * d [ 13 ]);
				temp += ( b [ i ] * d [ 14 ]);
				temp += ( b [ i ] * d [ 15 ]);
				temp += ( b [ i ] * d [ 16 ]);
				temp += ( b [ i ] * d [ 17 ]);
				temp += ( b [ i ] * d [ 18 ]);
				temp += ( b [ i ] * d [ 19 ]);
			}
			a [ i ] += temp / c [ i ];
		}
	#elif BASELINE == 1
		unsigned k , i ;
		// all elements in b are assumed positive
		#if THREADS > 1
			omp_set_num_threads(THREADS);
			#pragma omp parallel for
		#endif
		for ( i =0; i < n; i ++)
		{
			float temp = 0;
			for ( k =0; k < 20 ; k ++)
			{
				#ifndef SIMPLECOND
					if ( b [ i ] >= 0.0 && b [ i ] < 1.0)
				#else
					if ( b [ i ] < 1.0)
				#endif
				{
					temp += exp ( b [ i ] + d [ k ]);
				}
				#ifndef SIMPLECOND
					else if ( b [ i ] >= 1.0)
				#else
					else
				#endif
				{
					temp += ( b [ i ] * d [ k ]);
				}
			}
			a [ i ] += temp / c [ i ];
		}
	#else
		unsigned k , i ;
		// all elements in b are assumed positive
		#if THREADS > 1
			omp_set_num_threads(THREADS);
			#pragma omp parallel for
		#endif
		for ( k =0; k < 20; k ++)
		{
			for ( i =0; i < n ; i ++)
			{
				#ifndef SIMPLECOND
					if ( b [ i ] >= 0.0 && b [ i ] < 1.0)
				#else
					if ( b [ i ] < 1.0)
				#endif
				{
					a [ i ] += exp ( b [ i ] + d [ k ]) / c [ i ];
				}
				#ifndef SIMPLECOND
					else if ( b [ i ] >= 1.0)
				#else
					else
				#endif
				{
					a [ i ] += ( b [ i ] * d [ k ]) / c [ i ];
				}
			}
		}
	#endif
}