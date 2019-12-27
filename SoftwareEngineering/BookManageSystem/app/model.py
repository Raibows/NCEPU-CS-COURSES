import time
import locale
from app import db, login_manager
import datetime
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import UserMixin
from flask import session, flash
import datetime



class Role(db.Model):
    __tablename__ = 'Role'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    role_name = db.Column(db.String(10), primary_key=True)
    role_book_limit = db.Column(db.Integer)

    @staticmethod
    def get_roles_info():
        info = {
            'admin': {
                'book_limit': 100
            },
            'teacher': {
                'book_limit': 5
            },
            'default': {
                'book_limit': 3
            }
        }
        return info

    def __init__(self, role_name):
        info = Role.get_roles_info()
        self.role_name = role_name
        self.role_book_limit = info[role_name]['book_limit']

    @staticmethod
    def insert_roles():
        info = Role.get_roles_info()
        users = [Role(x) for x in info.keys()]
        result = Role.query.filter_by().all()
        for user in users:
            flag = True
            for r in result:
                if user.role_name == r.role_name:
                    flag = False
                    break
            if flag:
                db.session.add(user)
        db.session.commit()
        print('Role init successfully')



class User(db.Model, UserMixin):
    __tablename__ = 'User'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    user_id = db.Column(db.String(6), primary_key=True)
    user_name = db.Column(db.String(10), nullable=False)
    user_password_hash = db.Column(db.String(128), nullable=False)
    user_role_name = db.Column(db.String(10), db.ForeignKey('Role.role_name'))
    user_role = db.relationship('Role', backref='user')
    user_remain_book_num = db.Column(db.Integer)

    def __init__(self, id, name, password, role_name='default'):
        self.user_id = id
        self.user_name = name
        self.user_password_hash = generate_password_hash(password)
        result = Role.get_roles_info().keys()
        if role_name not in result:
            raise RuntimeError('role_name not exists in Role_info')
        self.user_role_name = role_name
        self.user_remain_book_num = Role.get_roles_info()[role_name]['book_limit']

    @staticmethod
    def insert_admin():
        result = User.query.filter_by(user_role_name='admin').all()
        if not result:
            admin = User('000000', '管理员', '000000', 'admin')
            db.session.add(admin)
            db.session.commit()
            print('insert the default admin, id=000000, password=000000')

    @staticmethod
    def insert_default_user():
        result = User.query.filter_by(user_role_name='default').all()
        if not result:
            default = User('123456', '普通测试', '123456')
            db.session.add(default)
            db.session.commit()
            print('insert the default user, id=123456, password=123456')

    @staticmethod
    def insert_teacher():
        result = User.query.filter_by(user_role_name='teacher').all()
        if not result:
            teacher = User('654321', '老师用户', '654321', 'teacher')
            db.session.add(teacher)
            db.session.commit()
            print('insert teacher user, id=654321, password=654321')


    def varify(self, password):
        return check_password_hash(self.user_password_hash, password)

    def get_id(self):
        return (self.user_id)

    def __repr__(self):
        info = f'{self.user_id}, {self.user_name}, {self.user_role_name}'
        return info

