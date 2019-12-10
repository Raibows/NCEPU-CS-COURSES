from flask import render_template, redirect, url_for, flash, jsonify
from flask import request
from . import auth
import datetime
from app import db
from flask_login import login_required, current_user, login_user, logout_user
from ..model import User, Role, Book_basic, Book, Borrow_log, Lost_log, Return_log
from .forms import Insert_book_form, Return_book_form, Lend_book_form
from ..decorators import only_admin, online_required




@auth.route('/manage_book', methods=['GET', 'POST'])
@online_required
@only_admin
def manage_book():
    form1 = Insert_book_form()
    flag1 = False
    if form1.validate_on_submit():
        if form1.category.data == 'insert':
            temp = Book_basic.query.filter_by(book_basic_isbn=form1.isbn.data).first()
            if temp:
                temp.update(name=form1.name.data, author=form1.author.data, update_num=form1.update_num.data)
                flag1 = True
            else:
                if not(form1.isbn.data and form1.author.data and form1.name.data and form1.update_num.data):
                    flash('该书籍没有库存，为新增书籍，必须将信息全部填写完整')
                else:
                    new_book_basic = Book_basic(form1.isbn.data, form1.author.data, form1.name.data, form1.update_num.data)
                    db.session.add(new_book_basic)
                    db.session.commit()
                    num = int(form1.update_num.data)
                    for i in range(1, num + 1):
                        new_book = Book(form1.isbn.data, str(i))
                        db.session.add(new_book)
                    db.session.commit()
                    flag1 = True
            if flag1:
                temp = Book_basic.query.filter_by(book_basic_isbn=form1.isbn.data).first()
                info = temp.get_book_basic_status()
                info = f'增加书籍 {temp.book_basic_name} 成功，当前总共数量{info[0]}，当前剩余数量{info[1]}，当前借出数量{info[2]}，当前丢失数量{info[3]}'
                flash(info)

        elif form1.category.data == 'delete':
            if form1.book_id.data:
                lost_book = Book.query.filter_by(book_id=form1.book_id.data).first()
                if lost_book:
                    # 该书未被借，直接删除；该书正被借着，先还书，再删除
                    # 将book_basic的basic—num-1，但record-num保持不变
                    lost_user_id = None
                    if lost_book.book_borrowed:
                        lost_user_id = lost_book.borrow_log.borrow_user_id
                        lost_book.return_this_book()
                    lost_book_return_log = Return_log.query.filter_by(return_book_id=form1.book_id.data).all()
                    if lost_book_return_log:
                        for log in lost_book_return_log:
                            db.session.delete(log)
                        db.session.commit()
                    lost_book_isbn = lost_book.book_isbn
                    lost_book_basic = Book_basic.query.filter_by(book_basic_isbn=lost_book_isbn).first()
                    lost_book_basic.book_basic_num -= 1
                    db.session.commit()
                    db.session.delete(lost_book)
                    db.session.commit()
                    new_lost_log = Lost_log(form1.book_id.data, lost_book_isbn, lost_user_id)
                    db.session.add(new_lost_log)
                    db.session.commit()
                    lost_book_basic = Book_basic.query.filter_by(book_basic_isbn=lost_book_isbn).first()
                    info = lost_book_basic.get_book_basic_status()
                    flash(f'删除书籍 {form1.book_id.data} 成功，同本书籍总共数量{info[0]}，当前剩余数量{info[1]}，当前借出数量{info[2]}，当前丢失数量{info[3]}')
                else:
                    flash('该书籍编号不存在，请核实')
            else:
                flash('删除书籍必须填写丢失书籍id')

    return render_template('manage-book.html',form1=form1)



@auth.route('/delete_one_book<book_id>', methods=['POST'])
@online_required
@only_admin
def delete_one_book(book_id):
    message_info = ''
    lost_book = Book.query.filter_by(book_id=book_id).first()
    if lost_book:
        # 该书未被借，直接删除；该书正被借着，先还书，再删除
        # 将book_basic的basic—num-1，但record-num保持不变
        lost_user_id = None
        if lost_book.book_borrowed:
            lost_user_id = lost_book.borrow_log.borrow_user_id
            lost_book.return_this_book()
        lost_book_return_log = Return_log.query.filter_by(return_book_id=book_id).all()
        if lost_book_return_log:
            for log in lost_book_return_log:
                db.session.delete(log)
            db.session.commit()
        lost_book_isbn = lost_book.book_isbn
        lost_book_basic = Book_basic.query.filter_by(book_basic_isbn=lost_book_isbn).first()
        lost_book_basic.book_basic_num -= 1
        db.session.commit()
        db.session.delete(lost_book)
        db.session.commit()
        new_lost_log = Lost_log(book_id, lost_book_isbn, lost_user_id)
        db.session.add(new_lost_log)
        db.session.commit()
        lost_book_basic = Book_basic.query.filter_by(book_basic_isbn=lost_book_isbn).first()
        info = lost_book_basic.get_book_basic_status()
        message_info = f'删除书籍 {book_id} 成功，同本书籍总共数量{info[0]}，当前剩余数量{info[1]}，当前借出数量{info[2]}，当前丢失数量{info[3]}'
    else:
        message_info = '该书籍编号不存在，请核实'

    return jsonify(message_info=message_info)



@auth.route('/return_this_book', methods=['POST'])
@online_required
@only_admin
def return_this_book():
    if request.form['borrowed_book_id']:
        borrowed_book_id = request.form['borrowed_book_id']
        borrowed_book = Book.query.filter_by(book_id=borrowed_book_id).first()
        borrowed_book.return_this_book()
        message_info = f'书籍id为 {borrowed_book_id} 已经于 {datetime.datetime.now()} 成功还书！'
        return jsonify(
            message_info = message_info,
        )






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
                    info_label_1 = ['借阅人姓名', '借阅人学号', '借阅书籍名称', '借阅书籍id', '借阅书籍时间']
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
                    info_label_2 = ['借阅人姓名', '借阅人学号', '借阅书籍名称', '借阅书籍id', '借阅书籍时间']
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
                           info_label_1=info_label_1, info_label_2=info_label_2
                           )


