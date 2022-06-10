#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid):pid_{pid}{
  hertz_ = sysconf(_SC_CLK_TCK);
  cpu_utilization_ = CpuUtilization();
  
}
// TODO: Return this process's ID
int Process::Pid() { 
  return pid_;
  //return 0; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  string line;
  string data;
  
  vector<string> all_tokens{};
  long uptime{};
  float total_time{};
  float seconds{};
  float cpu_usage{};

  std::ifstream stream(LinuxParser::kProcDirectory +    to_string(pid_) + LinuxParser::kStatFilename);

  if (stream.is_open()) { 
    getline(stream, line); 
    std::istringstream linestream(line); 
    while (linestream >> data) { 
			all_tokens.push_back(data);  
        }
    }
  
    u_time_ = stof(all_tokens[13]);
    s_time_ = stof(all_tokens[14]);
    cutime_ = stof(all_tokens[15]);
    cs_time_ = stof(all_tokens[16]);
    start_time_ = stof(all_tokens[21]);
    uptime = LinuxParser::UpTime();
    total_time = u_time_ + s_time_ + cutime_ + cs_time_;

    seconds = uptime - (start_time_ / hertz_);
    cpu_usage = (total_time / hertz_) / seconds;

    return cpu_usage;
    
  
  
  //return 0; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
return LinuxParser::Command(pid_);  
   
  //return string(); 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  return LinuxParser::Ram(pid_);
  
  
  //return string(); 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
   return LinuxParser::User(pid_);
  //return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
return LinuxParser::UpTime(pid_);  
  
  
  //return 0; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return a.cpu_utilization_ < this->cpu_utilization_;
  //return true;
  
  }