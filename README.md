Operating-Systems
=================
NOTE: Linux-specific programs.
-----------------
ASSIGNMENT 1: 
 cpuinfo.cxx

<no issues>
-----------------
ASSIGNMENT2:
 myshell.cxx

-3: exit status for the child not given when an invalid command is given
-3: The exit status of the child is not given when a command with invalid arguments is provided
-----------------
ASSIGNMENT 3:
 setup.cxx
 writers.cxx
 readers.cxx

Compilation: 
g++ -lrt -pthread -std=c++11 -Wall setup.cxx -o setup
g++ -lrt -pthread -std=c++11 -Wall writers.cxx -o writers
g++ -lrt -pthread -std=c++11 -Wall readers.cxx -o readers

THEY NEED TO BE RUN INDIVIDUALLY IN THREE DIFFERENT CONSOLE WINDOWS.

setup needs to be run first as follows:
./setup [a number here]

then either writers or readers:
./writers
./readers

In case of core dumps:
rm /dev/shm/one.z1707589 /dev/shm/two.z1707589 /dev/shm/memory.z1707589

Grade:
-3: The reader should exit when it encounters a value of zero
-----------------
ASSIGNMENT 4:
 N/A - written assignment
-----------------
ASSIGNMENT 5:
 driver.cxx
 PageTable.cxx
 PageTable.h
 PhysicalMemory.cxx
 PhysicalMemory.h
 Makefile

Compilation: 
make

Notes:
Program was worked around existing driver.cxx (included) and Makefile. It was with time as a priority due to other deadlines. 

Grade:
Waiting
