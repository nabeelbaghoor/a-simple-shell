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
#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif /* _COLORS_ */
// Assume no input line will be longer than 1024 bytes
#define MAX_INPUT 1024
#ifndef NULL
#define NULL ...
#endif

struct command_t
{
  char *name;
  int argc = 0;
  char *argv[MAX_ARGS];
};
void printPrompt()
{
  /* Build the prompt string to have the machine name,
 * current directory, or other desired information.
 */
  char cwd[MAX_INPUT];
  getcwd(cwd, sizeof(cwd));
  //printf("%s",cwd);
  strcat(cwd, "# ");
  write(1, "root@dash: ", 11);
  write(1, cwd, strlen(cwd));
  // cout << BOLD(FRED("root@dash: "));
  // cout << cwd;
  // cout << BOLD(FBLU("# "));
}
void Clear()
{
  system("/bin/clear");
}
void StartMessage()
{
  //
  cout << BOLD(FGRN("Kali Linux GNU/Linux Rolling [Version 10.0.17763.1039](c) 2018 Kali Linux.All rights reserved."))
       << endl;
}

int readAndParseCommand(char *commandLine, command_t &command)
{
  char *cursor;
  char *parser;
  char last_char;
  int rv;
  int count;
  int oldCount = -1;

  // read the input and parse the command
  for (rv = 1, count = 0,
      cursor = commandLine, last_char = 1, parser = commandLine;
       rv && (count < (MAX_INPUT - 1)) && (last_char != '\n');
       cursor++, count++)
  {

    rv = read(0, cursor, 1);
    last_char = *cursor;
    if ((last_char == ' ' || last_char == '\n') && *parser != '\n')
    {
      if (*parser == ' ')
      {
        parser++;
        count--;
      }
      else
      {
        command.argv[command.argc] = new char[count - oldCount];
        strncpy(command.argv[command.argc], parser, count - oldCount - 1);

        command.argc++;
        parser = cursor + 1;
        oldCount = count;
      }
    }
  }
  command.argv[command.argc] = NULL;
  *cursor = '\0';
  return rv;
  /* This code uses any set of I/O functions, such as those in the
 * stdio library to read the entire command line into the buffer. This
 * implementation is greatly simplified but it does the job.
 */
  //gets(buffer);
}

void parseCommand(char *commandLine, command_t &command)
{
}
void testCommand(command_t &command)
{
  for (int i = 0; i < command.argc; i++)
    cout << command.argv[i] << endl;
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
  int index = 0;
  char *cursor;
  char *parser; //=new char[LINE_LEN];
  char last_char;
  int count;
  int oldCount = -1;

  // read the input and parse the command
  for (count = 0,
      cursor = thePath, last_char = 1, parser = thePath;
       count < strlen(thePath) + 1;
       cursor++, count++)
  {
    last_char = *cursor;
    if ((last_char == ':' || last_char == '\0') && *parser != '\0')
    {
      if (*parser == ':')
      {
        parser++;
        count--;
      }
      else
      {
        dirs[index] = new char[count - oldCount];
        strncpy(dirs[index], parser, count - oldCount - 1);
        index++;
        parser = cursor + 1;
        oldCount = count;
      }
    }
  }
  *cursor = '\0';
  return index;
}
//char *lookupPath(char **argv, char **dir)
char *lookupPath(char *filename, char *dir[], int total_paths) //changed
{
  /* This function searches the directories identified by the dir
 * argument to see if argv[0] (the file name) appears there.
 * Allocate a new string, place the full path name in it, then
 * return the string.
 */
  if (filename && dir) //check if null
  {
    //char *result;
    char *pName = new char[MAX_PATH_LEN];
    // Check to see if file name is already an absolute path
    if (*filename == '/')
    {
      if (!access(filename, F_OK))
        return filename;
    }
    else
    {
      // Look in PATH directories.
      // Use access() to see if the file is in a dir.
      for (int i = 0; i < total_paths; i++)
      {
        strcpy(pName, "");
        strcpy(pName, dir[i]);
        strcat(pName, "/");
        strcat(pName, filename);
        //cout << pName << endl;
        // cout<<"!access(pName, F_OK)"<<access(pName, F_OK)<<endl;
        if (!access(pName, F_OK))
          return pName;
      }
      // File name not found in any path variable
    }
    fprintf(stderr, "%s: command not found\n", filename);
  }
  return NULL;
}
