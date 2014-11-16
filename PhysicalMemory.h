/*****************************************************
* Edgar Sias -  z1707589
* assignment05
* Due date: 11/14/14
* Date: 11/14/14
* This program  simulates a paging-based virtual memory system.
*
* This is the physical memory, which will map to and
*  store the ID of the accessing Page Table index. 
*****************************************************/
#ifndef PHYSICAL_HEADER
#define PHYSICAL_HEADER

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PhysicalMemory
{
   public:
	  PhysicalMemory();
	  PhysicalMemory(int _size, int _algorithm);
      int access(int pageID);
	  int store(int pageID);
      void print();
	  int getSize();
	  int getMember(int index);

   private:
      int size, algorithm, fifo;
	  vector<int> memory;
};

#endif
