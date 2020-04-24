#include <math.h>
#include <stdlib.h>

#include "common.h"

//
void sort(f64 *a, u64 n)
{
  for (u64 i = 0; i < n; i++)
    for (u64 j = i + 1; j < n; j++)
      if (a[i] > a[j])
	{
	  f64 tmp = a[i];

	  a[i] = a[j];
	  a[j] = tmp;
	}
}

//Arithmetic mean
f64 mean(f64 *a, u64 n)
{
  f64 m = 0.0;

  for (u64 i = 0; i < n; i++)
    m += a[i];

  m /= (f64)n;
  
  return m;
}

//Standard deviation
f64 stddev(f64 *a, u64 n)
{
  f64 d = 0.0;
  f64 m = mean(a, n);

  //
  for (u64 i = 0; i < n; i++)
    d += (a[i] - m) * (a[i] - m);

  d /= (f64)(n - 1);
  
  return sqrt(d); 
}

//Array initialization
void init_array(u64 size, float *tab )
{
    int i ;
    for (i = 0 ; i < size ; i++)
    {
        tab[i] = 2.0 * (float)(rand()) / RAND_MAX;
    }
}
