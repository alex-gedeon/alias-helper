import os
import datetime as dt

timestamp = dt.datetime.now().strftime("%d-%b-%Y-%H:%M:%S")
script_path = os.path.realpath(__file__)
base_path = os.path.dirname(os.path.dirname(script_path))

if not os.path.exists(f'{base_path}/local/'):
    os.mkdir(f'{base_path}/local/')
if not os.path.exists(f'{base_path}/local/backups/'):
    os.mkdir(f'{base_path}/local/backups/')
if not os.path.exists(f'{base_path}/local/{timestamp}'):
    os.mkdir(f'{base_path}/local/backups/{timestamp}')

backup_path = base_path + f'/local/backups/{timestamp}'

os.system(f'cat ~/.bash_aliases > {backup_path}/aliases')
os.system(f'cat {base_path}/local/aliases_unformatted.txt > {backup_path}/unformatted')
