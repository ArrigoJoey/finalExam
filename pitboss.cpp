#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){ 
  int opt;
  bool pflag=false;
  int percentage=0;
  ifstream inputFile;
  
  inputFile.open(argv[argc-1], ios::binary);
  if (inputFile.is_open()){
    while((opt = getopt(argc, argv, "p:")) != -1) {
      switch(opt){
      case 'p':
	pflag=true;
	percentage=atoi(optarg);
	if (percentage < 0 || percentage > 100){
	  cerr << "Invalid percentage. Must be 0-100." << endl;
	  exit(EXIT_FAILURE);
	}
	break;
      default: /* '?' */
	cerr << "Invalid option. Requires -p with valid percentage." << endl;
	exit(EXIT_FAILURE);
      }
    }
    if (pflag == false){
      cerr << "Option -p required." << endl;
      exit(EXIT_FAILURE);
    }
    int trials = 0;
    int successCount = 0;
    cout << "Reading results from " <<  argv[argc-1] << " ...\n" << endl;
    for(int i = 0; i < (percentage*100)-1000; i++){
      char j;
      inputFile.read(&j, sizeof(char));
    }
    for(int i = 0; i < 1000; i++){
      trials++;
      char j;
      inputFile.read(&j, sizeof(char));
      if (j == '1'){
	successCount++;
      }
    }
   
    cout << "Checking results for -p = " << percentage << " ...\n" << endl;
    cout << "Found " << trials << " trials.\n" << endl;
    
    double successPercent = 100.0*((double)successCount/(double)trials);
    cout << "Success - " << successPercent << "%" << endl;
    cout << "Failure - " << 100.0-successPercent << "%" << endl;
  }
  else{
    cerr << "Error opening file";
  }
  inputFile.close();
  return 0;
}
