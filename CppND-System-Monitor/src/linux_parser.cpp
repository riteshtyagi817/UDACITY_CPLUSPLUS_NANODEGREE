#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stol;
using std::stoi;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  //doing work 
  string MemTotal {};
  float MemTotalValue{};
  string MemFree{};
  float MemFreeValue{};
  string line;
  string size{};
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> MemTotal >> MemTotalValue >> size;
        
  }
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> MemFree >> MemFreeValue >> size;
        
  }
  return ((MemTotalValue - MemFreeValue)/MemTotalValue);
  
}
  //return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime_{};
  
  string line;
  //long int val{};
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime_;
    
        
  }
  long uptime = stol(uptime_);
  
  return uptime;
}
  //return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
//long LinuxParser::ActiveJiffies(int pid) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  //int no_process{};
  string cpu_match{}; 
  string user{};
  string nice{};
  string system{};
  string idle{};
  string iowait{};
  string irq{};
  string softirq{};
  string steal{};
  string guest{};
  string guest_nice{};
  
  vector<string> output{};
   
  string line;
  //long int val{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()) {
    	std::getline(stream, line);
    	std::istringstream linestream(line);
    		while(linestream >> cpu_match >> user >> nice >> system >>  idle >> iowait >> 					  irq>> softirq >> steal >> guest >> guest_nice)
    			{
      				if(cpu_match == "cpu")
      				{
  						output.push_back(user);
  						output.push_back(nice);
  						output.push_back(system);
  						output.push_back(idle);
  						output.push_back(iowait);
  						output.push_back(irq);
  						output.push_back(softirq);
  						output.push_back(steal);
  						output.push_back(guest);
  						output.push_back(guest_nice);
  						return output;
        
         			}
       			}
  			}
   
  			return output;
  //return {};
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  //return 0; 
  int no_process{};
  string process_match{};
  string line;
  //long int val{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> process_match >> no_process;
    if(process_match == "processes")
    {
      return no_process;
    }
        
    
  }
  //return uptime;
  return 0;
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
 
  int no_process_running{};
  string process_match{};
  string line;
  //long int val{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> process_match >> no_process_running;
    if(process_match == "procs_running")
    {
      return no_process_running;
    }
        
    
  }
  
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  string command_line{};
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
        std::getline(stream, line); 
  		std::istringstream linestream(line);
    	linestream >> command_line;
    }
     return command_line;
  
  
  
  //return string(); 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
string line{};
string key{};
string data{};
int memory_value{};
std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
if (stream.is_open()) {
    while (std::getline(stream, line)){
          std::istringstream linestream(line);
              while (linestream >> key >> data) {
                   if (key == "VmSize:") {
                        memory_value = stoi(data)/1024;
                         return to_string(memory_value); 
              }
          }
      }
    } 
  return string();
  
  
  //return string(); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
   
  string key{};
  string line{};
  string uid_data{}; 
  
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
  		std::istringstream linestream(line);
    	while (linestream >> key >> uid_data) {
        	if (key == "Uid:") { return uid_data;}
        	}
      	}
    }
  return uid_data;
   
  //return string(); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
  string line{};
  string uid{};
  string userid{};
  string user_name{};
  string second{};
  uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
        std::replace(line.begin(), line.end(), ':', ' ');
  		std::istringstream linestream(line);
    	while (linestream >> user_name >> second >> userid) {
        	if (userid == uid) { return user_name;}
        	}
      	}
    }
  
  return string();
    
 // return string(); 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line{};
  vector<string> all_tokens{};
  string data{};
  long up_time{};
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename); 
  if (stream.is_open()) { 
    std::getline(stream, line); 
    std::istringstream linestream(line); 
    while (linestream >> data) { 
			all_tokens.push_back(data); 
        }
    }
  
    up_time = LinuxParser::UpTime() - stol(all_tokens[21]) / sysconf(_SC_CLK_TCK); 
  
  
   return up_time;
  
  
  //return 0; 
}
