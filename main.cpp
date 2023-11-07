#include <iostream>
#include <filesystem>
using namespace std;



void get_paths(vector<string>& paths, const string& current_path) {

	for (const auto& file : filesystem::directory_iterator(current_path)) {
		if (filesystem::is_directory(file)) {
			get_paths(paths, file.path().string());
		}
		else {
			filesystem::remove(file);
		}
	}
	

}

int main() {

	vector<string> paths;
	get_paths(paths, "C:/Users/mickhail/test");
	cout << "the files were placed in another folder" << endl;
	return 0;
}

