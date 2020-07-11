import socket
import errno
import sys
import time
import threading
from queue import Queue, PriorityQueue
from tools import *



class TCPClient():
    def __init__(self, server_addr=('127.0.0.1', 5000), HEADER_LEN=10):
        self.send_queue = PriorityQueue()
        self.server_addr = server_addr
        self.HEADER_LEN = HEADER_LEN
        self.stop_signal = False
        self.password = None
        self.username = None
        self.receive_queue = None
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect(self.server_addr)
        self.client.setblocking(False)
        self.thread_pause = False
        self.output_func = None

    def connect_to_server(self):
        return None
        try:
            self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client.connect(self.server_addr)
            self.client.setblocking(False)
        except:
            return False
        return True

    def register(self, username, password):
        self.connect_to_server()
        data = self.encode_message('None', 'register', password, str(time.time()), username)
        self.client.sendall(data)
        while True:
            try:
                res = receive_data(self.client)
                if res: break
            except:
                continue
        return eval(res.decode('utf-8'))

    def login(self, username, password):
        self.connect_to_server()
        data = self.encode_message('None', 'login', password, str(time.time()), username)
        self.client.sendall(data)
        while True:
            try:
                res = receive_data(self.client)
                if res: break
            except:
                continue
        res = eval(res.decode('utf-8'))
        if res:
            self.username = username
            self.password = password
            return True
        else: return False

    def search_user_exist(self, username):
        self.thread_pause = True
        data = self.encode_message('None', 'search', username, str(time.time()))
        self.client.sendall(data)
        while True:
            try:
                res = receive_data(self.client)
                if res: break
            except:
                continue
        res = eval(res.decode('utf-8'))
        self.thread_pause = False
        return res

    def quit_from_server(self):
        data = self.encode_message('None', 'quit', 'None', str(time.time()), 'None')
        self.client.sendall(data)
        return None

    def encode_message(self, receiver, msg_type, message, timestamp, username=None):
        if username is None: username = self.username
        if msg_type == 'pic':
            data = encode_header(username) + username.encode('utf-8') + encode_header(receiver) + \
                   receiver.encode('utf-8') + encode_header(msg_type) + msg_type.encode('utf-8') + \
                   encode_header(message) + message + encode_header(timestamp) + str(timestamp).encode('utf-8')
        else:
            data = encode_header(username) + username.encode('utf-8') + encode_header(receiver) + \
                receiver.encode('utf-8') + encode_header(msg_type) + msg_type.encode('utf-8') + \
                encode_header(message) + message.encode('utf-8') + encode_header(timestamp) + str(timestamp).encode('utf-8')
        return data


    def receive_msg(self):
        time.sleep(2)
        while True and not self.stop_signal:
            try:
                while True:
                    if self.thread_pause: continue
                    sender_header = self.client.recv(self.HEADER_LEN).decode('utf-8')
                    if not len(sender_header):
                        print("Connection closed by the Server")
                        sys.exit()
                    sender = self.client.recv(int(sender_header.strip())).decode('utf-8')
                    receiver = receive_data(self.client, decode_flag=True)
                    msg_type = receive_data(self.client, decode_flag=True)
                    msg = receive_data(self.client)
                    timestamp = receive_data(self.client, decode_flag=True)
                    # print(sender, receiver, msg_type, msg, timestamp)
                    self.receive_queue.put(MessageNode(msg_type, timestamp, msg, sender, receiver))


            except IOError as e:
                if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                    print('Reading error', str(e))
                    sys.exit()
                continue

            except Exception as e:
                print("General error", e)
                sys.exit()


    def send_msg(self):
        while True and not self.stop_signal:
            if self.send_queue.empty():
                time.sleep(0.3)
                continue
            msg:MessageNode = self.send_queue.get()
            if msg:
                data = self.encode_message(msg.receiver, msg.msg_type, msg.msg, msg.timestamp)
                while True:
                    try:
                        self.client.sendall(data)
                        break
                    except Exception as e:
                        print(f"{get_time()} ERROR", e)



    def run(self, receive_queue):
        self.receive_queue = receive_queue
        send_thread = threading.Thread(target=self.send_msg)
        send_thread.start()
        recv_thread = threading.Thread(target=self.receive_msg)
        recv_thread.start()







if __name__ == '__main__':
    pass
