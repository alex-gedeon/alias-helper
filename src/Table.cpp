#include <iostream>
#include <vector>

#include "Table.h"

using namespace std;

Table::Table(const vector<int> &lengths_in)
    : lengths(lengths_in) {}

void Table::print_horizontal_line() {
	for (int i = 0; i < lengths.size(); ++i) {
		cout << "+";
		for (int j = 0; j < lengths[i] + 2; ++j) {
			cout << "-";
		}
	}
	cout << "+\n";
}

void Table::print_header() {
    print_interior_line("ID", "Type", "Alias", "Description");
}

void Table::print_interior_line(string id, string type, string alias, string desc) {
	cout << "|" << pad_blanks(id, lengths[0]) << "|" << pad_blanks(type, lengths[1])
		 << "|" << pad_blanks(alias, lengths[2]) << "|" << pad_blanks(desc, lengths[3]) << "|\n";
}

void Table::trim_string(string &input) {
	int first_non = input.find_first_not_of("\t\n ");
	int last_non = input.find_last_not_of("\t\n ");
	if (first_non == -1 || last_non == -1) {
		input = "";
	} else {
		input = input.substr(first_non, last_non + 1 - first_non);
	}
}

string Table::pad_blanks(string &input, int column_width) {
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
