from app import create_app

app = create_app()





if __name__ == '__main__':
    localhost = '127.0.0.1'
    app.run(host=localhost, port=5000)