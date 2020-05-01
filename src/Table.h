#include <fstream>
#include <iostream>
#include <vector>

class Table {
   public:
	// Expects an unformatted file path, and a formatted file output path.
	// Other arguments are optional.
	Table(std::string path_input_in, std::string path_output_in, int length_id_in = 3, int length_type_in = 10,
		  int length_alias_in = 10, int length_desc_in = 20);

	void output_horizontal_line();

	void print();

   private:
	struct Datum {
		int id;
		std::string type;
		std::string alias;
		std::string description;

		bool operator<(Datum &other) const;
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