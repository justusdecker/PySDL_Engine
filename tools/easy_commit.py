from json import load, dumps
from subprocess import Popen
PINFO = 'src/pinfo.json'

type _data = str | dict | list | None
def f_handler(filepath: str, mode: str,data: _data = None) -> _data:
    with open(filepath, mode[0]) as f:
        match mode:
            case 'r': return f.read()
            case 'rj': return load(f)
            case 'w': f.write(data)
            case 'wj': f.write(dumps(data))

def update_pinfo() -> str:
    #Read Data
    data: dict = f_handler(PINFO,'rj')
    
    #Update Data
    data['micro'] += 1
    
    # Write Data
    f_handler('./tools/cmtmsg.i','w',f"{data['major']}.{data['minor']}.{data['micro']}")
    f_handler(PINFO,'wj',data)
if __name__ == '__main__':
    Popen('./tools/get_current_commit_msg.vbs')
    update_pinfo()