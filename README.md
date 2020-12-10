# alias-helper v3.0

## Terminal based utility intended to streamline the usage of aliases

After typing repetitive commands like `$ cd ..`, `$ cd ../..`, `$ explorer.exe .`, and spending cumulative hours typing long `$ cd /mnt/c/Projects/.....` commands to get to my working directories, I decided to make this utility to make repetitive commands much more manageable through aliases.

### Usefulness of aliases

An alias is simply another name for something, where in this case it refers to another name for a complicated instruction. For example, it is quite tedious to have to constantly type a long command such as the following:  
`$ cd /mnt/c/Projects/foo/bar/foo_bar/bar_foo/foo_bar_foo/target`  
It would be much more convenient to just type a short alias instead, such as:  
`$ tdir`  
This can be done manually with `$ echo "alias tdir='{long command}'" >> ~/.bash_aliases`, or through editing `~/.bash_aliases` in an editor like vim, but these methods make it hard to keep track of current and relevant aliases when, like me, you accumulate dozens of aliases and find that parsing through the output of `$ alias` is just too inefficient.

That's what this utility aims to solve. I intend to create a more user-friendly system to manage aliases, by assigning user-inputted tags to them through types and descriptions, and printing out an organized table which summarizes the aliases created to date.

### Installation

- Clone the git repository with `$ git clone https://github.com/alex-gedeon/alias-helper.git`
- Compile and install the utility with `$ sudo make`
- Test the output of `$ alh`, make sure you create a `~/.bash_aliases` file.

### Example usages

#### Help menu

The help menu can be accessed with the `-h` flag, run as `$ alh -h` for an output of:

``` none
$ alh -h
alias helper, version 3.0
Homepage: https://github.com/alex-gedeon/alias-helper

Usage: alh [OPTIONS]
        -h: Print help menu
        -l: List non-blacklisted aliases
        -n: Create a new alias. Requires 2, 4, or 5 arguments
        -u: Update alias type and description. Requires 2 arguments
        -b: Show blacklist, or toggle an alias with a given ID
```

#### Listing aliases

Listing non-blacklisted aliases in a formatted table can be done simply with `$ alh`, or `$alh -l`, where blacklisted aliases can be shown with `$ alh -b`. Attributes that do not fit into the column of a table are cut off, with the last fitting character replaced with a `#`.

``` none
$ alh
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
| 25  | dir        | 388        | 388 dir                                            |
| 16  |            | alex       | Windows home dir                                   |
| 23  |            | chirp      | Chirp dir                                          |
| 24  |            | mseed      | Minecraft seed project dir                         |
| 14  |            | projs      | Projects dir                                       |
| 22  |            | school     | School dir                                         |
| 15  |            | squirl     | Squirl dir                                         |
+-----+------------+------------+----------------------------------------------------+
| 7   | git        | ga         | Stage all files                                    |
| 8   |            | gc         | git commit -m                                      |
| 21  |            | gcm        | Checkout master                                    |
| 10  |            | gpl        | git pull                                           |
| 9   |            | gpu        | git push                                           |
| 6   |            | gs         | git status                                         |
+-----+------------+------------+----------------------------------------------------+
| 19  | online     | drive      | Opens Google Drive in Chrome                       |
+-----+------------+------------+----------------------------------------------------+
| 18  | program    | chrome     | Opens chrome.exe                                   |
+-----+------------+------------+----------------------------------------------------+
| 11  | python     | act        | Activate venv                                      |
| 12  |            | deac       | Deactivates venv                                   |
| 13  |            | pyenv      | Create a venv, expects version                     |
| 20  |            | pyswitch   | Switches default python3 version                   |
+-----+------------+------------+----------------------------------------------------+
| 1   | util       | cbal       | Edit aliases in vscode                             |
| 17  |            | expl       | Opens explorer in .                                |
| 0   |            | rel        | Reloads aliases                                    |
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
$ alh -b
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
| 2   | util       | ..         | Go up a level                                      |
| 3   |            | ...        | Go up 2 levels                                     |
| 4   |            | ....       | Go up 3 levels                                     |
| 5   |            | .....      | Go up 4 levels                                     |
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
```

#### Creating an alias

Creating an alias is done through the `-n` flag, and expects two to four arguments for the alias itself, the command it replaces, and optionally the alias's type and description. This can be seen by typing `$ alh -n`, yielding the output of:

``` none
$ alh -n
Usage: alh -n [alias] [command] {type} {description}
```

#### Updating an alias

If the type and description of an alias is not given at creation, such as if a previous `~/.bash_aliases` file had aliases created externally, they can be updated with the `-u` flag. This option requires the ID of the alias to fix, given through the table in `-l`, along with the new type and description for it. This can be seen by typing `$alh -u`, yielding the output of:

``` none
$ alh -u
Usage: alh -u [ID] [new type] [new description]
```

#### Blacklisting an alias

Removing an alias from the regular output of `$alh -l` can be done through the `-b` flag. This option takes in either zero arguments, whereupon it prints all blacklisted aliases, or one argument in the form of the target alias's ID.

### Features

Current Functionality:

- Command line parsing for h, l, n, and u flags.
- Create, parse, and update aliases locally (in ~/.bash_aliases file)
- Blacklist aliases from appearing in list menu, run -b with no arguments for blacklist

In development:

- Make sure commented lines are ignored

Future plans:

- Alias creation should fail if name has already been used
- Allow user to create and view variables with similar functionality, would allow for commands such as `cd ${PROJ_DIR}/...` instead of retyping entire path (aliases within aliases I suppose)
- Ability to change printed table size in config file
- Blacklist multiple aliases at once
- Alias backup system
- Allow for environment aliases to be created easily (i.e. aliases that use a variable assigned at runtime, yet have a value during initialization)
- Allowing for functions
- Cross platform support
- Allow for listing aliases of only specific types
- Allow for general expansion characters, such as adding a '+' to commands to automatically include pulling from git, activating python environment, and opening vscode
