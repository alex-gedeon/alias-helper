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
        {"import", required_argument, nullptr, 'i'},
        {"new", no_argument, nullptr, 'n'},
        {"type", required_argument, nullptr, 't'},
        {"alias", required_argument, nullptr, 'a'},
        {"description", required_argument, nullptr, 'd'}
    };

    while ((choice = getopt_long(argc, argv, "hli:nt:a:d:", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                cout << "TODO: help menu\n";
                exit(0);
            case 'l':
                cout << "TODO: list\n";
                exit(0);
            case 'i':
                cout << "TODO: import\n";
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
            default:
				cerr << "Invalid option or input. Try with -h flag for help." << endl;
                exit(1);
        }
    }
}