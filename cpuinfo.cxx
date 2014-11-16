/********************************************
* Name: Edgar Sias
* ZID: z1707589
* Assignment: 1
* Due date: 9/12/14
* Date: 9/12/14
* Purpose: This program reports info about a 
*  running Linux system via ifstream.
********************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
   string buffer;   //string buffer used to hold data from file
   int upNum;       //integer buffer for uptime

/******* BEGIN HOSTNAME INFO ******/
   ifstream hostName;
   hostName.open("/proc/sys/kernel/hostname");
   hostName >> buffer;
   cout << "System information for: " << buffer << endl;
   hostName.close();
/******* END HOSTNAME INFO ********/

/********* BEGIN OS INFO **********/
   ifstream osType;
   osType.open("/proc/sys/kernel/ostype");
   osType >> buffer;
   cout << "OS: " << buffer << " ";
   osType.close();

   osType.open("/proc/sys/kernel/osrelease");
   osType >> buffer;
   cout << buffer << endl;
   osType.close();
/********** END OS INFO ***********/

/********* BEGIN CPU INFO *********/
   ifstream cpuFile;
   cpuFile.open("/proc/cpuinfo");
   while(!cpuFile.eof())
   {
      cpuFile >> buffer;
      if(buffer == "processor")
      {
         cpuFile >> buffer;
         cpuFile >> buffer;
         cout << "CPU " << buffer << ": ";
      }
      if(buffer == "name")
      {
         cpuFile >> buffer;
         while(buffer != "stepping")
         {
            cout << buffer << " ";
            cpuFile >> buffer;
         }
      }
      if(buffer == "cache")
      {
         cpuFile >> buffer;
         cpuFile >> buffer;
         cpuFile >> buffer;
         cout << "with " << buffer;
         cpuFile >> buffer;
         cout << " " << buffer << " cache" << endl;
      }
   }
   cpuFile.close();
/********** END CPU INFO **********/

/******* BEGIN MEMORY INFO ********/
   ifstream memInfo;
   memInfo.open("/proc/meminfo");
   memInfo >> buffer;
   memInfo >> buffer;
   cout << "memory physical: " << buffer << " KB";
   while(buffer != "SwapFree:")
   {
      memInfo >> buffer;
      if(buffer == "SwapTotal:")
      {
         memInfo >> buffer;
         cout << " + swap: " << buffer << " KB\n";
         break;
      }
   }
   memInfo.close();
/********* END MEMORY INFO ********/

/******* BEGIN PROCESS INFO *******/
   ifstream procs;
   procs.open("/proc/stat");
   while(buffer != "procs_running")
   {
      procs >> buffer;
   }
   procs >> buffer;
   cout << "number of processes running: " << buffer << endl;
   procs.close();
/******** END PROCESS INFO ********/

/******** BEGIN UPTIME INFO *******/
   ifstream upTime;
   upTime.open("/proc/uptime");
   upTime >> upNum;
   int days = upNum / 60 / 60 / 24;
   int hrs = (upNum / 60 / 60) % 24;
   int mins = (upNum / 60) % 60;
   int secs = upNum % 60;
   cout << days << " days, " << hrs << " hours, " << mins 
        << " minutes, " << secs << " seconds.\n";
   upTime.close();
/******** END UPTIME INFO *********/

   return 0;
 }

