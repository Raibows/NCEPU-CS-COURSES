from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Hash import SHA256
from Crypto.Signature import PKCS1_v1_5




def generate_RSA(username):
    key = RSA.generate(2048)
    private_key = key.export_key()
    file_out = open(f"{username}/RSA_private.pem", "wb")
    file_out.write(private_key)
    file_out.close()
    public_key = key.publickey().export_key()
    file_out = open(f"{username}/RSA_public.pem", "wb")
    file_out.write(public_key)
    file_out.close()

def generate_AES(username):
    key = get_random_bytes(16)
    file = open(f"{username}/aes.pem", "wb")
    file.write(key)
    file.close()

def encrypt_RSA(username, data, is_public=False):
    if isinstance(data, str): data = data.encode('utf-8')
    if is_public:
        key = get_pub_key(username)
    else:
        key = get_pri_key(username)
    cipher_rsa = PKCS1_OAEP.new(key)
    return cipher_rsa.encrypt(data)

def encrypt_AES(path, data):
    if isinstance(data, str): data = data.encode('utf-8')
    with open(path, 'rb') as file:
        key = file.read()
    cipher = AES.new(key, AES.MODE_EAX)
    ciphertext, tag = cipher.encrypt_and_digest(data)
    t = b''
    for x in (cipher.nonce, tag, ciphertext):
        t += x
    return t

def decrypt_RSA(username, ciphertext, is_public=True):
    if is_public:
        key = get_pub_key(username)
    else:
        key = get_pri_key(username)
    cipher_rsa = PKCS1_OAEP.new(key)
    if is_public: res = cipher_rsa.encrypt(ciphertext)
    else: res = cipher_rsa.decrypt(ciphertext)
    try:
        if isinstance(res, bytes): res = res.decode('utf-8')
    except:
        pass
    return res

def decrypt_AES(path, ciphertext):
    with open(path, 'rb') as file:
        key = file.read()
    nonce, tag, ciphertext = ciphertext[:16], ciphertext[16:32], ciphertext[32:]
    cipher = AES.new(key, AES.MODE_EAX, nonce)
    data = cipher.decrypt_and_verify(ciphertext, tag)
    try:
        if isinstance(data, bytes): data = data.decode('utf-8')
    except:
        pass
    return data


def mac_sha256(msg):
    if isinstance(msg, str): msg = msg.encode('utf-8')
    digest = SHA256.new()
    digest.update(msg)
    return digest

def sign_with_RSA(username, msg):
    key = get_pri_key(username)
    signer = PKCS1_v1_5.new(key)
    return signer.sign(mac_sha256(msg))

def verify_with_RSA(username, msg, signature):
    key = get_pub_key(username)
    signer = PKCS1_v1_5.new(key)
    return signer.verify(mac_sha256(msg), signature)

def get_AES(username):
    with open(f"{username}/aes.pem", 'rb') as file:
        return file.read()

def get_pub_key(username):
    with open(f"{username}/RSA_public.pem") as file:
        return RSA.import_key(file.read())

def get_pri_key(username):
    with open(f"{username}/RSA_private.pem") as file:
        return RSA.import_key(file.read())


if __name__ == '__main__':
    generate_RSA("bob")
    data = "hello123"
    t = encrypt_RSA("bob", data, is_public=True)
    t = decrypt_RSA("bob", t, is_public=False)
    print(t)

    print(sign_with_RSA("bob", data))
    t = sign_with_RSA("bob", data)
    print(verify_with_RSA("bob", data, t))