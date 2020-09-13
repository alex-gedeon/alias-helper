import os

filepath = 'local/backups/13-Sep-2020-14:57:35' # input('enter path to backup folder: ').strip()
script_path = os.path.realpath(__file__)
base_path = os.path.dirname(os.path.dirname(script_path))

def add_unfomatted(line):
    with open(f'{base_path}/local/aliases_unformatted.txt', 'a') as outfile:
        outfile.write(line.strip() + '\n')
    print(f'{base_path}/local/aliases_unformatted.txt')

def add_alias(line):
    os.system(f'echo "{line.strip()}" >> ~/.bash_aliases')

with open(f'{filepath}/aliases') as alias_file:
    with open(f'{filepath}/unformatted') as unformatted_file:
        ulines = unformatted_file.readlines()
        for aline in alias_file:
            for uline in ulines:
                if not len(aline) or not len(uline):
                    continue
                if uline.split('#')[1] == aline.split(' ')[1].split('=')[0]:  # find unformatted aliases
                    add_unfomatted(uline)
            
            add_alias(aline)    
