#include <getopt.h>

#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Table.h"

using namespace std;

void parse_command_line(int argc, char** argv, string& type, string& file_path, unordered_map<string, int>& passed_args);
void print_invalid_input();

int main(int argc, char** argv) {
	// Parse command line arguments
	string type, file_path;
	unordered_map<string, int> passed_args;
	parse_command_line(argc, argv, type, file_path, passed_args);

	cout << "type: " << type << ", path: " << file_path << endl;

	return 0;

	// Check if /local/ path exists. If it doesn't, create it

	// Passed in directory is the directory to the Makefile, or to the bin/ folder.
	// Works out really conveniently actually, just need to remove last
	// section of the path in all cases.
	string temp_path = string(argv[1]);
	string root_path = temp_path.substr(0, temp_path.find_last_of('/'));
	cout << "root:" << root_path << endl;
	string local_path = root_path + "/local/";
	cout << "local path: " << local_path << endl;

	if (!experimental::filesystem::v1::exists(root_path + "/local/")) {
		experimental::filesystem::v1::create_directory(root_path + "/local/");
	}

	Table table(local_path);
	table.print();
}

void parse_command_line(int argc, char* argv[], string& type, string& file_path, unordered_map<string, int>& passed_args) {
	opterr = true;	// Help with errors

	int choice = 0;
	int option_index = 0;
	option long_options[] = {
		{"help", no_argument, nullptr, 'h'},
		{"type", required_argument, nullptr, 't'},
		{"file_path", required_argument, nullptr, 'f'},
		{"length_id", optional_argument, nullptr, 'i'},
		{"length_type", optional_argument, nullptr, 'y'},
		{"length_alias", optional_argument, nullptr, 'a'},
		{"length_desc", optional_argument, nullptr, 'd'},
		{nullptr, 0, nullptr, '\0'}};

	while ((choice = getopt_long(argc, argv, "ht:f:iyad", long_options, &option_index)) != -1) {
		switch (choice) {
			case 'h':
				cout << "usage: ./formatted [options]\n";
				cout << "Options:\n"
					 << "  --help          or -h: [ OPTIONAL ] Prints helpful information.\n"
					 << "  --type          or -t: [ REQUIRED ] Change type of inputted information. Requires argument \"alias\" or \"var\"\n"
					 << "  --file_in       or -f: [ REQUIRED ] Unformatted input file.\n"
					 << "  --length_id     or -i: [ OPTIONAL ] Specify the width of the \"id\" column. Default is 3.\n"
					 << "  --length_type   or -y: [ OPTIONAL ] Specify the width of the \"type\" column. Default is 10.\n"
					 << "  --length_alias  or -a: [ OPTIONAL ] Specify the width of the \"alias\" column. Default is 10.\n"
					 << "  --length_desc   or -d: [ OPTIONAL ] Specify the width of the \"description\" column. Default is 20.\n";
				exit(0);
			case 't':
				if (string(optarg) != "alias" && string(optarg) != "var") {
					print_invalid_input();
				}
				type = string(optarg);
				break;
			case 'f':
				file_path = string(optarg);
				break;
			case 'i':
				passed_args["length_id"] = atoi(optarg);
				break;
			case 'y':
				passed_args["length_type"] = atoi(optarg);
				break;
			case 'a':
				passed_args["length_alias"] = atoi(optarg);
				break;
			case 'd':
				passed_args["length_desc"] = atoi(optarg);
				break;
			default:
				cerr << "Invalid option or input. Try with -h flag for help." << endl;
				exit(1);
		}  // switch
	}	   // while loop
}  // parse_command_line();

void print_invalid_input() {
	cerr << "Invalid input. Run with -h flag for help." << endl;
	exit(1);
}