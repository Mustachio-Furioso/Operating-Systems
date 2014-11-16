# make file for virtual memory simulation assignment
CC=g++
CFLAGS=-c -Wall
HEADERS=PhysicalMemory.h PageTable.h
OBJECTS=driver.o PhysicalMemory.o PageTable.o
	
driver: $(OBJECTS) 
	$(CC) $(OBJECTS) -o driver

%.o: %.cxx $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o driver

