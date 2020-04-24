//
#define MAX_SAMPLES 1000

//
typedef unsigned long long u64;

//
typedef float  f32;
typedef double f64;

//
void sort(f64 *a, u64 n);

//Arithmetic mean
f64 mean(f64 *a, u64 n);

//Standard deviation
f64 stddev(f64 *a, u64 n);

//Array initialization
void init_array(u64 size, float *tab);
