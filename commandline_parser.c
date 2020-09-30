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
#include "global.h"
#include "scheduling.h"
#include "parser.h"

/* Error Code */
#define EINVAL       1
#define E2BIG        2

#define MAXMENUARGS  4 
#define MAXCMDLINE   64 

void menu_execute(char *line, int isargs); 
int cmd_run(int nargs, char **args); 
int cmd_quit(int nargs, char **args); 
void showmenu(const char *x[]);
int cmd_helpmenu(int n, char **a);
int cmd_dispatch(char *cmd);

int cmd_fcfs(int nargs);
int cmd_sjf(int nargs);
int cmd_priority(int nargs);

int cmd_list(int nargs);
int cmd_test(int nargs);

/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args) {
	if (nargs != 4 && nargs != 3) {
		printf("Usage: run <job> <time> <priority>\" specify the time and priority.\n");
        printf("Usage: \"run <job> <time>\" to specify the time. Priority will be set to 1.\n");
		return EINVAL;
	}

    Node *newNode = (Node*) malloc(sizeof(Node));
    printf("Job %s was submitted.\n", args[1]);

    print_policy();
    newNode->name = (char*) malloc(strlen(args[1]) + 1);
    strcpy(newNode->name, args[1]);
    newNode->jobTime = (int) atoi(args[2]);

    if (nargs == 3){
        newNode->jobPriority = 1;
    }
    else{
        newNode->jobPriority = (int) atoi(args[3]);
    }
        
        enQueue(newNode);
        print_num_jobs();
      	return 0; /* if succeed */
}

/*
 * FCFS command 
 */
int cmd_fcfs(int nargs){
    if(nargs != 1){
        printf("The \"FCFS\" command does not accept any flags.\n");
        return EINVAL;
    }
    
    return orderFCFS();
}

/*
 * SJF command
 */
int cmd_sjf(int nargs){
    if (nargs != 1){
        printf("The \"SJF\" command does not accept any flags.\n");
        return EINVAL;
    }
    return orderSJF();
}
 /*
 * Priority command 
 */
 int cmd_priority(int nargs){
     if(nargs != 1){
         printf("The \"Prioritty\" command does not accept any flags.\n");
         return EINVAL;
     }
    return orderPriority();
}

/*
 * The quit command.
 */
int cmd_quit(int nargs, char **args) {
    if(nargs != 1){
        printf("The \"quit\" command does not accept any flags.\n");
        return EINVAL;
    }
	printf("Please display performance information before exiting csubatch!\n");
        exit(0);
}

/*
 * Display menu information
 */
void showmenu(const char *x[])
{
	int ct, half, i;

	printf("\n");
	//printf("%s\n", name);
	
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
    if(n==1){
        showmenu(helpmenu);
    }
    else if(n>2){
        printf("Can only accept one flag at a time\n");
        printf("Acceptable flags:\"-fcfs\", \"-help\", \"-list\", \"-priority\", \"-quit\", \"-run\", \"-sjf\", \"-test\"\n");
    }
    else{
        if(a[1][0] == "-"){
            showmenu(helpmenu);
        }
        else{
            printf("\"%s\" is not a valid flag. All flag starts with a hyphen ('-').\n", a[1]);
        }
    }
	return 0;
}

/*
 * The list command.
 */
int cmd_list(int nargs) {
	if(nargs != 1){
        //print list of jobs in the queue that are running and pending
        printf("The\"list\" command does not accept any flags.");
        return EINVAL;
    }
    print_num_jobs();
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
	{ "?",	cmd_helpmenu },
	{ "h",	cmd_helpmenu },
	{ "help",	cmd_helpmenu },
	{ "r",		cmd_run },
	{ "run",	cmd_run },
	{ "q",	cmd_quit },
	{ "quit",	cmd_quit },
        /* Please add more operations below. */
    {"l",	cmd_list },
	{ "list",	cmd_list },

    {"t",	cmd_test },
	{ "test",	cmd_test},
    {"FCFS", cmd_fcfs},
    {"fcfs", cmd_fcfs},
    {"SJF", cmd_sjf},
    {"sjf", cmd_sjf},
    {"priority", cmd_priority},
    {"p", cmd_priority},
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
        if(strcmp(word, " ")!= 0 && strcmp(word, "\n") !=0){
            args[nargs++] = word;
        }
	}

	if (nargs==0) //if nothing was entered 
    {
		return 0;
	}
    for(i=0; i<nargs;i++){
        args[i] = strtok(args[i], "\n");
    }
    //iterates through the commans table to see if the "cmd" wntered is a valid command 
	for (i=0; cmdtable[i].name; i++) {
		if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
			assert(cmdtable[i].func!=NULL);
            
            /* Call function through the cmd_table */
			result = cmdtable[i].func(nargs, args);
			return result;
		}
	}
    //Command not found 
	printf("%s: Command not found\n", args[0]);
	return EINVAL;
}

/*
 * Command line main loop.
 */
int parse()
{
    job_queue=initializeQueue();
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
        printf("\n");
	}
        return 0;
}
