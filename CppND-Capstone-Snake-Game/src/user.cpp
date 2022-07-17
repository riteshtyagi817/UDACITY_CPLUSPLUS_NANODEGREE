#include<iostream>
using namespace std;
#include "user.h"
void User::show_message()
{
  cout << " Welcome to snake Game " << endl;
  
  user_processing();
    
  return ;      
}
void User::user_processing()
{
  cout << " Please Enter your first name without any space" << endl;
  string name{};
  
  cin >> name;
  _name = name;
  cout << " Name entered by you : " << _name << endl;
  cout << " Please continue with your game now " << endl;
  cout << " Your details will be saved in file details.txt " << endl;
  return ;
}

void User::writing_user_data_to_file(Game &game)
{
  if( !out_file_stream ) { 
      cerr << "Error: details.txt file could not be opened" << endl;
      
  }
  else
  {
    
    cout << " Writing the details to details.txt file which is present in the current folder " << endl;
    out_file_stream << "**************************************" << endl;
    out_file_stream << "name: " << _name  << endl;
    out_file_stream << "Score: " << game.GetScore()  << endl;
    out_file_stream << "Size: "  << game.GetSize() << endl;
    out_file_stream << "**************************************" << endl;
   
  
  }
  return ;
  
}
void User::checking_and_updating_highest_score(Game &game)
{
  	int temp_high_score {};
  	std::ifstream in_file_stream;
  	in_file_stream.open(highest_score_filepath);
  	if(!in_file_stream)
  	{
    	cerr << " Could not read the file highest_score.txt in the current folder " << endl;
      	cerr << " you might be the first user so we are creating this file highest_score.txt now " << endl;
        std::ofstream high_score_file_stream;
      	high_score_file_stream.open(highest_score_filepath);
      	if(!high_score_file_stream)
      	{
        	cerr << " could not update the file highest_score.txt in the current folder " << endl;
                
      	}
      	else
      	{
            int temp  = 0;
  			high_score_file_stream << " Highest_Score " << temp << endl;
    		high_score_file_stream.close();
            
      	}
        
  	}
  	else
  	{
    	std::string line;
    	string temp{};
    	int high_score{};
    
    	getline(in_file_stream, line);
    	istringstream my_stream(line);
    	my_stream >> temp >> high_score;
    	in_file_stream.close();
    	// readin has been closed
    	if(game.GetScore() > high_score)
    	{
      		cout << " previous highest score was " << high_score << endl;
      		cout << " Your score became highest score now , Well done!! " << endl;
      
      		std::ofstream high_score_file_stream;
      		high_score_file_stream.open(highest_score_filepath);
      		if(!high_score_file_stream)
      		{
        		cerr << " could not update the file highest_score.txt in the current folder " << endl;
                
      		}
      		else
      		{
        
  				high_score_file_stream << " Highest_Score " << game.GetScore() << endl;
    			high_score_file_stream.close();
            
      		}
          
    	}
    
    
  	}
  	
  return;
  
   
}
  
  
  
 



