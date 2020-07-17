import os

os.system("cat ~/.bash_aliases > local/aliases_raw.txt")

script_path = os.path.dirname(os.path.realpath(__file__))

base_path = "/".join(script_path.split('/')[:-1])
# or lol
base_path = script_path[:-script_path[::-1].index("/")-1]

alias_text = open(f'{base_path}/local/aliases_raw.txt').readlines()

print(alias_text)
