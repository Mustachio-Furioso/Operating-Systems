/*
 * driver.cxx
 * 
 * 	sample main program for virtual memory simulation
 * 
 */
#include <iostream>
using namespace std;

// header files of the related classes and data structure
#include "PhysicalMemory.h"
#include "PageTable.h"

// layout of the virtual memory
const char* virtualMemoryList[] =
	{ "main()", "load()", "tax()", "update()", "print()", "holding[]", "activity[]", "net[]"}; 	

// page reference ids
int runList[] = { 0, 1, 5, 0, 6, 7, 0, 3, 5, 7, 6, 0, 2, 3, 7 }; 			

int main() {
	cout << "Virtual memory simulation: (memory size 4, FIFO strategy)" << endl;

	// create instance of class PhysicalMemory: size 4, 1 for FIFO
	PhysicalMemory *pMem = new PhysicalMemory(4, 1);
	// create instance of PageTable, size 8
	PageTable pTable(pMem, 8);
	
	//for each item in the run list
	for(int i = 0; i < 15; i++) {
		
		//fetch the virtual index for the string item
		int virtualIdx = runList[i];

		cout << i+1 << ". access: " << virtualMemoryList[virtualIdx] << ", ";
		
		//reference the item at the specified virtual index
		pTable.reference(virtualIdx);
	}

	cout << "\nSimulation complete:\n";

	// print page contents
	cout << "Virtual page contents:\n";
	for (int i = 0; i < 8; i++)
		cout << i << ": " << virtualMemoryList[i] << endl;
	// print physical memory contents
	pMem->print();
	// print page table
	pTable.print();	
	cout << "Current page fault count: " << pTable.getFaults() << endl;
    return 0;
}

