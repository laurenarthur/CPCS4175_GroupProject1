
/* 
 *
 * This program will be launched in fork_execv (see fork_execv.c).
 *
 * Compilation Instruction: 
 * gcc process.c -o process
 * 
 * Reference: 
 * https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  //int seconds = (int) atoi(argv[0]);
  printf("Child: Sleeping for %s seconds\n", argv[0]);
  sleep((int)atoi(argv[0]));
  printf("Child: Done sleeping. Attempting to go back to parent process.\n");
  //exit(0);
}
