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
  //parsePath(pathv);
  int finished = 0;
  if (!StartMessage())
    finished = 1;

  cout << endl
       << endl;
  while (!finished)
  {
    command_t command;
    char commandLine[MAX_INPUT];
    // Print the prompt
    if (!printPrompt())
    {
      finished = 1;
      break;
    }
    //read and parse the command
    if (!readAndParseCommand(commandLine, command))
    {
      finished = 1;
      break;
    }

    //print it for now
    testCommand(command);
    char *dirs[MAX_PATHS];
    parsePath(dirs);

    //parse the command
    //parseCommand(commandLine, command);

    // Execute the command, handling built-in commands separately
    // Just echo the command line for now
    //write(1, commandLine, strnlen(commandLine, MAX_INPUT));
  }

  return 0;
}
