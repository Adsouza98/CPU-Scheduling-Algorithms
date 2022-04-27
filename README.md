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
  -> To ***Only Compile The Program***
  -> I tried to get command line arguments to work with the Makefile, but it was
     having trouble with the '<' File Redirection parameter, Make thought it was
     a parameter for the make program instead of my program ./simcpu
README.md
  -> If you're reading this its too late

########################## How To Compile The Program ##########################
"make"

############################ How to Run The Program ############################
"cd bin"
"./simcpu [-d] [-v] [-r quantum] < input_file"

           ***NOTE*** *MUST COMPILE THE PROGRAM BEFORE TRYING TO RUN IT*
        *(e.g. "make" then change directory to bin folder to run the program)*

As stated in the folder structure segment, I had trouble dealing with file
redirection with the Makefile, so in order to run the program without problems.
Please use the ***make*** command in the base folder to compile the program
then **Change Directory** to the bin folder (***cd bin***) in order to run the
program with the flags of your choice.

################## How to Remove Compiled Source Executables ###################
"make clean"

############################## About the Program ###############################
To my knowledge there are no bugs in the program, although for the Verbose Mode
it prints the Time in the order of the Ready Queue then runs the current ready
Thread Burst.

For example:
$ ./simcpu -v < test.txt
At Time 0: Thread 1 of Process 1 moves from new to ready
At Time 0: Thread 1 of Process 1 moves from ready to running
At Time 10: Thread 1 of Process 1 moves from running to terminated
At Time 0: Thread 1 of Process 2 moves from new to ready
At Time 17: Thread 1 of Process 2 moves from ready to running
At Time 117: Thread 1 of Process 2 moves from running to terminated
At Time 5: Thread 2 of Process 1 moves from new to ready

The program knows the time it happens but since I did not want to use future
information I let the loop run its course and print it when it actually happens
in the loop.

If No quantum number is provided the program will interpret it as invalid input
and exit the program, the quantum number should be the last argument before
the file redirection as stated in the Assignment Description.

############################ Extension to 03/26/22 #############################
I emailed the Professor a week before the deadline asking for an extension
because of my ENGG*41X Capstone Project work load. She gave me a 1 week extension.
She did not specify a date in the email only an extension of 1 week, so I
interpreted as 1 week from the grace-period, which is 03/26/22.

I interpreted this way because of the discord channel as other students said it
was 1 week from the grace-period date. I did not choose to email the professor
again to verify because at the time she was receiving many regrade requests from
other students about A1.

By looking at the Git History section you can see I completed the assignment in
about 3 days, so I didn't need a lot of time to complete the assignment, its just
that I am so busy with 41X right now that my time had to be allocated to my Final
Engg. Design course.

I hope this assumption I made is okay and valid.

P.S:
My capstone project is an automated (unintrusive) shopping cart prototype that
uses the traveling salesman algorithm to traverse a common grocery store without
the need of cameras.
Here's a video of my Capstone update if you are interested in it:
https://youtu.be/qEqmThmMtkU

################################# Git History ##################################
* 9d5e1e1 2022-03-25 | Cleaned up Code added Comments (HEAD -> master) [Andre D'Souza]
* c3c3bfb 2022-03-25 | Updated README.md file (HEAD -> master) [Andre D'Souza]
* 7f99298 2022-03-25 | Completed Assignment - Added File Redirection and Mode Selection via CLI [Andre D'Souza]
* 0bd1706 2022-03-25 | Completed Round Robin [Andre D'Souza]
* cd93e92 2022-03-24 | Completed FCFS Problem [Andre D'Souza]
* 10c2a06 2022-03-16 | Created Assignment Framework, File input can be read correctly, created Framework for Heap Priority Queue [Andre D'Souza]
