from subprocess import run
from os import getcwd, remove
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
    """Updates the project's version information and commits changes.

    This function automates the versioning process for a project. It increments
    the `micro` version number in the `src/pinfo.json` file, stages all pending
    changes, and then performs a Git commit. The new version string is
    formatted as `{MAJOR}.{MINOR}.{MICRO}:{COMMIT_HASH}`.

    The commit message is read from the `tools/cm.i` file, and this file is
    deleted after its content is used. The updated version data is committed
    along with all other staged changes. Finally, the function pushes the
    new commit to the remote repository.

    The function assumes the following file structure and dependencies:
    - A `src/pinfo.json` file containing the version information.
    - A `tools/cm.i` file that contains the commit message.
    - The Git command-line tool is installed and configured.

    Raises:
        FileNotFoundError: If 'src/pinfo.json' or 'tools/cm.i' cannot be found.
    """
    #    chdir('..')
    data = json_read('src/pinfo.json')

    run('git add -A')
    
    data['micro'] += 1
    
    msg = read_file('tools/cm.i')
    
    data['hash'] = get_commit_hash()
    
    cmtmsg = f"\"{data['major']}.{data['minor']}.{data['micro']}:{data['hash']} - {msg}\""
    
    json_write('src/pinfo.json',data)
    run('git add -A')
    run(f'git commit -m {cmtmsg}')
    run(f'git push')
if __name__ == '__main__':
    get_commit_hash()
    update_pinfo()



