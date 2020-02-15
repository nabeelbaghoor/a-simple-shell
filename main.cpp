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
// Assume no input line will be longer than 1024 bytes
#define MAX_INPUT 1024
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
    char *cursor;
    char *parser; //=new char[LINE_LEN];
    char last_char;
    int rv;
    int count;
    int oldCount = 0;
    // Print the prompt
    if (!printPrompt())
    {
      finished = 1;
      break;
    }

    // read the input and parse the command
    for (rv = 1, count = 0,
        cursor = commandLine, last_char = 1, parser = commandLine;
         rv && (count < (MAX_INPUT - 1)) && (last_char != '\n');
         cursor++, count++)
    {

      rv = read(0, cursor, 1);
      last_char = *cursor;
      if (last_char == ' ' || last_char == '\n')
      {
        if (command.argc == 0)
        {
          command.name = new char[count + 1];
          strncpy(command.name, parser, count);
          //command.name[count]='/0';
        }
        else
        {
          command.argv[command.argc] = new char[count - oldCount];
          strncpy(command.argv[command.argc], parser, count - oldCount - 1);
          //command.argv[command.argc++][count-oldCount-1]='/0';
        }
        command.argc++;
        parser = cursor+1;
        oldCount = count; //except space
      }
    }
    *cursor = '\0';
    if (!rv)
    {
      finished = 1;
      break;
    }
    //parse the command
    parseCommand(commandLine, command);
    // Execute the command, handling built-in commands separately
    // Just echo the command line for now
    //write(1, commandLine, strnlen(commandLine, MAX_INPUT));
  }

  return 0;
}
