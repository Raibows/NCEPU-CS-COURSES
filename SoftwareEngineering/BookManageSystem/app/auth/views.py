from flask import render_template, redirect, url_for, flash, jsonify
from flask import request
from . import auth
import datetime
from app import db, app
from flask_login import login_required, current_user, login_user, logout_user
from ..model import User, Role, Book_basic, Book, Borrow_log, Lost_log, Return_log
from .forms import Insert_book_form, Return_book_form, Lend_book_form
from ..decorators import only_admin, online_required
import os
import datetime
from ..regexcheck import *




@auth.route('/delete_book_basic<isbn>', methods=['GET', 'POST'])
@online_required
@only_admin
def delete_book_basic(isbn):
    book_basic = Book_basic.query.filter_by(book_basic_isbn=isbn).first()
    if check_isbn(isbn) and book_basic:
        for book in book_basic.book:
            manage_delete_book(book.book_id)
            # 经过此操作，存在记录只剩下basic、book、return-log、lost-log
        for book in book_basic.book:
            logs = Return_log.query.filter_by(return_book_id=book.book_id).all()
            [db.session.delete(i) for i in logs]
            db.session.commit()

        logs = Lost_log.query.filter_by(lost_book_isbn=isbn).all()
        [db.session.delete(i) for i in logs]
        db.session.commit()

        book = Book.query.filter_by(book_isbn=isbn).all()
        [db.session.delete(i) for i in book]
        db.session.commit()

        book_basic = Book_basic.query.filter_by(book_basic_isbn=isbn).first()
        db.session.delete(book_basic)
        db.session.commit()

        flash(f'已经将ISBN为 {isbn} 的书籍所有信息成功删除！')
    else:
        flash(f'ISBN为 {isbn} 格式有误或该书籍不存在！')

    return r'http://127.0.0.1:5000/'





@auth.route('/return_this_book', methods=['POST'])
@online_required
@only_admin
def return_this_book():
    if request.form['borrowed_book_id']:
        borrowed_book_id = request.form['borrowed_book_id']
        borrowed_book = Book.query.filter_by(book_id=borrowed_book_id, book_lost=False).first()
        if borrowed_book:
            borrowed_book.return_this_book()
            message_info = f'书籍id为 {borrowed_book_id} 已经于 {datetime.datetime.now()} 成功还书！'
        else:
            message_info = f'书籍id为 {borrowed_book_id} 未被借或者已经丢失，无法归还'
            raise RuntimeError(message_info)

        return jsonify(message_info = message_info)






@auth.route('/return_book_page', methods=['GET', 'POST'])
@online_required
@only_admin
def return_book_page():
    form = Return_book_form()
    info_label_1 = []
    info_1 = []
    info_label_2 = []
    info_2 = []
    if form.validate_on_submit():
        if not(form.book_id.data or form.user_id.data):
            flash('要么填写归还书籍id，要么查询用户借阅记录，两者不能同时为空')
        else:
            if form.book_id.data:
                temp = Borrow_log.query.filter_by(borrow_book_id=form.book_id.data).first()
                if temp:
                    info_label_1 = ['借阅人姓名', '借阅人用户id', '借阅书籍名称', '借阅书籍id', '借阅书籍时间']
                    info_1 = [
                        temp.borrow_user.user_name,
                        temp.borrow_user_id,
                        temp.borrow_book.book_basic.book_basic_name,
                        temp.borrow_book_id,
                        temp.borrow_time
                    ]
                else:
                    flash('操作失败，该书未被借阅')
            if form.user_id.data:
                temp_all = Borrow_log.query.filter_by(borrow_user_id=form.user_id.data).all()
                if temp_all:
                    info_label_2 = ['借阅人姓名', '借阅人用户id', '借阅书籍名称', '借阅书籍id', '借阅书籍时间']
                    for temp in temp_all:
                        info_2.append(
                            [
                                temp.borrow_user.user_name,
                                temp.borrow_user_id,
                                temp.borrow_book.book_basic.book_basic_name,
                                temp.borrow_book_id,
                                temp.borrow_time
                            ]
                        )
                else:
                    flash('未查询到该用户的借阅记录')
    return render_template('return-book.html', info_1=info_1, info_2=info_2, form=form,
                           info_label_1=info_label_1, info_label_2=info_label_2)




@auth.route('/manage_book', methods=['POST', 'GET'])
@online_required
@only_admin
def manage_book():
    if request.method == 'GET':
        return render_template('manage-book.html')
    file1 = request.files.get('file-1')
    isbn1 = request.form.get('isbn-1')
    name1 = request.form.get('name-1')
    author1 = request.form.get('author-1')
    num1 = request.form.get('num-1')
    book_id = request.form.get('book_id')
    file2 = request.files.get('file-2')
    isbn2 = request.form.get('isbn-2')
    name2 = request.form.get('name-2')
    author2 = request.form.get('author-2')
    num2 = request.form.get('num-2')
    message = None
    if request.form.get('category'):
        if request.form.get('category') == 'delete':
            message = manage_delete_book(book_id)
        elif request.form.get('category') == 'insert':
            message = manage_insert_book(isbn1, name1, author1, num1, file1)
        elif request.form.get('category') == 'modify':
            message = manage_modify_book(isbn2, name2, author2, num2, file2)
        if message:
            flash(message)
    return render_template('manage-book.html')





