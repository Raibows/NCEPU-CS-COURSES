import socket
import select
from tools import *
from queue import Queue
import threading
import time
import sys
import pickle

class User():
    def __init__(self, username, password, register_date):
        if isinstance(username, bytes): username = username.decode('utf-8')
        if isinstance(password, bytes): password = password.decode('utf-8')
        if isinstance(register_date, bytes): register_date = register_date.decode('utf-8')
        self.username = username
        self.password = password
        self.register_date = register_date

class TCPServer():
    def __init__(self, addr='127.0.0.1', port=5000, max_req=10, HEADER_LEN=10):
        self.addr = (addr, port)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(self.addr)
        self.server.listen(max_req)
        self.HEADER_LEN = HEADER_LEN
        self.sockets_list = [self.server]
        self.users = {}
        self.clients_id = {}
        self.clients_sk = {}
        self.messages = Queue()


    def encode_msg(self, msg:tuple)->bytes:
        msg_type = msg[0].encode('utf-8')
        sender = msg[1].encode('utf-8')
        receiver = msg[2].encode('utf-8')
        message = try_encode(msg[3])
        timestamp = msg[4].encode('utf-8')
        data = encode_header(sender) + sender + encode_header(receiver) + receiver + \
        encode_header(msg_type) + msg_type + encode_header(message) + message + encode_header(timestamp) + timestamp
        return data

    def receive_msg(self, client:socket.socket):
        sender = receive_data(client, decode_flag=True)
        receiver = receive_data(client, decode_flag=True)
        msg_type = receive_data(client, decode_flag=True)
        msg = receive_data(client)
        timestamp = receive_data(client, decode_flag=True)
        return (msg_type, sender, receiver, msg, timestamp)

    def broadcast(self):
        while True:
            if not self.messages.empty():
                data = self.messages.get()
                if data[2] not in self.users: continue # receiver not exits
                if data[2] not in self.clients_id: # receiver offline
                    self.messages.put(data)
                    time.sleep(0.8)
                    continue
                print(f"{get_time()} Broadcast from {data[1]} to {data[2]} msg_type {data[0]} msg{data[3][:10]}")
                try:
                    self.clients_id[data[2]].sendall(self.encode_msg(data))
                except Exception as e:
                    print(f"{get_time()} ERROR when broadcast {e}")
                    self.del_socket(self.clients_id[data[2]])
                    self.messages.put(data)
            else: time.sleep(0.5)

    def del_socket(self, sk):
        self.sockets_list.remove(sk)
        if sk in self.clients_sk:
            del self.clients_id[self.clients_sk[sk]]
            del self.clients_sk[sk]
        try:
            sk.close()
        except:
            pass

    def handle_register(self, client_sk:socket.socket, data):
        if data[1] in self.users:
            res = 'False'
            print(f"{get_time()} New Register failed from {client_sk.getpeername()} username {data[1]}")
        else:
            self.users[data[1]] = User(data[1], data[3].decode('utf-8'), data[4])
            print(f"{get_time()} New Register success from {client_sk.getpeername()} username {data[1]}")
            res = 'True'
        res = encode_header(res) + res.encode('utf-8')
        client_sk.sendall(res)
        # client_sk.close()

    def handle_login(self, client_sk:socket.socket, data):
        res = 'False'
        if data[1] not in self.users:
            res = 'False'
            print(f"{get_time()} Login failed from {client_sk.getpeername()} username {data[1]}")
        elif data[3].decode('utf-8') == self.users[data[1]].password:
            res = 'True'
            self.clients_id[data[1]] = client_sk
            self.clients_sk[client_sk] = data[1]
            print(f"{get_time()} Login success from {client_sk.getpeername()} username {data[1]}")
        res = encode_header(res) + res.encode('utf-8')
        client_sk.sendall(res)
        # if res == 'False': client_sk.close()

    def handle_search(self, client_sk:socket.socket, data):
        self.clients_id[data[1]] = client_sk
        username = data[3].decode('utf-8')
        if username in self.users:
            res = 'True'
        else: res = 'False'
        print(f"{get_time()} Search {res} from {client_sk.getpeername()} username {data[1]}")
        res = encode_header(res) + res.encode('utf-8')
        client_sk.sendall(res)

    def handle_quit(self, client_sk:socket.socket):
        print(f"{get_time()} Closed connection from {client_sk.getpeername()} user quit")
        self.del_socket(client_sk)

    def listening(self):
        print(f"{get_time()} Server {self.addr[0]}:{self.addr[1]} is running!")
        while True:
            read_sockets, _, exception_sockets = select.select(self.sockets_list, [], self.sockets_list)
            for sk in read_sockets:
                if sk == self.server:
                    client_sk, client_addr = self.server.accept()
                    self.sockets_list.append(client_sk)
                    print(f"{get_time()} Accept connection from {client_sk.getpeername()}")
                else:
                    data = self.receive_msg(sk)
                    if None in data: continue
                    elif data[0] == 'quit':
                        self.handle_quit(sk)
                    elif data[0] == 'register':
                        self.handle_register(sk, data)
                    elif data[0] == 'login':
                        self.handle_login(sk, data)
                    elif data[0] == 'search':
                        self.handle_search(sk, data)
                    else:
                        print(f"{get_time()} Received from {data[1]} to {data[2]} msg_type {data[0]} msg{data[3][:10]}")
                        self.messages.put(data)

            for sk in exception_sockets:
                print(f"Closed connection from {sk.getpeername()} because of socket exception")
                self.del_socket(sk)


    def write_data(self):
        print(f"{get_time()} Have written user data to server/log.dat")
        if not file_exist('server'): os.mkdir('server')
        with open('server/log.dat', 'wb') as file:
            pickle.dump(self.users, file)

    def load_data(self):
        if file_exist('server/log.dat'):
            with open('server/log.dat', 'rb') as file:
                self.users = pickle.load(file)
            print(f"{get_time()} Have loaded user data")
            return True
        else: return False

    def generate_test_data(self):
        print(f"{get_time()} Generated test users from i=0 to 9 account=useri password=useri")
        for i in range(10):
            i = str(i)
            self.users['user'+i] = User('user'+i, 'user'+i, time.time())

    def run(self):
        if not self.load_data(): self.generate_test_data()
        listen_thread = threading.Thread(target=self.listening)
        listen_thread.daemon = True
        listen_thread.start()
        broadcast_thread = threading.Thread(target=self.broadcast)
        broadcast_thread.daemon = True
        broadcast_thread.start()

        try:
            while True:
                time.sleep(1)
        except:
            self.write_data()
            sys.exit()








if __name__ == '__main__':
    server = TCPServer()
    server.run()

