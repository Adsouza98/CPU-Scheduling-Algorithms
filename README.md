Assignment: A2
Andre D'Souza
#: 0952594
March 16, 2022
Deadline: 03/16/22
Grace Period: 03/19/22
Extension: 03/26/22

############################ Folder Structure ##################################

/bin
  <Executables>
/docs
/include
  <.h>
    -> Header Files for all .c files
/src
  simcpu.c
    -> The Main Loop which calls FCFS Scheduling Algorithm or RR Scheduling Algo
  heapPriorityQueue.c
    -> Code for Priority Queue Heap used to keep track of Threads (Bursts)
      -> Inspired by GeeksForGeeks, but I basically had to rewrite most of the
         data structure, so I'm going to call it mine, but I will cite the source
         to show respects.
         (https://www.geeksforgeeks.org/priority-queue-using-binary-heap/)
  utilities.c
    -> Helper Functions
      -> modeCheck(): Checking Mode Selection
      -> getFileInput(): Parsing input File via STDIN (File Redirection)
      -> max(): Find the Max between two numbers
      -> min(): Find the Min between two numbers
      -> fcfs(): First-Come-First-Serve Scheduling Algorithm
      -> rr(): Round-Robin Scheduling Algorithm
    -> Debug Functions
      -> printFileInput(): Used to debug the input File Redirection
/Test
  -> Files used for Testing
.gitignore
  -> Simple gitignore file to not track changes I did not need to be tracked
Makefile
  -> To Compile and Run the Program
  -> I used -std=gnu11 to compile the program since this is not specified in the
     Assignment description I believe this is okay, I also tested it on the SOCS
     Servers and it ran fine
README.md
  -> If you're reading this its too late

########################## How To Compile The Program ##########################
"make"

############################ How to Run The Program ############################
"make run"

           ***NOTE*** *MUST COMPILE THE PROGRAM BEFORE TRYING TO RUN IT*
                        *(e.g. "make" then "make run")*

################## How to Remove Compiled Source Executables ###################
"make clean"
