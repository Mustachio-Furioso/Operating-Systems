/*****************************************************
* Edgar Sias -  z1707589
* assignment05
* Due date: 11/14/14
* Date: 11/14/14
* This program  simulates a paging-based virtual memory system.
*
* This is the page table, which will map to the physical
*  memory.
*****************************************************/
#include <iostream>
#include <string>
#include "PhysicalMemory.h"

using namespace std;

class PageTable
{
   public:
      PageTable(PhysicalMemory* _temp, int _size);
      void reference(int pageID);
      void print();
      int getFaults();

   private:
      int size, faults;
	  PhysicalMemory* pm;
	  vector<string> table;
};