class Book_basic(db.Model):
    __tablename__ = 'Book_basic'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    book_basic_isbn = db.Column(db.String(13), primary_key=True)
    book_basic_author = db.Column(db.String(20), nullable=False)
    book_basic_name = db.Column(db.String(100), nullable=False)
    book_basic_num = db.Column(db.Integer, nullable=False) #标记实际存在的数量
    book_record_num = db.Column(db.Integer, nullable=False) #标记总数（包括丢失的
    book_basic_cover = db.Column(db.String(256), nullable=False)

    def __init__(self, isbn, author, name, num, cover='book-cover/default-cover.png'):
        # 使用构造方法，说明以前就没有这本书
        if not cover:
            cover = 'book-cover/default-cover.png'
        num = int(num)
        self.book_basic_isbn = isbn
        self.book_basic_author = author
        self.book_basic_name = name
        self.book_basic_num = num
        self.book_record_num = num
        self.book_basic_cover = cover




    def update_info(self, new_name=False, new_author=False, new_cover=False, update_num:int=0):
        # 使用此方法证明，以前有这本书，可以进行修改基本信息，添加新的数量
        try:
            update_num = int(update_num)
        except:
            raise RuntimeError(f'update_num 必须为整数, 但传入了{update_num}')
        if new_name:
            self.book_basic_name = new_name
        if new_author:
            self.book_basic_author = new_author
        if new_cover:
            self.book_basic_cover = new_cover
        begin_num = self.book_record_num + 1
        end_num = begin_num + update_num
        if self.book_basic_num + update_num > 999:
            flash('操作错误，图书数量超过上限999')
        else:
            self.book_basic_num += update_num
            self.book_record_num += update_num
            for i in range(begin_num, end_num):
                new = Book(self.book_basic_isbn, str(i))
                db.session.add(new)
            db.session.commit()


    @staticmethod
    def insert_origin_books():
        temp = Book_basic.query.count()
        if temp < 1:
            import csv, time
            start = time.clock()
            origin_books = r'app\static\book-cover\origin-info.csv'
            books_num = 0
            import sys
            with open(origin_books, 'r', encoding='utf-8') as file:
                reader = csv.reader(file)
                for i, line in enumerate(reader):
                    if i != 0:
                        isbn = line[3].replace('-', '')
                        cover = line[-1][1:].replace('\\', '/')
                        new_book_basic = Book_basic(isbn, line[1], line[0], line[2], cover=cover)
                        db.session.add(new_book_basic)
                        db.session.commit()
                        book_num = int(line[2]) + 1
                        books_num += int(line[2])
                        for j in range(1, book_num):
                            new_book = Book(isbn, str(j))
                            db.session.add(new_book)
                        db.session.commit()
            cost_time = time.clock() - start
            cost_time = round(cost_time, 2)
            print(f'初始化图书库完毕！耗时 {cost_time} 秒，共添加了 {i+1} 种图书共 {books_num} 本图书')

    def get_book_basic_status(self):
        temp = self.book
        num_all = len(temp) # 可借 + 已借出 + 丢失
        num_borrow = 0
        num_lost = 0
        num_remain = 0
        for book in temp:
            if book.book_borrowed:
                num_borrow += 1
            elif book.book_lost:
                num_lost += 1
            if book.book_borrowed == False and book.book_lost == False:
                num_remain += 1
        if num_all != (num_remain + num_lost + num_borrow):
            flash(f'{self.book_basic_isbn} 书籍统计出现错误！')
            raise RuntimeError(f'{self.book_basic_isbn} 书籍统计出现错误！')
        return (num_all, num_remain, num_borrow, num_lost)



class Book(db.Model):
    __tablename__ = 'Book'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    book_id = db.Column(db.String(16), primary_key=True)
    book_isbn = db.Column(db.String(13), db.ForeignKey('Book_basic.book_basic_isbn'))
    book_basic = db.relationship('Book_basic', backref='book')
    book_borrowed = db.Column(db.Boolean(), default=False)
    book_lost = db.Column(db.Boolean(), default=False)

    def __init__(self, book_isbn:str, book_id:str):
        self.book_isbn = book_isbn
        while len(book_id) != 3:
            book_id = '0' + book_id
        self.book_id = book_isbn + str(book_id)

    def get_this_book_status(self):
        if self.book_borrowed:
            return '未归还'
        if self.book_lost:
            return '已丢失'
        if self.book_borrowed == False:
            return '可借阅'

    def borrow_this_book(self, user_id):
        if self.book_lost == True:
            flash(f'该书籍 {self.book_id} 已经丢失')
            raise RuntimeError(f'该书籍 {self.book_id} 已经丢失')
        if self.book_borrowed == False:
            self.book_borrowed = True
            user = User.query.filter_by(user_id=user_id).first()
            if user and user.user_remain_book_num >= 0:
                new_borrow_log = Borrow_log(self.book_id, user_id)
                db.session.add(new_borrow_log)
                user.user_remain_book_num -= 1
                db.session.commit()
        else:
            flash(f'借书失败，该书 {self.book_id} 已经被借阅')

    def return_this_book(self):
        if self.book_lost == True:
            flash(f'该书籍 {self.book_id} 已经丢失')
            raise RuntimeError(f'该书籍 {self.book_id} 已经丢失')
        if self.book_borrowed:
            user = User.query.filter_by(user_id=self.borrow_log[0].borrow_user_id).first()
            user.user_remain_book_num += 1
            new_return_log = Return_log(self.book_id, self.borrow_log[0].borrow_user_id, self.borrow_log[0].borrow_time)
            db.session.add(new_return_log)
            self.book_borrowed = False
            db.session.delete(self.borrow_log[0])
            db.session.commit()
        else:
            flash(f'还书失败，该书 {self.book_id} 已经归还，未被借阅')

    def delete_this_book(self, user_id='000000'):
        if user_id != '000000':
            user = User.query.filter_by(user_id=user_id).first()
            if not user:
                raise RuntimeError(f'{user_id} 此人不存在，不能删除该书籍')
        # 首先归还此书，然后插入丢失记录
        if self.book_borrowed:
            self.return_this_book()
        new_lost_log = Lost_log(self.book_id, self.book_isbn, user_id)
        db.session.add(new_lost_log)
        db.session.commit()
        self.book_basic.book_basic_num -= 1
        self.book_lost = True
        db.session.commit()



