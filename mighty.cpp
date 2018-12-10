#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
  ifstream inputFile;
  ofstream outputFile;
  if (argv[1] != NULL){
    inputFile.open(argv[1]);
  }
  else{
    cerr << "Usage: Missing argument. Requires input file and output file." << endl;
    exit(EXIT_FAILURE);
  }
  if (argv[2] != NULL){
    outputFile.open(argv[0]);
  }
  else{
    cerr << "Usage: Missing argument. Requires input file and output file." << endl;
    exit (EXIT_FAILURE);
  }

  if (inputFile.is_open()){
    int fd[2];
    if (pipe(fd) == -1){
      cerr << "pipe failed" << endl;
      exit(EXIT_FAILURE);
    }
    pit_t pid = fork();
    if (pid == -1){
      //failure
      cerr << "fork failed." << endl;
      exit(EXIT_FAILURE);
    }
    else if (pid==0){
      //child
      close(fd[0]);
    } 
    else{
      //parent
    }
  }
  else{
    cerr << "Error opening file. Input file may not exist." << endl;
  }
  return 0;
}
