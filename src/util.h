#include <iostream>
#include <vector>

void print_help_menu();
void split_line_by_delimiter(const std::string &str, std::vector<std::string> &pieces, char delimiter);

void trim_string(std::string &input);
std::string pad_blanks(std::string &input, int column_width);
void output_horizontal_line(std::vector<int> &lengths);
void print_interior_line(std::string id, std::string type, std::string alias, std::string desc, std::vector<int> &lengths);
void print_header(std::vector<int> &lengths);
