# alias-helper

## Terminal based utility intended to streamline the usage of aliases: a fantastic way to optimize productivity

After typing repetitive commands like `$ cd ..`, `$ cd ../..`, `$ explorer.exe .`, and spending cumulative hours typing long `$ cd /mnt/c/Projects/.....` commands to get to my working directories, I decided to make this utility to make repetitive commands much more manageable through aliases.

What are aliases?

An alias is simply another name for something, where in this case it refers to another name for a complicated instruction. For example, it is quite tedious to have to constantly type a long command such as  
`$ cd /mnt/c/Projects/foo/bar/foo_bar/bar_foo/foo_bar_foo/target`  
to get to a project directory, when with an alias, you can quickly set it up (in ~/.bash_aliases) to execute the command with another name, such as `$ example`. This can be done manually with `$ echo "alias example='{long command}'" >> ~/.bash_aliases`, or through editing the file in an editor like vim, but these methods make it hard to keep track of current and relevant aliases when, like me, you accumulate dozens of aliases and find that parsing through the output of `$ alias` is just too inefficient.

That's what this utility aims to solve. I intend to create a more user-friendly system to manage aliases, by assigning user-inputted tags to them through types and descriptions, and printing out an organized table which summarizes the aliases created to date.

Installation:

- Install the utility with `$ make install` to create the necessary directory and compile the table printing executable.
- Run the overall manager with `$ ./bin/alias_manager.sh`. May need to give the scripts permission first, such as with `$ chmod +x bin/*`
- You can run the individual components, `view_aliases.sh` and `create_alias.sh` separately, and I'd recommend making aliases for all three scripts to get the most out of the utility.

Example usage (creates an alias for calling the alias manager script):

```$ pwd
/mnt/c/Projects/alias-helper
$ ./bin/alias_manager.sh
Alias Helper v. 1.0```

`Enter command (enter h for help):`  
`$ c`  

`---NEW ALIAS CREATION---`  
`Enter q at any time to exit.`  

`Enter the alias type (must be one word):`  
`This can be any string, like directory, online, program, etc.`  
`$ program`  

`Enter the alias you wish to substitute the command for (must be one word)`  
`$ alman`  

`Enter the command to substitute (spaces allowed, format strings carefully)`  
`$ /mnt/c/Projects/alias-helper/bin/alias_manager.sh`  

`Enter a description for the alias (spaces allowed)`  
`Open alias manager` (thus allowing the creation of aliases by aliases)  

`Enter command (enter h for help):`  
`$ q`  
`$ exit` (restart terminal)  
`$ cd ~` (to show aliases work anywhere)  
`$ alman`  
`Alias Helper v. 1.0` (now you can call the manager from anywhere!)  

`Enter command (enter h for help):`  
$ q

Current functionality:

- Command line parsing
- Prints a table to display aliases
- Create aliases locally (in ~/.bash_aliases file)
- Remove displayed aliases with blacklist
- View inverse blacklist

In development:

- Remove aliases from blacklist (currently just manually delete idsfrom text file, where the id is the line (0 indexed) of the entry in /local/aliases_unformatted.txt)

Future plans:

- Installation script
- Alias creation should fail if name has already been used, even if in blacklist
- Allow user to create and view variables with similar functionality
- Allow user to modify previously inputted type and description, maybe with override.txt, id#new_type#new_description. This should work even if you change information twice, since the program can just use whatever is farther along in the file
- Ability to change printed table size
- Blacklist multiple aliases at once
- Load in ~/.bash_aliases and populate unformatted aliases and variables with user input, effectively restarting the system
