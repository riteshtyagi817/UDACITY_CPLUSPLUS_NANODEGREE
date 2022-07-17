#include<iostream>
#include<fstream>
#include"game.h"
#include<sstream>
using namespace std;
const std::string filepath{"./details.txt"};
const std::string highest_score_filepath{"./highest_score.txt"};
class User{
  public:
  User(){
    out_file_stream.open(filepath,ios::app);
  }
  ~User()
  {
    out_file_stream.close();
  }
  void show_message();
  void writing_user_data_to_file(Game &game);
  void checking_and_updating_highest_score(Game &game);
  private:
  string _name{};
   void user_processing();
  std::ofstream out_file_stream;
 };
