#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

class Table {
   public:
	/* Expects an unformatted file path, and a formatted file output path.
	Other arguments are optional, can be ["inv_blist"], ["length_id"],
	["length_type"], ["length_alias"], and ["length_desc"] */
	Table(const std::string &path_input_in, const std::string &path_output_in,
		  const std::string &path_blacklist_in, std::unordered_map<std::string, int> &other_args);

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
	bool id_in_blacklist(int id);
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
	std::string path_blacklist;
	int length_id = 3;
	int length_type = 10;
	int length_alias = 10;
	int length_desc = 40;
	std::ofstream fout;
	std::ifstream fin;
	std::ifstream blacklist_fin;
	std::vector<Datum> data;
	std::vector<int> blacklist;
	bool invert_blacklist = false;
};