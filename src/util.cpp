#include <iostream>
#include <vector>

using namespace std;


void print_help_menu() {
    cout << "alias helper, version 3.0.0\n"
                    << "Homepage: https://github.com/alex-gedeon/alias-helper\n\n"
                    << "Usage: alh [OPTIONS]\n"
                    << "\t-h: Prints help menu\n"
                    << "\t-l: Lists available aliases\n"
                    << "\t-n: Creates a new alias. Requires -t and -d\n"
                    << "\t-t: Specifies alias type\n"
                    << "\t-a: Specifies alias shorcut\n"
                    << "\t-d: Specifies alias description\n"
                    << "\t-i: Imports aliases from a file\n";
}

void split_line_by_delimiter(const string &str, std::vector<string> &pieces, char delimiter) {
    int last_split_index = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == delimiter && i != 0) {
			pieces.push_back(str.substr(last_split_index, i - last_split_index));
			last_split_index = i + 1;
		}
	}
	pieces.push_back(str.substr(last_split_index, string::npos));
}
