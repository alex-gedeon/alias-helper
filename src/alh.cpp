#include <getopt.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "util.h"
#include "Table.h"

using namespace std;

class Driver {
    public:
        Driver(unordered_map<char, string>& passed_args_in, string alias_dir_in)
            : passed_args(passed_args_in), alias_dir(alias_dir_in) {}

        void run() {
            if(passed_args.find('l') != passed_args.end()) {
                read_in_aliases();
                // for(int i = 0; i < data.size(); ++i) {
                //     data[i].print();
                // }

                vector<int> lengths = {length_id, length_type, length_alias, length_description};
                Table table(lengths);
                table.print_horizontal_line();
                table.print_header();

                string curr_type = "\n";
                for(auto datum : data) {
                    if (curr_type != datum.type) {
                        table.print_horizontal_line();
                        curr_type = datum.type;
                        table.print_interior_line(to_string(datum.id), datum.type, datum.alias, datum.description);
                    }
                    else {
                        table.print_interior_line(to_string(datum.id), "", datum.alias, datum.description);
                    }
                }
                table.print_horizontal_line();
                table.print_header();
                table.print_horizontal_line();
            }
        }

    private:
        void read_in_aliases() {
            string line;
            ifstream alias_filestream(alias_dir);
            int id = 0;
            while(getline(alias_filestream, line)) {
                // Properly formatted line:
                // alias temp='echo "hello world!"'#{type}#{description}

                // cout << line << endl;
                // Split by space first to extract alias
                int first_space = line.find(' ');
                int first_equals = line.find('=');
                int first_hash = line.find('#');
                string extracted_alias = line.substr(first_space+1, first_equals-first_space-1);

                string extracted_command;
                if(first_hash != -1) {
                    extracted_command = line.substr(first_equals+2, first_hash-first_equals-3);
                }
                else {
                    extracted_command = line.substr(first_equals+2, line.size() - first_equals-3);
                }

                // Extract type and description
                vector<string> tokens;
                split_line_by_delimiter(line, tokens, '#');
                string extracted_type, extracted_description;
                if(tokens.size() == 3) {
                    extracted_type = tokens[1];
                    extracted_description = tokens[2];
                }
                // cout << extracted_alias << " | " << extracted_command << " | " << extracted_type << " | " << extracted_description << endl;

                // Append to data vector
                data.push_back(Datum{id, extracted_alias, extracted_command, extracted_type, extracted_description});

                id += 1;
            }
            sort(data.begin(), data.end());
        }
        
        struct Datum {
                int id;
                std::string alias;
                std::string command;
                std::string type;
                std::string description;

                bool operator<(Datum &other) {
                    if (type != other.type) {
                        return type < other.type;
                    }
                    else if (alias != other.alias) {
                        return alias < other.alias;
                    }
                    return id < other.id;
                }

                void print() {
                    std::cout << "id: " << id << " type: " << type
                            << " alias: " << alias << " desc: "
                            << description << std::endl;
                }
            };
        vector<Datum> data;
        unordered_map<char, string> passed_args;
        string alias_dir;
        int length_id = 3;
        int length_command = 20;
        int length_alias = 10;
        int length_type = 10;
        int length_description = 50;

};

void parse_command_line(int argc, char** argv, unordered_map<char, string>& passed_args);

int main(int argc, char** argv) {
    // Argument check
    if (argc == 1) {
        print_help_menu();
        exit(0);
    }

    // Read in command line arguments
    unordered_map<char, string> passed_args;
    parse_command_line(argc, argv, passed_args);

    // Get alias filepath
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    string alias_dir = string(homedir) + "/.bash_aliases";

    ifstream f(alias_dir);
    if (!f.good()) {
        cout << "Error: no alias file\n";
        exit(1);
    }
    f.close();

    // Create driver object, run processing of aliases
    Driver driver(passed_args, alias_dir);
    driver.run();
}

void parse_command_line(int argc, char** argv, unordered_map<char, string>& passed_args) {
    opterr = true;

    int choice = 0;
    int option_index = 0;
    option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"list", no_argument, nullptr, 'l'},
        {"new", no_argument, nullptr, 'n'},
        {"alias", required_argument, nullptr, 'a'},
        {"command", required_argument, nullptr, 'c'},
        {"type", required_argument, nullptr, 't'},
        {"description", required_argument, nullptr, 'd'},
        {"import", required_argument, nullptr, 'i'},
    };

    while ((choice = getopt_long(argc, argv, "hlna:c:t:d:i:", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                print_help_menu();
                exit(0);
            case 'l':
                passed_args['l'] = "true";
                break;
            case 'n':
                cout << "TODO: new\n";
                exit(0);
            case 'a':
                cout << "TODO: alias\n";
                exit(0);
            case 'c':
                cout << "TODO: command\n";
                exit(0);
            case 't':
                cout << "TODO: type\n";
                exit(0);
            case 'd':
                cout << "TODO: description\n";
                exit(0);
            case 'i':
                cout << "TODO: import\n";
                exit(0);
            default:
				cerr << "Invalid option, or missing command line argument. Try with -h flag for help." << endl;
                exit(1);
        }
    }
}
