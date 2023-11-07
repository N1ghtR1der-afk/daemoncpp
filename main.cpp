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
           
		}
	}
	

}

int main() {

	vector<string> paths;
	get_paths(paths, "./test");
	cout << "the files were placed in another folder" << endl;
	return 0;
}

