#include "processor.h"
#include "linux_parser.h"
#include<iostream>
#include<vector>
#include<string>
#include<bits/stdc++.h>
using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> output1{}; 
  output1 = LinuxParser::CpuUtilization();
  float cpu_percentage_{};
  /* in the  ncurses display it is calling multiple times so no need to call here 2 times */
  
  
  float user_ = stof(output1[0]);
  float nice_ = stof(output1[1]) ;
  float system_ = stof(output1[2]);
  float idle_   = stof(output1[3]);
  float iowait_   = stof(output1[4]);
  float irq_ = stof(output1[5]);
  float softirq_  = stof(output1[6]); 
  float steal_ = stof(output1[7]);
  //float guest_ = stof(output1[8]);
  //float  guest_nice_ = stof(output1[9]);
  
  
  float prev_idle = prev_idle_ + prev_iowait_;
  float idle = idle_ + iowait_;
  
  float prev_non_idle = prev_user_ + prev_nice_ + prev_system_ + prev_irq_ + prev_softirq_ + prev_steal_;
  float non_idle = user_ + nice_ + system_ + irq_ + softirq_ + steal_;

  float prev_total = prev_idle + prev_non_idle;
  float  total_ = idle + non_idle;

  float  total_d  = total_ - prev_total;
  float idle_d = idle - prev_idle;

  cpu_percentage_ = (total_d - idle_d)/total_d;
  
  //cout << cpu_percentage_<< endl;
  prev_user_ = user_;
  prev_nice_ = nice_;
  prev_system_ = system_;
  prev_idle_   = idle_;
  prev_iowait_   = iowait_;
  prev_irq_ = irq_;
  prev_softirq_  = softirq_; 
  prev_steal_ = steal_;
  //prev_guest_ = guest_;
  //prev_guest_nice_ = guest_nice_;
  
  return cpu_percentage_;   
   
   
  //return 0.0; 
}