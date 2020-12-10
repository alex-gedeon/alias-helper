#include <getopt.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "util.h"

using namespace std;

class Driver {
    public:
        Driver(unordered_map<char, string>& passed_args_in, string alias_dir_in)
            : passed_args(passed_args_in), alias_dir(alias_dir_in) {}

        void run() {
            if(passed_args.find('l') != passed_args.end()) {
                string line;
                ifstream alias_filestream(alias_dir);
                while(getline(alias_filestream, line)) {
                    // Properly formatted line:
                    // alias temp='echo "hello world!"'#{type}#{description}

                    cout << line << endl;
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
                    cout << extracted_alias << " " << extracted_command << endl;
                }
            }
        }

    private:
        unordered_map<char, string> passed_args;
        string alias_dir;

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
                return alias < other.alias;
            }

            void print() {
                std::cout << "id: " << id << " type: " << type
                        << " alias: " << alias << " desc: "
                        << description << std::endl;
            }
        };
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
        {"type", required_argument, nullptr, 't'},
        {"alias", required_argument, nullptr, 'a'},
        {"description", required_argument, nullptr, 'd'},
        {"import", required_argument, nullptr, 'i'},
    };

    while ((choice = getopt_long(argc, argv, "hlnt:a:d:i:", long_options, &option_index)) != -1) {
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
            case 't':
                cout << "TODO: type\n";
                exit(0);
            case 'a':
                cout << "TODO: alias\n";
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
