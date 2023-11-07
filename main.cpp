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
	
	fs::path sourceFile = "path/to/sourceFile.ext";
    fs::path targetParent = "path/to/target";
    auto target = targetParent / sourceFile.filename(); // sourceFile.filename() returns "sourceFile.ext".

    try // If you want to avoid exception handling, then use the error code overload of the following functions.
    {
        fs::create_directories(targetParent); // Recursively create target directory if not existing.
        fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing);
    }
    catch (std::exception& e) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
    {
        std::cout << e.what();
    }
	return 0;
}

