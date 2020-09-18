from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField,BooleanField,SubmitField,TextAreaField,FormField,SelectField
from wtforms.validators import DataRequired,EqualTo,length,regexp,optional

user_id_regex = '^[0-9]{6}$'
user_name_regex = '^[\u4e00-\u9fa5]{2,10}$'
user_password_regex = '^[0-9a-zA-Z]{6,12}$'


class Register_user_form(FlaskForm):
    register_user_id = StringField(
        '用户id',
        render_kw={'placeholder': '由6位0-9整数组成'},
        validators=[
            DataRequired(),
            regexp(regex=user_id_regex, flags=0, message='用户id必须为6位整数')
        ]
    )
    register_user_name = StringField(
        '姓名',
        render_kw={'placeholder': '2-10位中文组成'},
        validators=[
            DataRequired(),
            regexp(regex=user_name_regex, flags=0, message='姓名必须为中文2到10位')
        ]
    )
    register_user_password = PasswordField(
        '密码',
        render_kw={'placeholder': '数字或英文6-12位组成'},
        validators=[
            DataRequired(),
            regexp(regex=user_password_regex, flags=0, message='密码必须为数字或英文6到12位')
        ]
    )
    register_user_password_confirm = PasswordField(
        '确认密码',
        validators=[
            DataRequired(),
            EqualTo('register_user_password', message='两次输入密码必须一致')
        ]
    )
    register_submit = SubmitField('注册')

class Login_form(FlaskForm):
    login_user_id = StringField(
        '用户id',
        validators=[
            DataRequired(),
            regexp(regex=user_id_regex, flags=0, message='用户id必须为6位整数')
        ]
    )
    login_user_password = PasswordField(
        '密码',
        validators=[
            DataRequired(),
            regexp(regex=user_password_regex, flags=0, message='密码必须为数字或英文6到12位')
        ]
    )
    login_submit = SubmitField('登陆')



class Search_form(FlaskForm):
    search = StringField(
        render_kw={'placeholder': '请输入任何书籍名称、作者、书籍ISBN关键词，关键词以空格分隔，不超过30个字符'},
        validators=[
            DataRequired(),
            length(1, 30),
        ]
    )