class Borrow_log(db.Model):
    __tablename__ = 'Borrow_log'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    borrow_book_id = db.Column(db.String(16), db.ForeignKey('Book.book_id'), primary_key=True)
    borrow_book = db.relationship('Book', backref='borrow_log')
    borrow_user_id = db.Column(db.String(6), db.ForeignKey('User.user_id'))
    borrow_user = db.relationship('User', backref='borrow_log')
    borrow_time = db.Column(db.DateTime(), default=datetime.datetime.now())

    def __init__(self, booK_id, user_id):
        self.borrow_book_id = booK_id
        self.borrow_user_id = user_id
        self.borrow_time = datetime.datetime.now()

    def __repr__(self):
        info = f'{self.borrow_user_id}, {self.borrow_book_id}, {self.borrow_time}'
        return info

class Return_log(db.Model):
    __tablename__ = 'Return_log'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    return_sequence = db.Column(db.Integer, primary_key=True, autoincrement=True)
    return_book_id = db.Column(db.String(16), db.ForeignKey('Book.book_id'))
    return_book = db.relationship('Book', backref='return_log')
    return_user_id = db.Column(db.String(6), db.ForeignKey('User.user_id'))
    return_user = db.relationship('User', backref='return_log')
    return_time = db.Column(db.DateTime(), default=datetime.datetime.now())
    borrowed_time = db.Column(db.DateTime(), nullable=False)

    def __init__(self, book_id, user_id, borrowed_time):
        self.return_book_id = book_id
        self.return_user_id = user_id
        self.return_time = datetime.datetime.now()
        self.borrowed_time = borrowed_time


class Lost_log(db.Model):
    __tablename__ = 'Lost_log'
    __table_args__ = {'mysql_collate': 'utf8mb4_unicode_ci'}
    lost_sequence = db.Column(db.Integer, primary_key=True, autoincrement=True)
    lost_book_id = db.Column(db.String(16), nullable=False)
    lost_book_isbn = db.Column(db.String(13), db.ForeignKey('Book_basic.book_basic_isbn'))
    lost_book_basic = db.relationship('Book_basic', backref='lost_log')
    lost_user_id = db.Column(db.String(6), db.ForeignKey('User.user_id'))
    lost_user = db.relationship('User', backref='lost_log')
    lost_book_time = db.Column(db.DateTime(), default=datetime.datetime.now())

    def __init__(self, lost_book_id, lost_book_isbn, lost_user_id='000000'):
        check_temp = Book.query.filter_by(book_id=lost_book_id).first()
        if check_temp.book_borrowed or check_temp.book_lost:
            flash(f'该书籍 {lost_book_id} 尚未正确删除，请检查，无法增加删除记录')
        else:
            if not lost_user_id:
                lost_user_id = '000000'
            self.lost_book_id = lost_book_id
            self.lost_book_isbn = lost_book_isbn
            self.lost_user_id = lost_user_id
            self.lost_book_time = datetime.datetime.now()




@login_manager.user_loader
def load_user(user_id):
    return User.query.get(user_id)





