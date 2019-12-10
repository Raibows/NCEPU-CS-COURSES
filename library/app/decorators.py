from flask_login import current_user
from flask import flash,redirect,render_template,url_for,request
from functools import wraps



def only_admin(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        if current_user.is_authenticated and current_user.user_role_name == 'admin':
            return func(*args, **kwargs)
        else:
            flash('您的权限不够！请联系管理员！')
            return redirect(url_for('main.index'))
    return wrapper


def online_required(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        if current_user.is_authenticated:
            return func(*args, **kwargs)
        else:
            flash('请先登陆再使用该功能！')
            return redirect(url_for('main.login'))
    return wrapper
