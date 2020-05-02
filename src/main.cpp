#include <getopt.h>

#include <iostream>
#include <string>
#include <unordered_map>

#include "Table.h"

using namespace std;

void parse_command_line(int argc, char** argv, string& type, string& file_path, unordered_map<string, int>& passed_args);
void print_invalid_input();

/* Driver for table program, expects a path to the /local/ directory with
an unformatted file with 3 columns, separated with a #. This functionality
can be expanded to as many columns as inputted later, but for the purposes
of this project it will only need 3 columns, for type, alias, and description.
The ID column will be drived from the line number that each entry is on in
the unformatted file, allowing the use of a blacklist file with a list of IDs
not to be displayed.

The blacklisting itself will be done with a bash script, and will be read in
separately by this program. blacklist.txt should be in the /local/ folder as
well. */
int main(int argc, char** argv) {
	// Error checking, primarily for testing and so rogue inputs don't cause errors
	if (argc < 3) {
		// Minimum is 3 since 2 flags are required (plus one for program itself).
		cout << "Wrong usage. Try with -h for help" << endl;
		exit(1);
	}
	/* Parse command line arguments using an unordered map and two strings to ease
	returning data. Could probably just use two maps for more general use later,
	like one from <string, string>, and another from <int, int>. */
	string table_type, file_path;
	unordered_map<string, int> passed_args;
	parse_command_line(argc, argv, table_type, file_path, passed_args);

	string local_path = file_path + "/local/";

	// Append filename extensions
	string input_addition, output_addition, blacklist_addition;
	if (table_type == "alias") {
		input_addition = "aliases_unformatted.txt";
		output_addition = "aliases_formatted.txt";
	} else {
		input_addition = "variables_unformatted.txt";
		output_addition = "variables_formatted.txt";
	}
	blacklist_addition = "blacklist.txt";

	Table table(local_path + input_addition, local_path + output_addition,
				local_path + blacklist_addition, passed_args);
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
		{"inv_blist", optional_argument, nullptr, 'b'},
		{"length_id", optional_argument, nullptr, 'i'},
		{"length_type", optional_argument, nullptr, 'y'},
		{"length_alias", optional_argument, nullptr, 'a'},
		{"length_desc", optional_argument, nullptr, 'd'},
		{nullptr, 0, nullptr, '\0'}};

	while ((choice = getopt_long(argc, argv, "ht:f:b:iyad", long_options, &option_index)) != -1) {
		switch (choice) {
			case 'h':
				cout << "usage: ./formatted [options]\n";
				cout << "Options:\n"
					 << "  --help          or -h: [ OPTIONAL ] Prints helpful information.\n"
					 << "  --type          or -t: [ REQUIRED ] Change type of inputted information. Requires argument \"alias\" or \"var\"\n"
					 << "  --file_in       or -f: [ REQUIRED ] Unformatted input file.\n"
					 << "  --inv_blist     or -b: [ OPTIONAL ] Boolean flag to invert the blacklist. Requires argument \"true\" or \"false\". Default is false.\n"
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
			case 'b':
				if (string(optarg) == "true") {
					passed_args["inv_blist"] = 1;
				}
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