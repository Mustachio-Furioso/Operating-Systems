/*****************************************************
* Edgar Sias -  z1707589
* assignment03
* Due date: 10/10/14
* Date: 10/10/14
* This program runs reader and writers routines simultaneously 
*  using threads. 
* This is the reader, which prints the data inside the 
*  shared memory so long as it is not currently in use
*  by the writer. It runs four indentical threads.
*****************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <iostream>
#include <pthread.h>
using namespace std;

// shared memory structure: used by producer and consumer
#include "common.h"

/*******************************************
* Function: reader
* Argument: num
* Task: this function reads from shared memory
*  and interacts with the writer via semaphores
*******************************************/
void *reader(void *num)
{
  // open shared memory object
  int shm_fd = shm_open("/memory.z1707589", O_RDWR, 0666);

  // memory map the shared memory
  int size = sizeof(shm_mem_struct);
  shm_mem_struct *shm_ptr = (shm_mem_struct *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  // open semaphores
  sem_t *one = sem_open("/one.z1707589", O_RDWR);
  sem_t *two = sem_open("/two.z1707589", O_RDWR);

  // let the consumer consume
  while(shm_ptr->value >= 0)
  {
    if(shm_ptr->value < 0)
      break;
    sem_wait(two);
    cout << "Reader thread R" << (char *) num << " reads value: " << shm_ptr->value << endl;
    sem_post(one);
  }
}

//main - runs 4 threads using reader()
int main()
{
  pthread_t t1, t2, t3, t4; // thread ids
  
  // construct & run new threads
  pthread_create(&t1, NULL, reader, (char *) "1");
  pthread_create(&t2, NULL, reader, (char *) "2");
  pthread_create(&t3, NULL, reader, (char *) "3");
  pthread_create(&t4, NULL, reader, (char *) "4");

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);

  return 0;
}


