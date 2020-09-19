from flask_sqlalchemy import SQLAlchemy
from flask import Flask, session
from flask_bootstrap import Bootstrap
from flask_login import LoginManager, logout_user
import sys


app = Flask(__name__, template_folder="../templates")
db = SQLAlchemy()
bootstrap = Bootstrap()
login_manager = LoginManager()
UPLOAD_FOLDER = r'app/static/book-cover/new-covers/'
COVER_URL_PATH = r'book-cover/new-covers/'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg'}



def logout_all():
    for user in session.keys():
        session.pop(user)


def create_app():
    app.app_context().push()
    password = ''
    app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+mysqldb://root:' + password + '@127.0.0.1/library?charset=utf8mb4'
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    app.config['WTF_CSRF_ENABLED'] = False
    app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
    app.config['COVER_URL_PATH'] = COVER_URL_PATH
    import random, time
    secret_key = random._urandom(24) + bytes(str(time.clock()), encoding='utf-8')
    app.config['SECRET_KEY'] = secret_key

    db.init_app(app)
    from app.model import Role, User, Book_basic
    # db.drop_all()

    db.create_all()


    Role.insert_roles()
    User.insert_admin()
    User.insert_default_user()
    User.insert_teacher()

    Book_basic.insert_origin_books()

    bootstrap.init_app(app)
    login_manager.init_app(app)



    from app.main import main as main_blueprint
    from app.auth import auth as auth_blueprint
    app.register_blueprint(main_blueprint)
    app.register_blueprint(auth_blueprint)


    return app