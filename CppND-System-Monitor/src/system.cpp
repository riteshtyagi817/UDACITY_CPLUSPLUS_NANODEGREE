#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include<iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;
using namespace LinuxParser;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<int>  all_process_id = LinuxParser::Pids();
  processes_.clear();
  for(auto pid:all_process_id)
  {
    	Process process(pid);
        processes_.push_back(process);
    
  }
  sort(processes_.begin(), processes_.end());
  
  return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel();
  //return string(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  
  return LinuxParser::MemoryUtilization();
  //return 0.0;
                                  }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
 return LinuxParser::OperatingSystem();
  //return string(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
  
  
  return LinuxParser::RunningProcesses();
  
  //return 0; 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  return LinuxParser::TotalProcesses();
  //return 0; 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
  //std::cout << LinuxParser::UpTime();
  //return 0;
  return LinuxParser::UpTime();
} 
  //return 0; }