import re
from app import ALLOWED_EXTENSIONS

'''
只检查格式上合不合法
不保证数据库中的存在
'''


def check_isbn(isbn) -> bool:
    print(isbn)
    if not isbn:
        return False
    x = re.search('^[0-9]{13}$', isbn)
    return True if x else False

def check_book_id(book_id) -> bool:
    if not book_id:
        return False
    x = re.search('^[0-9]{16}$', book_id)
    return True if x else False

def check_user_id(user_id) -> bool:
    if not user_id:
        return False
    x = re.search('^[0-9]{6}$', user_id)
    return True if x else False

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS