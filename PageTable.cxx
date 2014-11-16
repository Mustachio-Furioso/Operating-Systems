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

#include "PageTable.h"
#include <sstream>

/*******************************************
* Function: PageTable
* Argument: PhysicalMemory* _pm, int _size
* Task: this is the constructor which will set
*  the size of the table and provide a pointer
*  to the physical memory being mapped. It will
*  also initialize the number of faults. 
*******************************************/
PageTable::PageTable(PhysicalMemory* _pm, int _size)
{
	pm = _pm;
	size = _size;
	faults = 0;

	//pad table with "empty"
	for(int i = 0; i < size; i++)
		table.push_back("empty");
}

/*******************************************
* Function: getFaults
* Argument: 
* Task: this function will return the value of
*  faults. 
*******************************************/
int PageTable::getFaults()
{
	return faults;
}

/*******************************************
* Function: reference
* Argument: int PageID
* Task: this function will store tableIDs in
*  memory and will update the table contents,
*  including page faults. 
*******************************************/
void PageTable::reference(int pageID)
{
	int found = pm->access(pageID);
	//if the value is found in memory, print where it's found
	if(found != -1)
		cout << "accessed in frame: " << found << endl;
	//if it is not, then store in memory and update the table 
	else
        {
		found = pm->access(pageID); //get where it is now stored
		faults++; //page fault

		//printable found
		stringstream ss;
		ss << found;
		string strFound = ss.str();

		//string strFound = to_string(static_cast<long long>(found)); //printable found
		string compare = "stored in frame:" + strFound; //comparable entry
		for(unsigned int i = 0; i < table.size(); i++) //update table, delete old value
			if(table[i] == compare)
				table[i] = "<swapped out>";
		table[pageID] = "stored in frame:" + strFound; //update table with new value
		cout << "page fault, now stored in frame: " + strFound << endl; //print
	}
}

/*******************************************
* Function: print
* Argument: 
* Task: this function will print the contents
*  of the table. 
*******************************************/
void PageTable::print()
{
	cout << "Content of Page Table:" << endl;
	for(unsigned int i = 0; i < table.size(); i++)
		cout << i << ". " << table[i] << endl;
}
