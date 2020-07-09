import os
from time import ctime

def is_file(path):
    return os.path.exists(path)

def standard_output(username, msg, color=None):
    if color: return f"{CC('red')}>>{username}    {ctime()} \n{msg}"
    return f">>{username}    {ctime()} \n{msg}"

def encode_header_len(data, HEADER_LEN=10)->bytes:
    if isinstance(data, str): data = data.encode('utf-8')
    return f"{len(data) :< {HEADER_LEN}}".encode('utf-8')

def read_file(path):
    if not is_file(path): return None
    with open(path, 'rb') as file:
        return file.read()

def try_encode(msg):
    try:
        msg = msg.encode('utf-8')
    except:
        pass
    return msg

def try_decode(msg):
    try:
        msg = msg.decode('utf-8')
    except:
        pass
    return msg

def get_othername(username):
    if username == 'alice': return 'bob'
    return 'alice'