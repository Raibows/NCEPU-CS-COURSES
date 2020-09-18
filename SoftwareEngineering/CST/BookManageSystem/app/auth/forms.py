from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, BooleanField,SubmitField,TextAreaField,FormField,SelectField
from wtforms.validators import DataRequired, EqualTo, length, regexp, optional, ValidationError
import re


isbn_regex = '^[0-9]{13}$'
book_id_regex = '^[0-9]{16}$'
user_id_regex = '^[0-9]{6}'

def book_insert_num(form, field):
    message = '单次添加数量必须为正整数，且小于1000'
    if field.data:
        try:
            data = int(field.data)
        except:
            raise ValidationError(message)
        else:
            if data < 0 or data > 999:
                raise ValidationError(message)

def return_book_id(form, field):
    message = '书籍id必须为16位数字'
    if field.data:
        x = re.findall(book_id_regex, field.data)
        if not x or x[0] != field.data:
            raise ValidationError(message)

def return_book_user_id(form, field):
    message = '用户用户id必须为6位整数'
    if field.data:
        x = re.findall(user_id_regex, field.data)
        if not x or x[0] != field.data:
            raise ValidationError(message)

def isbn_check(form, field):
    message='图书ISBN必须为13位数字'
    if field.data:
        x = re.findall(isbn_regex, field.data)
        if not x or x[0] != field.data:
            raise ValidationError(message)



class Insert_book_form(FlaskForm):
    category = SelectField(
        '操作类型',
        choices=[
            ('delete', '删除书籍'),
            ('insert', '增加书籍')
        ],
        validators=[DataRequired()]
    )
    isbn = StringField(
        '图书ISBN',
        validators=[
            isbn_check
        ]
    )
    book_id = StringField(
        '书籍id',
        validators=[
            return_book_id
        ]
    )
    name = StringField(
        '图书名称',
        validators=[
            length(0, 100)
        ]
    )
    author = StringField(
        '图书作者',
        validators=[
            length(0, 20)
        ]
    )
    update_num = StringField(
        '新增图书数量',
        validators=[
            book_insert_num
        ]
    )
    submit = SubmitField('提交修改')



class Return_book_form(FlaskForm):
    book_id = StringField(
        '还书id',
        render_kw={'placeholder': '16位图书id'},
        validators=[
            return_book_id
        ]
    )
    user_id = StringField(
        '用户用户id',
        render_kw={'placeholder': '6位用户用户id'},
        validators=[
            return_book_user_id
        ]
    )
    submit = SubmitField('提交查询')


class Lend_book_form(FlaskForm):
    lend_book_id = StringField(
        '借阅书籍id',
        validators=[
            DataRequired(),
            return_book_id
        ]
    )
    lend_user_id = StringField(
        '借阅书籍人用户id',
        validators=[
            DataRequired(),
            return_book_user_id
        ]
    )
    submit = SubmitField('办理借阅')

