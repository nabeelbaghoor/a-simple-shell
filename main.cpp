#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/* COMP 530: Tar Heel SHell */
#include <string.h>
#include "minishell.h"

using namespace std;
int main(int argc, char **argv, char **envp)
{
  int finished = 0;
  char *dirs[MAX_PATHS];
  //Clear();
  StartMessage();
  while (!finished)
  {
    command_t command;
    char commandLine[MAX_INPUT];
    // Print the prompt
    printPrompt();
    //read and parse the command
    if (!readAndParseCommand(commandLine, command))
    {
      finished = 1;
      break;
    }

    int total_paths = parsePath(dirs);
    char *filename = lookupPath(command.name, dirs, total_paths);

    int pid = fork();
    if(pid<0)
      cout<<"fork failed\n";
    if (pid == 0)
      execv(filename, command.argv);
    else
      wait(&pid);
  }

  return 0;
}
