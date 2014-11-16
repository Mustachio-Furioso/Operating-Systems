/*****************************************************
* Edgar Sias -  z1707589
* assignment03
* Due date: 10/10/14
* Date: 10/10/14
* This program runs reader and writers routines simultaneously 
*  using threads. 
* This is the setup, which initializes the shared memory 
*  and the semaphore status. Also cleans up memory after 
*  user terminates program.
*****************************************************/
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <semaphore.h>
#include <iostream>
using namespace std;

// shared memory structure: used by producer and consumer
#include "common.h"

int main(int argc, char *argv[])
{
  int shm_fd = shm_open("/memory.z1707589", O_CREAT | O_RDWR, 0666);
  int size = sizeof(shm_mem_struct);
  ftruncate(shm_fd, size);

  //memory map the shared memory
  shm_mem_struct *shm_ptr = (shm_mem_struct *)mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  //create semaphores
  sem_t *one = sem_open("/one.z1707589", O_CREAT, 0666, 1);
  sem_t *two = sem_open("/two.z1707589", O_CREAT, 0666, 0);

  //initialize shared memory counters
  sem_wait(one);
  shm_ptr->value = strtol(argv[1],NULL,10);
  sem_post(one);

  cout << "done initializing shared memory\n";

  // wait until user wants to end
  cout << "Press Enter to exit ";
  cin.get();

  // delete shared memory
  shm_unlink("/memory.z1707589");
  // close and delete semaphores
  sem_close(one);
  sem_close(two);
  sem_unlink("/one.z1707589");
  sem_unlink("/two.z1707589");

  return 0;
}


