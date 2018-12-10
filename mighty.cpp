#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[]){
  if (argv[1] == NULL){
    cerr << "Usage: Missing argument. Requires input file and output file." << endl;
    exit(EXIT_FAILURE);
  }
  if (argv[2] == NULL){
    cerr << "Usage: Missing argument. Requires input file and output file." << endl;
    exit (EXIT_FAILURE);
  }

  int fd[2];
  if (pipe(fd) == -1){
    cerr << "pipe failed" << endl;
    exit(EXIT_FAILURE);
  }
  pid_t pid = fork();
  if (pid == -1){
    //failure
    cerr << "fork failed." << endl;
    exit(EXIT_FAILURE);
  }
  else if (pid==0){
    //child
     close(fd[0]);
     dup2(fd[1], 1);

     execl("/bin/cat","cat","-b",argv[1],(char*)0);
     cerr << "Exec failed" << endl;
  } 
  else{
    //parent
     close(fd[1]);
     int outFd;
     outFd = open(argv[2],O_WRONLY | O_CREAT | O_CREAT, 0700);
     if (outFd < 0){
       cerr << "Failed to open file " << argv[2] << endl;
       exit(1);
     }
     char buf;
     while (read(fd[0], &buf, 1) > 0){
       write(1, &buf, 1);
       write(outFd, &buf, 1);
     }  
     close(fd[0]);
     close(outFd);
  }
  return 0;
}
