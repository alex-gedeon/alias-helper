#include <experimental/filesystem>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "needs 1 argument for path" << endl;
		exit(1);
	}
	experimental::filesystem::v1::path p(argv[1]);
	if (experimental::filesystem::v1::exists("../src/")) {
		cout << "exists!" << endl;
	} else {
		cout << "doesn't exist" << endl;
		cout << p.root_path() << endl;
		cout << "path: " << p << endl;
	}
}