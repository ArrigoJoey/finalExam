#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <gsl/gsl_rng.h>

using namespace std;

int main(int argc, char *argv[]){
  int opt;
  int points = 10;
  while ((opt = getopt(argc, argv, "p:")) != -1){
    switch(opt){
    case 'p':
      points = atoi(optarg);
      break;
    default: /* '?' */
      cerr << "Unrecognized option" << endl;
      exit(EXIT_FAILURE);
    }
  }

  gsl_rng * r = gsl_rng_alloc(gsl_rng_mt19937);
  int inCircle = 0;
  for (int i = 0; i < points; i++){
    gsl_rng_set(r,time(NULL)*(i+2)*(i+2));
    double x = gsl_rng_uniform(r);
    gsl_rng_set(r,time(NULL)*(i+2)*(i+2)*(i+2));
    double y = gsl_rng_uniform(r);
    double dist = sqrt((x*x) + (y*y));
    if (dist <= 1.0){
      inCircle++;
    }
  }
  double pi = 4*((double)inCircle/(double)points);
  cout << "pi = " << pi << endl;
  gsl_rng_free(r);
}
