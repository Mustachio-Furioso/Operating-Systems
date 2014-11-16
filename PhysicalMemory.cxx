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

#include "PhysicalMemory.h"

/*******************************************
* Function: Physical Memory
* Argument: N/A
* Task: this is the default constructor that 
*  sets algorithm and size to defaults. Also 
*  initializes fifo counter. 
*******************************************/
PhysicalMemory::PhysicalMemory()
{
	size = 4;
	algorithm = 1;
	fifo = 0;
}

/*******************************************
* Function: Physical Memory
* Argument: int _size, int _algorithm
* Task: this is the constructor which will set
*  the algorithm and size equal to the supplied
*  variables so long as they are valid, otherwise
*  they will be set to default values. Also 
*  initializes fifo counter. 
*******************************************/
PhysicalMemory::PhysicalMemory(int _size, int _algorithm)
{
	//set size, default 4
	if(_size > 0)
		size = _size;
	else 
		size = 4;

	//set algorithm, default 1 (fifo)
	if(_algorithm > 0 && algorithm < 2)
		algorithm = _algorithm;
	else 
		algorithm = 1;

	//fifo is initialized
	fifo = 0;
}

/*******************************************
* Function: store
* Argument: int pageID
* Task: this function will store the pageID
*  inside memory. If full, it will use the 
*  algorithm specified in the constructor to 
*  replace an existing variable. Returns the
*  accessed frame number. 
*******************************************/
int PhysicalMemory::store(int pageID)
{
	//if not full, push back until max size is hit
	if(memory.size() < (unsigned) size)
		memory.push_back(pageID);
	else
	{
		//fifo
		if(algorithm == 1)
		{
			if(fifo >= size) //reset fifo index
				fifo = 0;	
			memory[fifo] = pageID; //replace with pageID
			fifo++; //increase fifo index
		}
	}
	return access(pageID); //return frame number utilized
}

/*******************************************
* Function: access
* Argument: int pageID
* Task: this function will look for the given
*  pageID in the frames. If found, it will 
*  return the frame ID, otherwise it will 
*  return -1. 
*******************************************/
int PhysicalMemory::access(int pageID)
{
	int found = -1;
	for(unsigned int i = 0; i < memory.size(); i++)
	{
		if(memory[i] == pageID)
			found = i;
	}
	return found;
}

/*******************************************
* Function: getMember
* Argument: int index
* Task: this function will return the value
*  stored in frame ID index.
*******************************************/
int PhysicalMemory::getMember(int index)
{
	return memory[index];
}

/*******************************************
* Function: print
* Argument: 
* Task: this function will print the contents
*  of memory. 
*******************************************/
void PhysicalMemory::print()
{
	cout << "Content of Physical Memory:" << endl;
	for(unsigned int i = 0; i < memory.size(); i++)
		cout << i << ": page " << memory[i] << endl;
}

/*******************************************
* Function: getSize
* Argument: int index
* Task: this function will return the size
*  of memory. 
*******************************************/
int PhysicalMemory::getSize()
{
	return size;
}
