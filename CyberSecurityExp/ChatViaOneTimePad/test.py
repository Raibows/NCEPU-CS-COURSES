from cipher import *
from tools import *
from Crypto.PublicKey import RSA
from Crypto.Signature import PKCS1_v1_5
from Crypto.Hash import SHA

msg = "hello, how are you!aaaaaaaaaaaaaaaaaaa" * 2
msg_len = encode_header_len(msg)

alice = "alice"
bob = "bob"
generate_RSA(alice)
generate_RSA(bob)
generate_AES(alice)

"""
end to end encryption
1: client1生成RSA密钥对，私钥cs1，公开公钥cp1
2: client2生成RSA密钥对，私钥cs2，公开公钥cp2
3: client1利用AES生成对称密钥E，向server发送 [cp2(E) | cs1(hash(E))]
4: server转发至client2
5: client2利用私钥cs2，解密得对称密钥E，对E进行hash运算，利用公钥cp1解密得hash(E)进行比对
6: 之后发消息，使用 E[m | cs(hash(m))]，提供加密、签名、认证
"""


def decode_message(self, other, aes, rsa, msg_len):
    # msg_len = self.client.recv(self.HEADER_LEN).decode('utf-8')
    msg_len = msg_len.decode('utf-8')
    msg_len = int(msg_len.strip())


    aes_key = decrypt_RSA(self, rsa, is_public=False)
    aes_path = f"{self}/aes.pem"
    with open(aes_path, 'wb') as file:
        file.write(aes_key)
    aes_decode = decrypt_AES(aes_path, aes)

    msg = try_decode(aes_decode[0:msg_len])

    signature = aes_decode[msg_len:]

    if verify_with_RSA(alice, msg, signature):
        return msg
    else:
        return "wrong message"


if __name__ == '__main__':
    x = "123".encode('utf-8')
    print(x, len(x))
    # x = get_AES("bob")
    # print(len(x))
    #
    # en_hash_m = sign_with_RSA(alice, msg)
    #
    # temp = msg.encode('utf-8') + en_hash_m
    # print("AES before", len(temp))
    #
    # aes = encrypt_AES(f"{alice}/aes.pem", temp)
    # aes_len = encode_header_len(aes)
    # print("AES after", len(aes))
    #
    # rsa = encrypt_RSA(bob, get_AES(alice), is_public=True)
    #
    #
    #
    # temp = aes + encrypt_RSA(bob, get_AES(alice), is_public=True)
    # all_len = encode_header_len(temp)
    # print(len(temp), temp)
    #
    #
    #
    # print('below is decryption process')
    #
    # message = all_len + msg_len + aes_len + temp
    #
    # x = decode_message(bob, alice, aes, rsa, msg_len)
    # print(x)
    # print(x == msg)
