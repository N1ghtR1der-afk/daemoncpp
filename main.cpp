#include <iostream>
#include <filesystem>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "./libs/aes256.hpp"
#include <fstream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

 po::options_description desc("General options");
  std::string task_type;
  desc.add_options()
    ("help,h", "Show help")
    ("type,t", po::value<std::string>(&task_type), "Select task: train, recognize, score")
    ;
  po::options_description train_desc("Train options");
  train_desc.add_options()
    ("input,I", po::value<std::string>(), "Input .dat file")
    ("info,i", po::value<std::string>(), "Input .trn file")
    ("output,O", po::value<std::string>(), "Output parameters file .prs")
    ;
  po::options_description recognize_desc("Recognize options");
  recognize_desc.add_options()
    ("input,I",  po::value<std::vector<std::string> >(), "Input .dat file")
    ("params,p", po::value<std::string>(), "Input .prs file")
    ("output,O", po::value<std::string>(), "Output directory")
    ;
  po::options_description score_desc("Score options");
  score_desc.add_options()
    ("ethanol,e",  po::value<std::string>(), "Etalon .trn file")
    ("test,t", po::value<std::string>(), "Testing .trn file")
    ("output,O", po::value<std::string>(), "Output comparison file")
    ;


void encryptor(filesystem::path source,filesystem::path out){
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
    string big_str;

    while(getline(file_target, str)){
      big_str+=str;
      big_str+="\n";
    }



    ByteArray buffer;
    ByteArray big_byte_str(big_str.begin(), --big_str.end());
    Aes256::encrypt(byte_k, big_byte_str, buffer);
    for (auto x : buffer){
      file_out<<x;
    }
    
    
  }
  file_target.close();
  file_out.close();
}

void decryptor(filesystem::path source,filesystem::path out){
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
    string big_str;

    while(getline(file_target, str)){
      big_str+=str;
      big_str+="\n";

    }



    ByteArray buffer;
    ByteArray big_byte_str(big_str.begin(), --big_str.end());
    Aes256::decrypt(byte_k, big_byte_str, buffer);
    for (auto x : buffer){
      file_out<<x;
    }
    
    
  }
  file_target.close();
  file_out.close();
}

vector<filesystem::__cxx11::path> massiv;
filesystem::__cxx11::path target_to_crypt = "./test";
filesystem::__cxx11::path target_to_decrypt = "./encrypted";


filesystem::path cut_path(filesystem::path path_to_cut){
  filesystem::path p;
  for (auto it = ++++path_to_cut.begin(); it != --path_to_cut.end(); ++it){
    p+=*it;
    p+="/";
    }
  return p;
}

void encrypt_files(vector<string>& paths, const string& current_path) {

	for (const auto& file : filesystem::directory_iterator(current_path)) {
		if (filesystem::is_directory(file)) {
			encrypt_files(paths, file.path().string());
		}
		else {
    filesystem::path sourceFile = file.path();
    filesystem::path targetParent = "./encrypted" / cut_path(file.path());
    // string other_path{sourceFile.u8string()};

    auto target_to_crypt = targetParent/sourceFile.filename(); 

    try 
    {
        filesystem::create_directories(targetParent); 
        encryptor(sourceFile,target_to_crypt);
        cout<<sourceFile.filename()<<" had encrypted"<<endl;
    }
    catch (std::exception& e) 
    {
        std::cout << e.what();
    }
    
		}
    filesystem::remove(file);
    filesystem::remove(cut_path(file));
 
	}
	

}


void decrypt_files(vector<string>& paths, const string& current_path) {

	for (const auto& file : filesystem::directory_iterator(current_path)) {
		if (filesystem::is_directory(file)) {
			decrypt_files(paths, file.path().string());
		}
		else {
    filesystem::path sourceFile = file.path();
    filesystem::path targetParent = "./decrypted" / cut_path(file.path());


    auto target_to_decrypt = targetParent / sourceFile.filename(); 

    try 
    {
        filesystem::create_directories(targetParent); 
        decryptor(sourceFile,target_to_decrypt);
        cout<<sourceFile.filename()<<" had decrypted"<<endl;
    }
    catch (std::exception& e) 
    {
        std::cout << e.what();
    }

		}
    filesystem::remove(file);
    filesystem::remove(cut_path(file));
	}
	

}


void start_encrypt_scan(string folder){
  for(;;){
  vector<string> paths;
	encrypt_files(paths, folder);
  }
}

void start_decrypt_scan(string folder){
  for(;;){
  vector<string> paths;
	encrypt_files(paths, folder);
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
  encrypt_files(paths,"./test");
  decrypt_files(paths,"./encrypted");

	return 0;
}

