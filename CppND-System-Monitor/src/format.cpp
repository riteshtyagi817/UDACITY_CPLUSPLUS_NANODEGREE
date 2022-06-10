#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  long time_in_seconds = seconds;
  int hours{};
  int minutes{}; 
  int secs{};
  string formatted_time{};
  string formatted_hours{};
  string formatted_minutes{};
  string formatted_secs{};

  hours = time_in_seconds/3600;
  time_in_seconds = time_in_seconds%3600;
  minutes = time_in_seconds/60;
  time_in_seconds = time_in_seconds%60;
  secs = time_in_seconds;

  if(hours < 10)
  {  
    formatted_hours  = '0'+std::to_string(hours);
  } 
  else
  {
  	formatted_hours = std::to_string(hours);
  }
  if(minutes < 10)
  { 
   formatted_minutes = '0'+std::to_string(minutes);
  }  
  else
  {
    formatted_minutes = std::to_string(minutes);
  } 
  
  if(secs < 10)
  {  
    formatted_secs = '0'+std::to_string(secs);
    
  } 
  else
  { 
    formatted_secs = std::to_string(secs);
    
  } 
  
  formatted_time = formatted_hours+':'+formatted_minutes+':'+formatted_secs;
  
  return formatted_time;

  
}
  //return string(); }