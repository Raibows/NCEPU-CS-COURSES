import socket
import select
from time import ctime


class TCPServer():
    def __init__(self, addr='127.0.0.1', port=5000, max_req=5, HEADER_LEN=10):
        self.addr = (addr, port)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(self.addr)
        self.server.listen(max_req)
        self.HEADER_LEN = HEADER_LEN
        self.sockets_list = [self.server]
        self.clients = {}

    def receive_msg(self, client:socket.socket):
        try:
            header = client.recv(self.HEADER_LEN)
            if not len(header): return None
            msg_len = int(header.decode('utf-8').strip())
            return [header, client.recv(msg_len)]
        except:
            return None

    def broadcast(self, origin_sk:socket.socket, msg):
        user = self.clients[origin_sk]
        msg = user[0] + user[1] + msg[0] + msg[1]
        for client in self.clients:
            if client != origin_sk:
                client.send(msg)
                print(f"{ctime()} Broadcast message {msg}")

    def run(self):
        print(f"{ctime()} Server {self.addr[0]}:{self.addr[1]} is running!")
        while True:
            read_sockets, _, exception_sockets = select.select(self.sockets_list, [], self.sockets_list)
            for sk in read_sockets:
                if sk == self.server:
                    client_sk, client_addr = self.server.accept()
                    user = self.receive_msg(client_sk)
                    if user == None: continue
                    self.sockets_list.append(client_sk)
                    self.clients[client_sk] = user
                    print(f'{ctime()} Accepted new connection from {client_addr[0]}:{client_addr[1]} '
                          f"username {user[1].decode('utf-8')}")
                else:
                    msg = self.receive_msg(sk)
                    if msg == None:
                        print(f"{ctime()} Closed connection from {self.clients[sk][1].decode('utf-8')}")
                        self.sockets_list.remove(sk)
                        del self.clients[sk]
                        continue
                    else:
                        print(f"{ctime()} Received message from {self.clients[sk][1].decode('utf-8')} message {msg[1]}")
                        self.broadcast(sk, msg)
            for sk in exception_sockets:
                self.sockets_list.remove(sk)
                del self.clients[sk]








if __name__ == '__main__':
    server = TCPServer()
    server.run()

