# alias-helper

## Terminal based utility intended to streamline the usage of aliases: a fantastic way to optimize productivity

If you hate typing repetitive commands like `cd /mnt/c/....`, `explorer.exe .`, or simply like being able to easily open files through the terminal with annoying to reach executables, then you'll love being able to just create a new alias on the fly, restart the terminal, and simply type the short alias from then on to do your required task.

Current functionality:

- Command line parsing
- Prints a table to display aliases
- Create aliases locally (in ~/.bash_aliases file)
- Remove displayed aliases with blacklist
- View inverse blacklist

In development:

- Remove aliases from blacklist (currently manually delete from text file)

Future plans:

- Installation script
- Alias creation should fail if name has already been used, even if in blacklist
- Allow user to create and view variables with similar functionality
- Allow user to modify previously inputted type and description, maybe with override.txt, id#new_type#new_description. This should work even if you change information twice, since the program can just use whatever is farther along in the file
- Ability to change printed table size
