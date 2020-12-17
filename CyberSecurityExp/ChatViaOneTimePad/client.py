import socket
import errno
import sys
from time import ctime
import threading
from tools import *
from gui import ClinetGUI
from cipher import *



class TCPClient():
    def __init__(self, server_addr=('127.0.0.1', 5000), HEADER_LEN=10):
        self.gui = ClinetGUI()
        self.username = self.gui.run_login()
        self.server_addr = server_addr
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect(server_addr)
        self.HEADER_LEN = HEADER_LEN
        self.client.setblocking(False)
        data = f"{len(self.username.encode('utf-8')) :< {HEADER_LEN}}" + self.username
        self.client.send(data.encode('utf-8'))
        self.output = self.gui.output
        self.stop_signal = False
        generate_RSA(self.username)


    def decode_message(self, username):
        all_len = self.client.recv(self.HEADER_LEN).decode('utf-8')
        msg_len = self.client.recv(self.HEADER_LEN).decode('utf-8')
        msg_len = int(msg_len.strip())

        aes_header = self.client.recv(self.HEADER_LEN).decode('utf-8')
        aes_len = int(aes_header.strip())
        aes = self.client.recv(aes_len)

        rsa_header = self.client.recv(self.HEADER_LEN).decode('utf-8')
        rsa_len = int(rsa_header.strip())
        rsa = self.client.recv(rsa_len)

        aes_key = decrypt_RSA(self.username, rsa, is_public=False)
        aes_path = f"{self.username}/aes.pem"
        with open(aes_path, 'wb') as file:
            file.write(aes_key)
        aes_decode = decrypt_AES(aes_path, aes)
        aes_decode = try_encode(aes_decode)

        msg = aes_decode[0:msg_len]
        msg = try_decode(msg)
        if verify_with_RSA(username, msg, aes_decode[msg_len:]):
            return msg
        return "Message has been modified!"


    def encode_message(self, msg):
        msg_len = encode_header_len(msg, self.HEADER_LEN)
        generate_AES(self.username)
        rsa_hash_m = sign_with_RSA(self.username, msg)
        msg = try_encode(msg)
        msg_rsa_hash_m = msg +rsa_hash_m
        aes = encrypt_AES(f"{self.username}/aes.pem", msg_rsa_hash_m)
        aes_len = encode_header_len(aes, self.HEADER_LEN)
        rsa = encrypt_RSA(get_othername(self.username), get_AES(self.username), is_public=True)
        rsa_len = encode_header_len(rsa, self.HEADER_LEN)

        temp = msg_len + aes_len + aes + rsa_len + rsa
        all_len = encode_header_len(temp, self.HEADER_LEN)

        return all_len+temp



    def receive_msg(self):
        while True and not self.stop_signal:
            try:
                while True:
                    username_header = self.client.recv(self.HEADER_LEN).decode('utf-8')
                    if not len(username_header):
                        self.output("Connection closed by the Server")
                        sys.exit()
                    username_len = int(username_header.strip())
                    username = self.client.recv(username_len).decode('utf-8')
                    msg = self.decode_message(username)
                    self.output(standard_output(username, msg))


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
            msg = self.gui.text_value.get('text')
            if msg.empty(): continue
            msg = msg.get()
            if msg and len(msg) > 0:
                self.output(standard_output(self.username, msg))
                if is_file(msg): msg = read_file(msg)
                msg = self.encode_message(msg)
                # print(msg)
                self.client.send(msg)





    def run(self):
        send_thread = threading.Thread(target=self.send_msg)
        send_thread.start()
        recv_thread = threading.Thread(target=self.receive_msg)
        recv_thread.start()
        self.gui.run_chat()
        self.stop_signal = True







if __name__ == '__main__':
    client = TCPClient()
    client.run()
