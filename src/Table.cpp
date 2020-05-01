#include "Table.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Table::Table(string path_in, int length_id_in, int length_type_in,
			 int length_alias_in, int length_desc_in)
	: path(path_in), length_id(length_id_in), length_type(length_type_in), length_alias(length_alias_in), length_desc(length_desc_in) {
	fout.open(path + "aliases_formatted.txt");
	fout << "test formatted" << endl;
	fin.open(path + "aliases_unformatted.txt");
	string line;
	fin >> line;
	cout << "in unformatted: " << line << endl;
}

void Table::output_horizontal_line() {
	vector<int> lengths_to_loop = {length_id, length_type, length_alias, length_desc};
	for (int i = 0; i < lengths_to_loop.size(); ++i) {
		fout << "+";
		for (int j = 0; j < lengths_to_loop[i] + 2; ++j) {
			fout << "-";
		}
	}
	fout << "+";
}

void Table::print() {
	output_horizontal_line();
}