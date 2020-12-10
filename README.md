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
- Test the output of `$ alh`, make sure you already have a `~/.bash_aliases` file.

### Demo

In this example, I will be creating an alias to take me to the project directory of this git repo:

``` none
$ pwd
/mnt/c/Projects/alias-helper
$ alh -n alp "cd /mnt/c/Projects/alias-helper"
$ rel # alias for 'source ~/.bash_aliases`
$ cd ~
$ pwd
/home/alex
$ alp
$ pwd
/mnt/c/Projects/alias-helper
```

I'm now able to be able to go straight into this directory with just a simple alias. It appears in the output of `-l` as such:

``` none
$ alh # or alh -l
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
| 26  |            | alp        |                                                    |
...
```

I did not give this alias a type or description when creating it, so let's update it with the shown ID of 26:

``` none
$ alh -u 26 "dir" "Alias project directory"
$ alh
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
| 26  | dir        | alp        | Alias project directory                            |
...
```

It now appears under the proper category with the type and description columns filled in. If I wanted to blacklist this alias and omit it from the regular listing, it could be done as such:

``` none
$ alh -b 26
```

It will now only appear when blacklisted aliases are displayed with `$ alh -b`


### Option usage

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

Listing non-blacklisted aliases in a formatted table can be done simply with `$ alh`, or `$alh -l`, where blacklisted aliases can be shown with `$ alh -b`. Attributes that do not fit into the column of a table are cut off cleanly with a `#`.

``` none
$ alh
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
| 16  | dir        | alex       | Windows home dir                                   |
| 26  |            | alp        | Alias project directory                            |
| 24  |            | mseed      | Minecraft seed project dir                         |
| 14  |            | projs      | Projects dir                                       |
| 22  |            | school     | School dir                                         |
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
| 17  |            | expl       | Opens Windows explorer in cwd                      |
| 0   |            | rel        | Reloads aliases                                    |
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
$ alh -b
+-----+------------+------------+----------------------------------------------------+
| ID  | Type       | Alias      | Description                                        |
+-----+------------+------------+----------------------------------------------------+
| 7   | git        | ga         | Add all files to git                               |
| 8   |            | gc         | git commit -m                                      |
| 21  |            | gcm        | Checkout master                                    |
| 10  |            | gpl        | git pull                                           |
| 9   |            | gpu        | git push                                           |
| 6   |            | gs         | git status                                         |
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

After the new alias has been written to `~/.bash_aliases`, it will have to be reloaded with either restarting the shell, or executing `source ~/.bash_aliases`, which of course can be an alias itself:

``` none
$ alh -n greeting "echo 'hello world'" util "Example alias"
$ greeting
greeting: command not found
$ rel # does 'source ~/.bash_aliases'
$ greeting
hello world
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

- Command line parsing for h, l, n, u, and b flags.
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
