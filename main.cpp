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
  char *dirs[MAX_PATHS];
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

    //print it for now
    int total_paths = parsePath(dirs);
    const char *filename = lookupPath(command.name, dirs, total_paths);
    //cout << "result2:" << filename << endl;

    // char *arr[] = {"ls", "-l", "-R", "-a", NULL};
    // execv("/bin/ls", arr);
    //char *arguments[] = {"ls", "-l", "-R", "-a", NULL};
    int pid = fork();
    // execv(filename,command.argv);
    if (pid== 0)
    {
      //char *arr[] = {"ls", "-l", "-R", "-a", NULL};
      execv("filename", command.argv);
    }
    // for (int i = 0; i < total_paths+1; i++)
    // {
    //   cout << dirs[i] << endl;
    // }

    //testCommand(command);

    //parse the command
    //parseCommand(commandLine, command);

    // Execute the command, handling built-in commands separately
    // Just echo the command line for now
    //write(1, commandLine, strnlen(commandLine, MAX_INPUT));
  }

  return 0;
}
