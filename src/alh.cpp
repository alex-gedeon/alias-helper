#include <getopt.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

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
            // Check l argument
            if(passed_args.find('l') != passed_args.end()) {
                print_aliases(false);
            }

            // Check n argument
            if(passed_args.find('n') != passed_args.end()) {
                // Append new alias to file
                ofstream outfile(alias_dir, ios_base::app);

                // Skip if exists
                read_in_aliases();
                if(used_aliases.find(passed_args['a']) != used_aliases.end()) {
                    cout << "Alias '" << passed_args['a'] << "' already exists, skipping" << endl;
                    return;
                }

                // Escape quotes if exist
                ReplaceStringInPlace(passed_args['c'], "'", "'\\''");
                outfile << "alias " << passed_args['a'] << "='" << passed_args['c'] << "'";
                if(passed_args.find('t') != passed_args.end()) {
                    outfile << " #" << passed_args['t'];
                    outfile << "#" << passed_args['d'];
                    if(passed_args.find('b') != passed_args.end()) {
                        outfile << "#Y";
                    }
                    else {
                        outfile << "#N";
                    }
                }
                outfile << "\n";
                outfile.close();
                return;
            }

            // Check u argument
            if(passed_args.find('u') != passed_args.end()) {
                update_line_in_file(stoi(passed_args['i']), passed_args['t'], passed_args['d'], false);
                return;
            }

            // Check b argument
            if(passed_args.find('b') != passed_args.end()) {
                if(passed_args['b'] == "false") {
                    print_aliases(true);
                    return;
                }
                update_line_in_file(stoi(passed_args['b']), "", "", true);
                return;
            }

            // Check r argument
            if(passed_args.find('r') != passed_args.end()) {
                // Read in known aliases
                read_in_aliases();

                // Read from inputted file, append to alias file
                ifstream infile(passed_args['r']);
                if(!infile.is_open()) {
                    cout << "Error: invalid file" << endl;
                    exit(1);
                }
                ofstream outfile(alias_dir, ios::app);

                string line;
                while(getline(infile, line)) {
                    int first_space = line.find(' ');
                    int first_equals = line.find('=');
                    string extracted_alias = line.substr(first_space+1, first_equals-first_space-1);
                    if(used_aliases.find(extracted_alias) != used_aliases.end()) {
                        cout << "Alias '" << extracted_alias << "' already exists, skipping" << endl;
                        continue;
                    }
                    used_aliases.insert(extracted_alias);
                    outfile << line << endl;
                }
                return;
            }
        }

    private:
        void print_aliases(bool blacklist) {
            read_in_aliases();

            vector<int> lengths = {length_id, length_type, length_alias, length_description};
            Table table(lengths);
            table.print_horizontal_line();
            table.print_header();

            string curr_type = "\n";
            for(auto datum : data) {
                // If blacklist, skip non-blacklisted; if !blacklist, skip blacklisted
                if((blacklist && !datum.is_blacklisted) || (!blacklist && datum.is_blacklisted)) {
                    continue;
                }

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

        void update_line_in_file(int id_to_update, string new_type, string new_desc, bool flip_blacklist) {
            // Read in aliases, error check idx
            read_in_aliases();
            if(int(data.size()) < id_to_update) {
                cout << "Error: invalid idx" << endl;
                exit(1);
            }

            // Two streams: reading and writing
            string tmp_alias = alias_dir + ".tmp";
            ifstream fin(alias_dir);
            ofstream fout(tmp_alias);
            
            // Read in from one, dump to other
            string line;
            int idx = 0;
            while(getline(fin, line)) {
                // If hit index, print alias and command, print type and description
                if(idx == id_to_update) {
                    for(size_t i = 0; i < data.size(); ++i) {
                        if(data[i].id == id_to_update) {
                            fout << data[i] << " #";
                            // Update type if requested
                            if(new_type == "") {
                                fout << data[i].type;
                            }
                            else {
                                fout << new_type;
                            }
                            fout << "#";
                            // Update description if requested
                            if(new_desc == "") {
                                fout << data[i].description;
                            }
                            else {
                                fout << new_desc;
                            }
                            fout << "#";

                            // Flip blacklist if requested
                            if(flip_blacklist) {
                                if(data[i].is_blacklisted) {
                                    fout << "N";
                                }
                                else {
                                    fout << "Y";
                                }
                            }
                            else {
                                if(data[i].is_blacklisted) {
                                    fout << "Y";
                                }
                                else {
                                    fout << "N";
                                }
                            }
                            fout << endl;
                            break;
                        }
                    }
                }
                else {
                    fout << line << endl;
                }
                ++idx;
            }
            rename(tmp_alias.c_str(), alias_dir.c_str());
        }

        void read_in_aliases() {
            string line;
            ifstream alias_filestream(alias_dir);
            int id = 0;
            while(getline(alias_filestream, line)) {
                // Properly formatted line:
                // alias temp='echo "hello world!"'#{type}#{description}#{do_blacklist: Y or N}

                // Check for commented line
                if(line.size() == 0) {
                    ++id;
                    continue;
                }
                else if(line[0] == '#') {
                    ++id;
                    continue;
                }
                // Split by space first to extract alias
                int first_space = line.find(' ');
                int first_equals = line.find('=');
                int first_hash = line.find('#');
                string extracted_alias = line.substr(first_space+1, first_equals-first_space-1);
                
                // Keep track of used aliases
                used_aliases.insert(extracted_alias);

                string extracted_command;
                if(first_hash != -1) {
                    extracted_command = line.substr(first_equals+2, first_hash-1-first_equals-3);
                }
                else {
                    extracted_command = line.substr(first_equals+2, line.size() - first_equals-3);
                }

                // Extract type, description, and whether to blacklist
                vector<string> tokens;
                split_line_by_delimiter(line, tokens, '#');
                string extracted_type, extracted_description;
                bool is_blacklisted = false;
                if(tokens.size() > 2) {
                    extracted_type = tokens[1];
                    extracted_description = tokens[2];
                    if(tokens.size() == 4) {
                        is_blacklisted = tokens[3] == "Y";
                    }
                }

                // Append to data vector
                data.push_back(Datum{id, extracted_alias, extracted_command, extracted_type, extracted_description, is_blacklisted});

                id += 1;
            }
            sort(data.begin(), data.end());
        }
        
        struct Datum {
                int id;
                string alias;
                string command;
                string type;
                string description;
                bool is_blacklisted;

                bool operator<(const Datum &other) const {
                    if (type != other.type) {
                        return type < other.type;
                    }
                    else if (alias != other.alias) {
                        return alias < other.alias;
                    }
                    return id < other.id;
                }

                friend ostream& operator<<(ostream &out, Datum d) {
                    out << "alias " << d.alias << "='" << d.command << "'";
                    return out;
                }
            };
        vector<Datum> data;
        unordered_map<char, string> passed_args;
        unordered_set<string> used_aliases;
        string alias_dir;
        int length_id = 3;
        // int length_command = 20;
        int length_alias = 10;
        int length_type = 10;
        int length_description = 50;

};

void parse_command_line(int argc, char** argv, unordered_map<char, string>& passed_args);

int main(int argc, char** argv) {
    // Argument check
    unordered_map<char, string> passed_args;
    if (argc == 1) {
        passed_args['l'] = "true";
    }

    // Read in command line arguments
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
        {"update", no_argument, nullptr, 'u'},
        {"blacklist", no_argument, nullptr, 'b'},
        {"read", required_argument, nullptr, 'r'}
    };

    while ((choice = getopt_long(argc, argv, "hlnubr:", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                print_help_menu();
                exit(0);
            case 'l':
                passed_args['l'] = "true";
                break;
            case 'n': {
                // Read in alias, command, type, and description
                vector<string> inputs;
                for(; optind < argc && *argv[optind] != '-'; ++optind) {
                    inputs.push_back(string(argv[optind]));
                }

                // Check args
                if(inputs.size() < 2 || inputs.size() > 5) {
                    cout << "Usages:\n"
                         << "\talh -n [alias] [command]\n"
                         << "\talh -n [alias] [command] {do_blacklist}\n"
                         << "\talh -n [alias] [command] {type} {description} {do_blacklist}" << endl;
                    exit(1);
                }
                passed_args['a'] = inputs[0];
                passed_args['c'] = inputs[1];
                if(inputs.size() == 3) {
                    if(string(inputs[2]) == "Y") {
                        passed_args['b'] = "true";
                    }
                }
                // Read in optional arguments
                else if(inputs.size() > 3) {
                    passed_args['t'] = inputs[2];
                    passed_args['d'] = inputs[3];
                    if(inputs.size() == 5) {
                        if(string(inputs[4]) == "Y") {
                            passed_args['b'] = "true";
                        }
                    }
                }
                passed_args['n'] = "true";
                break;
            }
            case 'u': {
                // Read in id, type, and description
                vector<string> inputs;
                for(; optind < argc && *argv[optind] != '-'; ++optind) {
                    inputs.push_back(string(argv[optind]));
                }

                // Check args
                if(inputs.size() != 3) {
                    cout << "Usage: alh -u [ID] [new type] [new description]" << endl;
                    exit(1);
                }

                // Store args
                passed_args['i'] = inputs[0];
                passed_args['t'] = inputs[1];
                passed_args['d'] = inputs[2];
                passed_args['u'] = "true";
                break;
            }
            case 'b': {
                // Read in argument for ID
                vector<string> inputs;
                for(; optind < argc && *argv[optind] != '-'; ++optind) {
                    inputs.push_back(string(argv[optind]));
                }
                if(inputs.size() == 0) {
                    passed_args['b'] = "false";
                }
                else {
                    passed_args['b'] = string(inputs[0]);
                }
                break;
            }
            case 'r':
                passed_args['r'] = optarg;
                break;
            default:
				cerr << "Invalid option, or missing command line argument. Try with -h flag for help." << endl;
                exit(1);
        }
    }
}
