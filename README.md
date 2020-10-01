# CPCS4175_GroupProject1

Title: Project 1: CSU batch 
Members: Lauren Arthur and Sharon Deloach 

Configuration Instructions:

  Compile:
    gcc process.c -o process
    gcc batch.c commandline_parser.c queue.c scheduling.c dispatching.c -o main
    clear
    

Installations Instructions:
  
  Make sure to do the step to compile above. Also this is all in the makefile.
  
  run:
    ./main

Operating Instructions:
  
  To began you can type help or ? to get all the commands you will neeed to run the scheduler. 
  Run jobs by using the command run <job> <time> <pri> :
    <job> submit a job name,
    <time> execution time,
    <pri> priority.
