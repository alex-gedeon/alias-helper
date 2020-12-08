#include <getopt.h>

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void parse_command_line(int argc, char** argv, unordered_map<string, int>& passed_args);

int main(int argc, char** argv) {
    unordered_map<string, int> passed_args;
    parse_command_line(argc, argv, passed_args);
}

void parse_command_line(int argc, char** argv, unordered_map<string, int>& passed_args) {
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
                cout << "alias helper, version 3.0.0\n"
                    << "Homepage: https://github.com/alex-gedeon/alias-helper\n\n"
                    << "Usage: alh [OPTIONS]\n"
                    << "\t-h: Prints help menu\n"
                    << "\t-l: Lists available aliases\n"
                    << "\t-n: Creates a new alias. Requires -t and -d\n"
                    << "\t-t: Specifies alias type\n"
                    << "\t-a: Specifies alias shorcut\n"
                    << "\t-d: Specifies alias description\n"
                    << "\t-i: Imports aliases from a file\n";
                exit(0);
            case 'l':
                cout << "TODO: list\n";
                exit(0);
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