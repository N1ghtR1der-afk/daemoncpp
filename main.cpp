#include <iostream>
#include <filesystem>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;



void get_paths(vector<string>& paths, const string& current_path) {

	for (const auto& file : filesystem::directory_iterator(current_path)) {
		if (filesystem::is_directory(file)) {
			get_paths(paths, file.path().string());
		}
		else {
            cout<<file.filename()<<endl;
            
		}
	}
	

}

int main() {

	vector<string> paths;
	get_paths(paths, "./test");
	cout << "the files were placed in another folder" << endl;
	return 0;
}

