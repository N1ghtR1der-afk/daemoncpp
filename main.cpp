#include <iostream>
#include <filesystem>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


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
        filesystem::copy_file(sourceFile, target, filesystem::copy_options::overwrite_existing);
    }
    catch (std::exception& e) 
    {
        std::cout << e.what();
    }
    filesystem::remove(file);
		}
    
	}
	

}

void start_scan(){
  for(;;){
  vector<string> paths;
	get_paths(paths, "./test");
  }
}



int main() {

  start_scan();


	return 0;
}

