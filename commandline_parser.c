/*
 *
 * Compilation Instruction:
 * gcc commandline_parser.c -o commandline_parser
 * ./commandline_parser
 *
 */

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "queue.h"
#include "policies.h"
#include "global.h"

/* Error Code */
#define EINVAL       1
#define E2BIG        2

#define MAXMENUARGS  4 
#define MAXCMDLINE   64 

void menu_execute(char *line, int isargs); 
int cmd_run(int nargs, char **args); 
int cmd_quit(int nargs, char **args); 
void showmenu(const char *name, const char *x[]);
int cmd_helpmenu(int n, char **a);
int cmd_dispatch(char *cmd);

int cmd_fcfs();
int cmd_sjf();
int cmd_priority();

int cmd_list(int nargs);
int cmd_test(int nargs);

/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args) {
	if (nargs != 4) {
		printf("Usage: run <job> <time> <priority>\n");
		return EINVAL;
	}
        
        /* Use execv to run the submitted job in csubatch */
        printf("use execv to run the job in csubatch.\n");
      	return 0; /* if succeed */
}

/*
 * FCFS command 
 */
int cmd_fcfs(){
    return orderFCFS();
}

/*
 * SJF command
 */
int cmd_sjf(){
    return orderSJF();
}
 /*
 * Priority command 
 */
 int cmd_priority(){
    return orderPriority();
}

/*
 * The quit command.
 */
int cmd_quit(int nargs, char **args) {
	printf("Please display performance information before exiting csubatch!\n");
        exit(0);
}

/*
 * Display menu information
 */
void showmenu(const char *name, const char *x[])
{
	int ct, half, i;

	printf("\n");
	printf("%s\n", name);
	
	for (i=ct=0; x[i]; i++) {
		ct++;
	}
	half = (ct+1)/2;

	for (i=0; i<half; i++) {
		printf("    %-36s", x[i]);
		if (i+half < ct) {
			printf("%s", x[i+half]);
		}
		printf("\n");
	}

	printf("\n");
}

static const char *helpmenu[] = {
	"[run] <job> <time> <priority>       ",
	"[quit] Exit csubatch                 ",
	"[help] Print help menu              ",
        /* Please add more menu options below */
    "[list] Display the job status",
    "[fcfs] Change the scheduling policy to FCFS",
    "[sjf] Change the scheduling policy to SJF",
    "[priority] Change the scheduling policy to priority",
    "[test] <benchmark> <policy> <num_of_jobs> <priority_levels> <min_CPU_time> <max_CPU_time>",
	NULL
};

int cmd_helpmenu(int n, char **a)
{
	(void)n;
	(void)a;

	showmenu("csubatch help menu", helpmenu);
	return 0;
}

/*
 * The list command.
 */
int cmd_list(int nargs) {
	if(nargs != 1){
        //print list of jobs in the queue that are running and pending 
        return EINVAL;
    }
    print_number_jobs();
    printQueue();
    print_policy();
    return 0;
}

/*
 * The test command.
 */
int cmd_test(int nargs) {
	if(nargs != 4){
        //print what job it was on 
        printf("Usage: run <job> <time> <priority>\n");
        return EINVAL;
    }
    return 0;
}
/*
 *  Command table.
 */
static struct {
	const char *name;
	int (*func)(int nargs, char **args);
} cmdtable[] = {
	/* commands: single command must end with \n */
	{ "?\n",	cmd_helpmenu },
	{ "h\n",	cmd_helpmenu },
	{ "help\n",	cmd_helpmenu },
	{ "r",		cmd_run },
	{ "run",	cmd_run },
	{ "q\n",	cmd_quit },
	{ "quit\n",	cmd_quit },
        /* Please add more operations below. */
    {"l\n",	cmd_list },
	{ "list\n",	cmd_list },

    {"t\n",	cmd_test },
	{ "test\n",	cmd_test},
        {NULL, NULL}
};

/*
 * Process a single command.
 */
int cmd_dispatch(char *cmd)
{
	time_t beforesecs, aftersecs, secs;
	u_int32_t beforensecs, afternsecs, nsecs;
	char *args[MAXMENUARGS];
	int nargs=0;
	char *word;
	char *context;
 	int i, result;

	for (word = strtok_r(cmd, " ", &context);
	     word != NULL;
	     word = strtok_r(NULL, " ", &context)) {

		if (nargs >= MAXMENUARGS) {
			printf("Command line has too many words\n");
			return E2BIG;
		}
		args[nargs++] = word;
	}

	if (nargs==0) {
		return 0;
	}

	for (i=0; cmdtable[i].name; i++) {
		if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
			assert(cmdtable[i].func!=NULL);
            
            /* Call function through the cmd_table */
			result = cmdtable[i].func(nargs, args);
			return result;
		}
	}

	printf("%s: Command not found\n", args[0]);
	return EINVAL;
}

/*
 * Command line main loop.
 */
int main()
{
    policy = FCFS;

	char *buffer;
        size_t bufsize = 64;
        
        buffer = (char*) malloc(bufsize * sizeof(char));
        if (buffer == NULL) {
 		perror("Unable to malloc buffer");
 		exit(1);
	}

    printf("Welcome to Lauren and Sharon's batch job scheduler Version 1.0\n");
    printf("Type 'help' to find more about CSUbatch commands.\n");
 
    while (1) {
		printf("> [? for menu]: ");
		getline(&buffer, &bufsize, stdin);
		cmd_dispatch(buffer);
	}
        return 0;
}
