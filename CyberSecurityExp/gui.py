import PySimpleGUI as sg
from queue import Queue


class ClinetGUI():
    def __init__(self):
        sg.theme('DarkAmber')
        self.font = ('Helvetica', 18)
        self.username = None
        self.window = None
        self.text_value = {'text': Queue(), 'button': Queue()}
        self.output = print

    def create_login_layout(self, font):
        layout = [
            [sg.Text('Enter your Nickname below', font=font)],
            [sg.Text('Nickname', font=font), sg.InputText(font=font, text_color='white', size=(20, 1))],
            [sg.Button('Ok', font=font), sg.Button('Cancel', font=font)],

        ]
        return layout

    def create_chat_layout(self, font):
        layout = [
            [sg.Text(f'Hello, {self.username}', font=font, text_color='white')],
            [sg.Output(size=(40, 20), font=font, text_color='white', key='OUTPUT')],
            [sg.Input(font=font, size=(34, 1), do_not_clear=False), sg.FileBrowse(font=font)],
            [sg.OK(font=font), sg.Cancel(font=font)],
        ]
        return layout

    def run_login(self):
        window1 = sg.Window("Login", self.create_login_layout(self.font))
        while True:
            event, values = window1.read()
            if event == sg.WIN_CLOSED or event == 'Cancel':
                break
            if event == 'Ok' and len(values[0]) > 0:
                if values[0] in ('alice', 'bob'): break
                else: sg.popup_error("choose alice or bob!", font=self.font)
        window1.close()
        self.username = values[0]
        return self.username

    def run_chat(self):
        window2 = sg.Window("Chat", self.create_chat_layout(self.font))
        self.window = window2
        while True:
            event, values = window2.read()
            if event == sg.WIN_CLOSED or event == 'Cancel':
                break
            elif len(values[0]) > 0:
                self.text_value['text'].put(values[0])
        window2.close()


if __name__ == "__main__":
    clientgui = ClinetGUI()
    clientgui.run_login()
    clientgui.run_chat()
    # sg.theme_previewer()



