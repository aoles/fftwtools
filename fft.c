#include<complex.h>
#include<fftw3.h>
#include"fft.h"

void fft_r2c(int* n, double* data, 
             double complex* res, int* retHermConj) {
   
   int i, nc = *n/2 +1;
   fftw_plan p;

   p = fftw_plan_dft_r2c_1d(*n, data, res, FFTW_ESTIMATE);

   fftw_execute(p);

   if(*retHermConj == 1) {
      for(i=nc; i < *n; i++) {
         res[i] = conj(res[*n - i]); 
      }
   }
      
   fftw_destroy_plan(p);
}

void fft_c2r(int* n, double complex* data, 
                double* res) {
   
   fftw_plan p;

   p = fftw_plan_dft_c2r_1d(*n, data, res, FFTW_ESTIMATE);

   fftw_execute(p);

   fftw_destroy_plan(p);
}


void fft_c2c(int* n, double complex* data, 
             double complex* res, int* inverse) {
   int sign;
   fftw_plan p;
   
   if(*inverse == 1) {
      sign = FFTW_BACKWARD;
   } else {
      sign = FFTW_FORWARD;
   }
   
   p = fftw_plan_dft_1d(*n, data, res, sign, FFTW_ESTIMATE);
   
   fftw_execute(p);

   fftw_destroy_plan(p);
}

void mvfft_r2c(int *n, int *m, double* data,
               double complex* res, int* fftwplanopt) {

   int nc = *n/2 +1;
   fftw_plan p; 

   if(*fftwplanopt == 1 ) {
       *fftwplanopt = FFTW_MEASURE;
   } else {
       *fftwplanopt = FFTW_ESTIMATE;
   }
      
   p = fftw_plan_many_dft_r2c(1, n,
                              *m, data,
                              NULL, 1,
                              *n, res,
                              NULL, 1,
                              nc, *fftwplanopt);

   fftw_execute(p);
   
   fftw_destroy_plan(p);
}


void mvfft_c2r(int *n, int *m, double complex* data,
               double* res, int* fftwplanopt) {
   
   int nc = *n/2 +1;
   fftw_plan p;
   
   if(*fftwplanopt == 1 ) {
       *fftwplanopt = FFTW_MEASURE;
   } else {
       *fftwplanopt = FFTW_ESTIMATE;
   }
    

   p = fftw_plan_many_dft_c2r(1, n,
                              *m, data,
                              NULL, 1,
                              nc, res,
                              NULL, 1,
                              *n, *fftwplanopt);

   fftw_execute(p);
   
   fftw_destroy_plan(p);
}

void mvfft_c2c(int *n, int *m, double complex* data,
               double complex* res, int* inverse, int* fftwplanopt) {

   int sign;
   fftw_plan p;
   
   if(*fftwplanopt == 1 ) {
       *fftwplanopt = FFTW_MEASURE;
   } else {
       *fftwplanopt = FFTW_ESTIMATE;
   }

   if(*inverse == 1) {
      sign = FFTW_BACKWARD;
   } else {
      sign = FFTW_FORWARD;
   }

   p = fftw_plan_many_dft(1, n,
                          *m, data,
                          NULL, 1,
                          *n, res,
                          NULL, 1,
                          *n, sign, *fftwplanopt);
   
   fftw_execute(p);
   
   fftw_destroy_plan(p);
}

void fft_r2c_2d(int* nx, int* ny, double* data, double complex* res) {

   fftw_plan p;
   
   p = fftw_plan_dft_r2c_2d(*nx, *ny, data, res,
                            FFTW_ESTIMATE);

   fftw_execute(p);

   fftw_destroy_plan(p);
} 


void fft_c2c_2d(int* nx, int* ny, double complex* data, 
                double complex* res, int* inverse) {

   int sign;
   fftw_plan p;
   
   if(*inverse == 1) {
      sign = FFTW_BACKWARD;
   } else {
      sign = FFTW_FORWARD;
   }
      
   p = fftw_plan_dft_2d(*nx, *ny, data, res,
                        sign, FFTW_ESTIMATE);

   fftw_execute(p);

   fftw_destroy_plan(p);
} 