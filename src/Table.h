#include <fstream>
#include <iostream>
#include <vector>

class Table {
   public:
	// Expects an unformatted file path, and a formatted file output path.
	// Other arguments are optional.
	Table(std::string path_input_in, std::string path_output_in, int length_id_in = 3, int length_type_in = 10,
		  int length_alias_in = 10, int length_desc_in = 30);

	// Main driver for Table class. Should be only public method.
	void print();

   private:
	void output_horizontal_line();
	void read_in_and_sort();
	void split_line_by_delimiter(const std::string &str, std::vector<std::string> &pieces, char delimiter);
	void print_header();
	void print_interior_line(std::string id, std::string type, std::string alias, std::string desc);
	std::string pad_blanks(std::string &input, int column_width);
	void trim_string(std::string &input);
	struct Datum {
		int id;
		std::string type;
		std::string alias;
		std::string description;

		bool operator<(Datum &other) {
			if (type != other.type) {
				return type < other.type;
			}
			return alias < other.type;
		}

		void print() {
			std::cout << "id: " << id << " type: " << type
					  << " alias: " << alias << " desc: "
					  << description << std::endl;
		}
	};

	std::string path_input;
	std::string path_output;
	int length_id;
	int length_type;
	int length_alias;
	int length_desc;
	std::ofstream fout;
	std::ifstream fin;
	std::vector<Datum> data;
};