def manage_delete_book(book_id):
    if check_book_id(book_id):
        lost_book = Book.query.filter_by(book_id=book_id, book_lost=False).first()
        if lost_book:
            # 该书未被借，直接删除；该书正被借着，先还书，再删除
            # 将book_basic的basic—num-1，但record-num保持不变
            lost_user_id = None
            if lost_book.book_borrowed:
                lost_user_id = lost_book.borrow_log[0].borrow_user_id
                lost_book.return_this_book()
            lost_user_id = '000000' if lost_user_id == None else lost_user_id  # 默认让管理员背锅
            lost_book.delete_this_book(lost_user_id)
            lost_book_basic = Book_basic.query.filter_by(book_basic_isbn=lost_book.book_isbn).first()
            info = lost_book_basic.get_book_basic_status()
            return f'删除书籍 {book_id} 成功，同本书籍总共数量{info[0]}，当前可借数量{info[1]}，当前借出数量{info[2]}，当前丢失数量{info[3]}'
        else:
            return '该书籍编号不存在或已经被删除，请核实'
    else:
        return '书籍id必须填写，且为16位数字'

def manage_insert_book(isbn, name, author, num:int, cover=None):
    # 插入一个新图书basic
    try:
        num = int(num)
    except:
        return '数量格式错误，请填写正确的阿拉伯数字'
    if check_isbn(isbn) and name and author and num <= 999 and num > 0:
        temp = Book_basic.query.filter_by(book_basic_isbn=isbn).first()
        if temp:
            return f'书籍 {isbn} 已经存在，请不要重复添加，想要修改信息可以选择修改功能'
        if cover:
            print('hhhfielnaem', cover.filename)
            if allowed_file(cover.filename) == False:
                return '请上传正确的图片，格式为jpg或者png'
            cover_name = hash(cover.filename) + hash(datetime.datetime.now())
            cover_name = str(cover_name)
            cover_path = os.path.join(app.config['COVER_URL_PATH'], cover_name)
            print(os.path.join(app.config['UPLOAD_FOLDER'], cover_name))
            cover.save(os.path.join(app.config['UPLOAD_FOLDER'], cover_name))
        else:
            cover_path = None
        new_book_basic = Book_basic(isbn, author, name, num, cover_path)
        db.session.add(new_book_basic)
        db.session.commit()
        for i in range(1, num + 1):
            new_book = Book(isbn, str(i))
            db.session.add(new_book)
        db.session.commit()
        new_book_basic = Book_basic.query.filter_by(book_basic_isbn=isbn).first()
        info = new_book_basic.get_book_basic_status()
        return f'新增书籍 {isbn} 成功，同本书籍总共数量{info[0]}，当前可借数量{info[1]}，当前借出数量{info[2]}，当前丢失数量{info[3]}'
    else:
        return '表格信息需填写完整，且isbn格式为13位整数，书籍数量不超过999且大于0'


def manage_modify_book(isbn, name, author, update_num:int, cover=None):
    # 修改已经存在的图书basic
    if not update_num:
        update_num = 0
    else:
        try:
            update_num = int(update_num)
        except:
            return '数量格式错误，请填写正确的阿拉伯数字'
    if check_isbn(isbn) == False:
        return 'isbn填写错误，isbn为13位整数'
    old_book_basic = Book_basic.query.filter_by(book_basic_isbn=isbn).first()
    if old_book_basic:
        if old_book_basic.book_basic_num + update_num > 999:
            return f'该书籍已经有 {old_book_basic.book_basic_num} 本书，总数量不能超过999本，新增数量需不超过 {999-old_book_basic.book_basic_num}'
        if cover:
            if allowed_file(cover.filename) == False:
                return '请上传正确的图片，格式为jpg或者png'
            cover_name = hash(cover.filename) + hash(datetime.datetime.now())
            cover_name = str(cover_name)
            cover_path = os.path.join(app.config['COVER_URL_PATH'], cover_name)
            cover.save(os.path.join(app.config['UPLOAD_FOLDER'], cover_name))
        else:
            cover_path = None
        old_book_basic.update_info(new_name=name, new_author=author, new_cover=cover_path, update_num=update_num)
        info = old_book_basic.get_book_basic_status()
        message1 = f'修改书籍 {isbn} 成功，同本书籍总共数量{info[0]}，当前可借数量{info[1]}，当前借出数量{info[2]}，当前丢失数量{info[3]}，'
        message2 = f'新书籍名称为 {old_book_basic.book_basic_name}，作者为 {old_book_basic.book_basic_author}'
        return message1 + '\n' + message2
    else:
        return f'书籍 {isbn} 不存在，无法修改'
