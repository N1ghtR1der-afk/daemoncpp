#include <iostream>
#include <filesystem>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "./libs/aes256.hpp"
#include <fstream>
#include <string>
using namespace std;

void cryptor(filesystem::path source,filesystem::path out){
  ifstream file_target;
  ofstream file_out;
  
  file_target.open(source);
  file_out.open(out);

  if (!file_target.is_open()){
    cout<<"ERROR"<<endl;
  }
  else{
    
    string str;
    string k = "qwertyuiopasdfgh";
    ByteArray byte_k(k.begin(),k.end());

    while(getline(file_target, str)){
      ByteArray buffer;
      ByteArray byte_str(str.begin(), str.end());
      Aes256::encrypt(byte_k, byte_str, buffer);
        for ( auto x : buffer){
            file_out<<x;
        }
        file_out<<endl;
    }
  }
  file_target.close();
  file_out.close();
}

vector<filesystem::__cxx11::path> massiv;
filesystem::__cxx11::path target = "./encrypted";


void get_paths(vector<string>& paths, const string& current_path) {

	for (const auto& file : filesystem::directory_iterator(current_path)) {
		if (filesystem::is_directory(file)) {
			get_paths(paths, file.path().string());
		}
		else {
    filesystem::path sourceFile = file.path();
    filesystem::path targetParent = "./encrypted";

    auto target = targetParent / sourceFile.filename(); 

    try 
    {
        filesystem::create_directories(targetParent); 
        cryptor(sourceFile,target);
        cout<<sourceFile.filename()<<" had crypted"<<endl;
    }
    catch (std::exception& e) 
    {
        std::cout << e.what();
    }
    // filesystem::remove(file);
		}
    
	}
	

}

void start_scan(){
  for(;;){
  vector<string> paths;
	get_paths(paths, "./test");
  }
}

ByteArray get_byte_array(unsigned char* word, int len)
{
  unsigned char* word_ = (unsigned char*)word;
  ByteArray result(len);
  for (int i = 0; i < len; i++) result[i] = word_[i];
  return result;
}


int main() {
vector<string> paths;
const string current="./test";
get_paths(paths,current);

	return 0;
}

