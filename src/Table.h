#include <iostream>
#include <vector>

class Table {
	public:
		Table(const std::vector<int> &lengths_in);

		void print_horizontal_line();
		void print_header();
		void print_interior_line(std::string id, std::string type, std::string alias, std::string desc);
		void trim_string(std::string &input);
		std::string pad_blanks(std::string &input, int column_width);

	private:
		std::vector<int> lengths;
};
