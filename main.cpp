#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

using namespace std;
int main(int argc, char **argv, char **envp)
{
  int finished = 0;
  char *dirs[MAX_PATHS];
  int total_paths = parsePath(dirs);
  Clear();
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
    /* Get the full pathname for the file */
    command.name = lookupPath(command.argv[0], dirs, total_paths);
    if (command.name == NULL)
    {
      write(1, "unexpected error has occured!", 28);
      break;
    }
    int pid = fork();
    if (pid < 0)
      cout << "fork failed\n";
    if (pid == 0)
      execv(command.name, command.argv);
    else
      wait(&pid);
  }

  return 0;
}
