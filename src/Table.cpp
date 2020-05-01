#include "Table.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Table::Table(string path_input_in, string path_output_in, int length_id_in, int length_type_in,
			 int length_alias_in, int length_desc_in)
	: path_input(path_input_in), path_output(path_output_in), length_id(length_id_in), length_type(length_type_in), length_alias(length_alias_in), length_desc(length_desc_in) {
	// Opens unformatted file for input and formatted file for output.
	fin.open(path_input);
	fout.open(path_output);
}

void Table::output_horizontal_line() {
	vector<int> lengths_to_loop = {length_id, length_type, length_alias, length_desc};
	for (int i = 0; i < lengths_to_loop.size(); ++i) {
		fout << "+";
		for (int j = 0; j < lengths_to_loop[i] + 2; ++j) {
			fout << "-";
		}
	}
	fout << "+\n";
}

void Table::read_in_and_sort() {
	string read_line;
	int id = 0;
	while (getline(fin, read_line)) {
		vector<string> tokens;
		split_line_by_delimiter(read_line, tokens, '#');
		data.push_back(Datum{id, tokens[0], tokens[1], tokens[2]});
		++id;
	}
	// Uses overloaded Datum < operator to sort
	sort(data.begin(), data.end());
}

void Table::split_line_by_delimiter(const string &str, vector<string> &pieces, char delimiter) {
	int last_split_index = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == delimiter && i != 0) {
			pieces.push_back(str.substr(last_split_index, i - last_split_index));
			last_split_index = i + 1;
		}
	}
	pieces.push_back(str.substr(last_split_index, string::npos));
}

void Table::trim_string(string &input) {
	int first_non = input.find_first_not_of("\t\n ");
	int last_non = input.find_last_not_of("\t\n ");
	input = input.substr(first_non, last_non + 1 - first_non);
}

/* Pads left side with one blank, extends blanks to end of column.
If input doesnt fit in column, cuts off rest and places a # as
the last character. */
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

void Table::print_interior_line(std::string id, std::string type, std::string alias, std::string desc) {
	fout << "|" << pad_blanks(id, length_id) << "|" << pad_blanks(type, length_type)
		 << "|" << pad_blanks(alias, length_alias) << "|" << pad_blanks(desc, length_desc) << "|\n";
}

void Table::print_header() {
	output_horizontal_line();
	print_interior_line("ID", "Type", "Alias", "Description");
}

void Table::print() {
	read_in_and_sort();
	print_header();
	string curr_type = "";
	for (auto datum : data) {
		if (curr_type != datum.type) {
			output_horizontal_line();
			curr_type = datum.type;
		}
		print_interior_line(to_string(datum.id), datum.type, datum.alias, datum.description);
	}
	output_horizontal_line();
}