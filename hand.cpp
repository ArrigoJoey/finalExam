#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <time.h>
#include <gsl/gsl_rng.h>

using namespace std;

int main(int argc, char *argv[]){
  gsl_rng * r = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(r,getpid());
  int a = gsl_rng_uniform_int(r,101);
  gsl_rng_free(r);
  int percentage;

  int opt = getopt(argc, argv, "p:v");
  while(opt != -1){
    if (opt == 'p'){
      percentage = atoi(optarg);
    }
    opt = getopt(argc, argv, "p:v");
  }
  
  if (a < percentage){
    return 1;
  }
  else{
    return 0;
  }
  
}
