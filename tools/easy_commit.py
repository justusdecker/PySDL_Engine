"""
An easy to use commit tool

This updates:
    src/version.h
    src/hash.h

This needs to have two seperate files to show up correctly one my `elgato stream deck`

Usage:

I usually prefer to click one time on my `elgato stream deck` to run this.

"""
from subprocess import run
from os import getcwd, system, remove
from json import load, dumps
print(getcwd())
def json_read(filepath : str) -> dict | list:
    with open(filepath, 'r') as f:
        return load(f)

def json_write(filepath : str, data : dict | list):
    with open(filepath, 'w') as f:
        f.write(dumps(data))
def read_file(filepath : str):
    with open(filepath, 'r') as f:
        return f.read()


def get_terminal_result(cmd: str) -> str:
    return run(cmd, capture_output=True, text=True).stdout
     
def get_commit_hash(idm : int = 1) -> str:
    """ Gets the commit hash """
    return get_terminal_result(f"git log --pretty=format:'%h' -n {idm}").replace("\'",'')

def update_pinfo() -> str:
    """
    The new version format will be:
    {MAJOR}.{MINOR}.{MICRO}:{COMMIT_HASH}

    combined:
    1.0.4:abc123
    """
    #    chdir('..')
    data = json_read('../src/pinfo.json')

    run('git add -A')
    
    old, new = get_commit_hash(2).split("\n")[1], get_commit_hash()
    
    t_res: list[str] = get_terminal_result(f'git diff --shortstat {old} {new}').split(',')

    changes = sum([int(ch.split(' ')[1]) for ch in t_res])
    
    data['micro'] += int(changes)
    
    print(changes,t_res)
    
    msg = read_file('cm.i')
    
    cmtmsg = f"\"{data['major']}.{data['minor']}.{data['micro']}:{new} - {msg}\""
    
    remove('cm.i')
    
    json_write('../src/pinfo.json',data)
    run('git add -A')
    run(f'git commit -m {cmtmsg}')
    run(f'git push')
if __name__ == '__main__':
    system('get_current_commit_msg.vbs')
    get_commit_hash()
    update_pinfo()



