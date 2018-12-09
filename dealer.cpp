#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]){
  int opt;
  int number_of_trials;
  int percentage;
  bool pflag = false;
  bool verbose = false;
  int successCount = 0;
  
  number_of_trials=atoi(argv[argc-1]);
  if (number_of_trials < 0){
    cerr << "number_of_trials must be nonnegative." << endl;
    exit(EXIT_FAILURE);
  }

  opt = getopt(argc, argv, "p:v");
  while (opt !=-1){
    switch (opt){
    case 'p':
      if (atoi(optarg) < 0 || atoi(optarg) > 100){
	cerr << "Invalid percentage. Must be 0-100." << endl;
	exit(EXIT_FAILURE);
      }
      pflag = true;
      percentage = atoi(optarg);
      break;
    case 'v':
      verbose = true;
      break;
    default: /* '?' */
      exit(EXIT_FAILURE);
    }
    opt = getopt(argc, argv, "p:v");
  }
  if (pflag == false || number_of_trials<=0){
    cerr << "Must include -p option" << endl << "Must include number of trials last" << endl;
    exit(EXIT_FAILURE);
  }

 for (int i = 0; i < number_of_trials; i++){
    pid_t pid = fork();
    int status;
    if (pid == -1){
      //failure
      cerr << "fork failed" << endl;
      exit(EXIT_FAILURE);
    }
    else if (pid == 0){
      //child
      execvp("./hand",argv);
      cerr << "exec failed" << endl;
      exit(0);
    }
    else{
      //parent
      int success;
      wait(&status);
      if (WIFEXITED(status)){
        success = WEXITSTATUS(status);
      }
      if (verbose == true){
	cout << "PID " << pid << " returned ";
      }
      if (success == 1){
	cout << "success" << endl;
	successCount++;
      }
      else{
	cout << "failure" << endl;
      }
    }
  }
  int successPercentage = 100*((double)successCount/(double)number_of_trials);
  cout << "\nCreated " << number_of_trials << " processes." << endl;
  cout << "Success - " << successPercentage << "%" << endl;
  cout << "Failure - " << 100-successPercentage << "%" << endl;
  return 0;
}
