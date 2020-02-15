#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_PATHS 64
#define MAX_PATH_LEN 96
#define WHITESPACE " .,\t\n"

#ifndef NULL
#define NULL ...
#endif

struct command_t
{
  char *name;
  int argc=0;;
  char *argv[MAX_ARGS];
};
int printPrompt()
{
  /* Build the prompt string to have the machine name,
 * current directory, or other desired information.
 */
  char *promptString = (char *)"root@thsh> ";
  //printf("%s",promptString);
  return write(1, promptString, strlen(promptString));
}
int StartMessage()
{
  char *startString = (char *)"Kali Linux GNU/Linux Rolling [Version 10.0.17763.1039](c) 2018 Kali Linux. All rights reserved.";
  return write(1, startString, strlen(startString));
}

void readCommand(char *buffer)
{
  /* This code uses any set of I/O functions, such as those in the
 * stdio library to read the entire command line into the buffer. This
 * implementation is greatly simplified but it does the job.
 */
  //gets(buffer);
}

void parseCommand(char *commandLine, command_t&command)
{
  if(command.name)
    cout<<command.name<<endl;
  for (int i = 1; i <command.argc; i++)
  {
    cout<<command.argv[i]<<endl;
  }
  
}
//set path=(.:/bin:/usr/bin)
int parsePath(char *dirs[])
{
  /* This function reads the PATH variable for this
 * environment, then builds an array, dirs[], of the
 * directories in PATH
 */
  char *pathEnvVar;
  char *thePath;

  for (int i = 0; i < MAX_PATHS; i++)
    dirs[i] = NULL;
  pathEnvVar = (char *)getenv("PATH");
  thePath = (char *)malloc(strlen(pathEnvVar) + 1);
  strcpy(thePath, pathEnvVar);

  /* Loop to parse thePath. Look for a ":"
 * delimiter between each path name.
 */
  // for(int )

  //   return 0;//for now
  // }
  return 0;
}

char *lookupPath(char **argv, char **dir)
{
  /* This function searches the directories identified by the dir
 * argument to see if argv[0] (the file name) appears there.
 * Allocate a new string, place the full path name in it, then
 * return the string.
 */
  char *result;
  char pName[MAX_PATH_LEN];
  // Check to see if file name is already an absolute path
  if (*argv[0] == '/')
  {
    //do
  }
  // Look in PATH directories.
  // Use access() to see if the file is in a dir.
  for (int i = 0; i < MAX_PATHS; i++)
  {
  }
  // File name not found in any path variable
  fprintf(stderr, "%s: command not found\n", argv[0]);
  return NULL;
}
