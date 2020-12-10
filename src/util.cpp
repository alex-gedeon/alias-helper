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

void trim_string(string &input) {
	int first_non = input.find_first_not_of("\t\n ");
	int last_non = input.find_last_not_of("\t\n ");
	if (first_non == -1 || last_non == -1) {
		input = "";
	} else {
		input = input.substr(first_non, last_non + 1 - first_non);
	}
}

string pad_blanks(string &input, int column_width) {
	trim_string(input);
	if (input.size() > column_width) {
		input = input.substr(0, column_width - 1);
		input += "#";
		input = " " + input + " ";
	} else {
		string right_pad;
		for (int i = input.size() - 1; i < column_width; ++i) {
			right_pad += " ";
		}
		input = " " + input + right_pad;
	}
	return input;
}

void output_horizontal_line(vector<int> &lengths) {
	for (int i = 0; i < lengths.size(); ++i) {
		cout << "+";
		for (int j = 0; j < lengths[i] + 2; ++j) {
			cout << "-";
		}
	}
	cout << "+\n";
}

void print_interior_line(std::string id, std::string type, std::string alias, std::string desc, vector<int> &lengths) {
	cout << "|" << pad_blanks(id, lengths[0]) << "|" << pad_blanks(type, lengths[1])
		 << "|" << pad_blanks(alias, lengths[2]) << "|" << pad_blanks(desc, lengths[3]) << "|\n";
}

void print_header(vector<int> &lengths) {
    output_horizontal_line(lengths);
	print_interior_line("ID", "Type", "Alias", "Description", lengths);
}
