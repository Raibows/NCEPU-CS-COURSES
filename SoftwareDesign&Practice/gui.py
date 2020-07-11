import tkinter as tk
from tkinter import filedialog, messagebox
from tkinter.simpledialog import askstring
from tkinter import ttk
from queue import Queue, PriorityQueue
from client import TCPClient
from tools import *
import time
import threading
import copy
import os
import pickle



class MainPanel():
    def __init__(self):
        self.root = tk.Tk() # create window
        # self.root.attributes("-toolwindow", 1)
        # self.root.wm_attributes("-topmost", 1)
        self.root.title("Hi Chat")
        self.root.geometry("900x700+300+100")
        self.root.resizable(0, 0)
        self.username = None
        self.chat_with = ''
        self.chat_with_windows = {}
        self.output = None
        self.client = TCPClient()
        self.receive_queue = PriorityQueue()
        self.imgs = []
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)




        # header提示语
        self.frame_header = tk.Frame(self.root, bg='white')
        self.frame_header.place(x=0, y=0, width=900, height=30)
        self.hello_label = tk.Label(self.frame_header, text='', font=('仿宋', 20))
        self.hello_label.place(x=700, y=0)
        self.chat_with_label = tk.Label(self.frame_header, text=f'{self.chat_with}', font=('仿宋', 20), bg='#66FFFF')
        self.chat_with_label.place(x=240, y=0, width=150)


        # 好友栏
        self.canvas_right_bar = tk.Canvas(self.root, scrollregion=(0, 0, 250, 2000))
        self.canvas_right_bar.place(x=650, y=30, width=250, height=620)
        self.right_scroll_bar = tk.Scrollbar(self.canvas_right_bar, orient='vertical', command=self.canvas_right_bar.yview)
        self.right_scroll_bar.pack(side='left', fill=tk.Y)
        self.canvas_right_bar.config(yscrollcommand=self.right_scroll_bar.set)
        self.frame_right_bar = tk.Frame(self.canvas_right_bar, bg='#C0C0C0')
        self.frame_right_bar.place(x=0, y=0)
        self.canvas_right_bar.create_window(20, 0, anchor='nw', window=self.frame_right_bar)

        self.groups = {}
        self.friend_users = set()
        self.unread_message_num = {}





        # 好友栏下部按钮
        self.frame_right_bottem = tk.Frame(self.root)
        self.frame_right_bottem.place(x=650, y=650, width=250, height=50)
        self.btn_add_user = tk.Button(self.frame_right_bottem, text='添加用户', font=('仿宋', 18), bg='#00CCCC',
                                      command=self.btn_add_user_event)
        self.btn_add_user.place(x=10, y=0)
        self.btn_add_group = tk.Button(self.frame_right_bottem, text='管理群组', font=('仿宋', 18), bg='#FF6699',
                                       command=self.btn_add_group_event)
        self.btn_add_group.place(x=120, y=0)


        # 聊天框
        self.frame_chat = tk.Frame(self.root, bg='white')
        self.frame_chat.place(x=0, y=30, width=650, height=520)
        # self.output = tk.Text(self.frame_chat, state=tk.NORMAL, font=('仿宋', 20))
        # self.output.place(x=0, y=0, width=650, height=520)
        # self.output.tag_config('sending', background="#0B5FA5", foreground="white")
        # self.output.tag_config('receiving', background='gray', foreground='white')
        self.output_scroll_bar = tk.Scrollbar(self.frame_chat, orient='vertical')
        self.output_scroll_bar.pack(side='right', fill=tk.Y)
        # self.output.config(yscrollcommand=self.output_scroll_bar.set, state=tk.DISABLED)


        # 输入框
        self.frame_user_input = tk.Frame(self.root)
        self.frame_user_input.place(x=0, y=520, width=650, height=180)
        self.user_input = tk.Text(self.frame_user_input, font=('仿宋', 18))
        self.user_input.place(x=0, y=0, width=630, height=130)

        self.btn_user_input_ok = tk.Button(self.frame_user_input, text='发送', font=('仿宋', 18), bg='#99FF99',
                                           command=lambda :self.btn_get_text_data_event(self.user_input))
        self.btn_user_input_ok.place(x=560, y=130)

        self.btn_user_input_browse = tk.Button(self.frame_user_input, text='文件', font=('仿宋', 18), bg='#66FFFF',
                                               command=self.ask_open_file)
        self.btn_user_input_browse.place(x=470, y=130)

        self.btn_clear_output = tk.Button(self.frame_user_input, text='清屏', font=('仿宋', 18), bg='#FF6633',
                                               command=self.btn_clear_output_event)
        self.btn_clear_output.place(x=380, y=130)

    def read_groups_data(self):
        if file_exist(self.username+'/log.dat'):
            with open(self.username + '/log.dat', 'rb') as file:
                self.groups = pickle.load(file)
        else: self.create_new_group('default')

    def shift_chat_with_window(self, username=None):
        if not username:
            username = self.username
            self.chat_with = ''
        else:
            self.chat_with = username
        self.output = self.chat_with_windows[username]
        self.output.config(state=tk.DISABLED, yscrollcommand=self.output_scroll_bar.set)
        self.output_scroll_bar.config(command=self.output.yview)
        self.output.yview(tk.END)
        self.output.tkraise()
        self.chat_with_label.config(text=self.chat_with)

    def click_user_to_chat_event(self, event):
        widget = event.widget
        try:
            index = int(widget.curselection()[0])
        except:
            return None
        temp = widget.get(index).split('  未读')
        if temp[1] != '0':
            widget.delete(index)
            widget.insert(index, f"{temp[0]}  未读0")
            widget.select_set(index)
        temp = temp[0]
        self.unread_message_num[temp] = 0
        if self.chat_with != temp:
            self.shift_chat_with_window(temp)

    def btn_group_show_friends(self, group):
        group = self.groups[group]
        if group[2] == 0:
            if (len(group[0])) == 0: return None
            temp = tk.Listbox(group[1], font=('仿宋', 18))
            temp.bind('<<ListboxSelect>>', self.click_user_to_chat_event)
            for user in group[0]: temp.insert('end', f"{user}  未读{self.unread_message_num[user]}")
            temp.pack()
            group[2] = temp
        else:
            group[2].destroy()
            group[2] = 0
            self.update_groups()
            self.shift_chat_with_window(None)

    def btn_add_user_event(self):
        user_window = AddUserPanel(self.root, self.groups, self.client, self.update_groups)
        self.update_groups()

    def btn_add_group_event(self):
        for g, val in self.groups.items():
            if val[2] != 0: self.btn_group_show_friends(g)
        group_window = GroupManagePanel(self, self.groups)
        group_window.run()
        self.update_groups()

    def btn_clear_output_event(self):
        if isinstance(self.output, tk.Text):
            self.output.config(state=tk.NORMAL)
            self.output.delete('1.0', tk.END)
            self.output.config(state=tk.DISABLED)

    def ask_open_file(self):
        if self.chat_with == '':
            messagebox.showerror(message='请先指定联系人，再发送消息', parent=self.root)
            return None
        file = filedialog.askopenfile(mode='rb', )
        if file == None: return None
        file = file.read()
        temp = MessageNode('pic', time.time(), file, self.username, self.chat_with)
        self.output_one_message(temp, sending=True)
        self.client.send_queue.put(temp)

    def btn_get_text_data_event(self, text: tk.Text):
        if self.chat_with == '':
            messagebox.showerror(message='请先指定联系人，再发送消息', parent=self.root)
            return None
        text_content = text.get('1.0', tk.END).strip('\n').strip(' ')
        text.delete('1.0', tk.END)
        if len(text_content) == 0: return None
        temp = MessageNode('text', time.time(), text_content, self.username, self.chat_with)
        self.output_one_message(temp, sending=True)
        self.client.send_queue.put(temp)

    def create_chat_with_text_window(self, usr):
        if usr not in self.chat_with_windows:
            self.chat_with_windows[usr] = tk.Text(self.frame_chat, state=tk.DISABLED, font=('仿宋', 20), yscrollcommand=self.output_scroll_bar.set)
            self.chat_with_windows[usr].place(x=0, y=0, width=630, height=520)
            self.chat_with_windows[usr].tag_config('sending', background="#0B5FA5", foreground="white")
            self.chat_with_windows[usr].tag_config('receiving', background='gray', foreground='white')
        if isinstance(self.output, tk.Text): self.output.tkraise()

    def create_new_group(self, group_name: str):
        frm = tk.Frame(self.frame_right_bar)
        btn = tk.Button(frm, text=f"{group_name}  未读0", width=23, height=2, bg='#FFFF99',
                        command=lambda: self.btn_group_show_friends(group_name))
        btn.pack()
        self.groups[group_name] = [[], frm, 0]

    def get_group_button(self, group_name):
        frm:tk.Frame = self.groups[group_name][1]
        return frm.winfo_children()[0]

    def update_groups(self):
        self.update_friend_users()
        # self.groups['default'][1].pack()
        for key, val in self.groups.items():
            [self.create_chat_with_text_window(x) for x in val[0]]
            if val[1] == None:
                temp = val[0].copy()
                self.create_new_group(key)
                self.groups[key][0] = temp
            self.groups[key][1].pack(fill='both')

    def update_friend_users(self):
        self.friend_users.clear()
        for key, val in self.groups.items():
            [self.friend_users.add(x) for x in val[0]]
        for x in self.friend_users:
            if x not in self.unread_message_num:
                self.unread_message_num[x] = 0

    def update_unread_message(self):
        for key, val in self.groups.items():
            unread_sum = 0
            for x in val[0]: unread_sum += self.unread_message_num[x]
            self.get_group_button(key).config(text=f"{key}  未读{unread_sum}")
            if val[2] == 0: continue
            else:
                try:
                    index = int(val[2].curselection()[0])
                except:
                    index = None
                val[2].delete(0, 'end')
                for usr in val[0]:
                    val[2].insert('end', f"{usr}  未读{self.unread_message_num[usr]}")
                if index:
                    val[2].select_set(index)

    def output_one_message(self, data:MessageNode, sending=False):
        header, msg = data.get_output(sending)
        if sending:
            temp = data.receiver
            out_window = self.chat_with_windows[temp]
            out_window.config(state=tk.NORMAL)
            out_window.insert(tk.END, header, 'sending')
        else:
            temp = data.sender
            if self.chat_with != temp: self.unread_message_num[temp] += 1
            out_window = self.chat_with_windows[temp]
            out_window.config(state=tk.NORMAL)
            out_window.insert(tk.END, header, 'receiving')
        if data.msg_type == 'pic':
            self.imgs.append(tk.PhotoImage(data=msg))
            out_window.image_create(tk.END, image=self.imgs[-1])
            out_window.insert(tk.END, '\n')
        elif data.msg_type == 'text':
            out_window.insert(tk.END, msg)
        out_window.yview(tk.END)
        out_window.config(state=tk.DISABLED)

    def run_output(self):
        while True:
            if self.receive_queue.empty():
                break
            data = self.receive_queue.get()
            if not data: continue
            if data.sender not in self.friend_users:
                self.groups['default'][0].append(data.sender)
                self.update_groups()
            self.output_one_message(data)
        self.update_unread_message()
        self.root.after(300, self.run_output)

    def run(self):
        self.root.withdraw()
        lg_window = LoginPanel(self.client, self.root)
        lg_window.run()
        self.root.deiconify()
        if self.client.username == None:
            self.on_closing()
            return None
        self.username = self.client.username
        self.read_groups_data()
        self.update_groups()
        for usr in self.friend_users: self.unread_message_num[usr] = 0


        self.output = tk.Text(self.frame_chat, state=tk.DISABLED, font=('仿宋', 20))
        self.output.place(x=0, y=0, width=630, height=520)
        self.chat_with_windows[self.username] = self.output
        self.output.tkraise()


        self.hello_label.config(text=f'Hello, {self.username}')
        self.client.run(self.receive_queue)
        self.root.after(300, self.run_output)
        self.root.mainloop()


    def on_closing(self):
        self.client.stop_signal = True
        self.client.quit_from_server()
        for key, val in self.groups.items():
            self.groups[key][1] = None
            self.groups[key][2] = None
        if self.username:
            if not file_exist(self.username): os.mkdir(self.username)
            with open(self.username+'/log.dat', 'wb') as file:
                pickle.dump(self.groups, file)
        self.root.quit()
        try:
            self.root.destroy()
        except:
            pass

class LoginPanel():
    def __init__(self, client, parent):
        self.root = tk.Toplevel(parent)
        self.root.resizable(0, 0)
        self.root.attributes("-toolwindow", 1)
        self.root.wm_attributes("-topmost", 1)
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
        self.root.title('登录')
        self.root.geometry('500x380+400+300')
        self.font = ("仿宋", 16, "bold")
        self.client = client

        # header
        self.header = tk.Canvas(self.root)
        self.image_file = tk.PhotoImage(file='pics/welcome.png')
        self.image_file = self.image_file.subsample(2, 2)
        self.header.place(x=0, y=0, width=380, height=200)
        self.header.create_image(210, 5, anchor='nw', image=self.image_file)


        # input
        self.input = tk.Canvas(self.root, bg='#ffffff')
        self.input.place(x=0, y=130, heigh=250, width=500)

        self.btn_login = tk.Button(self.input, text='登陆', bg='#99FFFF', command=self.btn_login_click_event)
        self.btn_login.place(x=120, y=160, heigh=50, width=100)
        self.btn_register = tk.Button(self.input, text='注册', bg='#FFFF99', command=self.btn_register_click_event)
        self.btn_register.place(x=280, y=160, height=50, width=100)

        self.lab_account = tk.Label(self.input, text='账户', font=self.font)
        self.lab_account.place(x=90, y=30)
        self.ent_account = tk.Entry(self.input, font=self.font)
        self.ent_account.place(x=160, y=30)
        self.lab_password = tk.Label(self.input, text='密码', font=self.font)
        self.lab_password.place(x=90, y=90)
        self.ent_password = tk.Entry(self.input, font=self.font, show='*')
        self.ent_password.place(x=160, y=90)

    def on_closing(self):
        self.root.quit()
        self.root.destroy()

    def check_account_password(self, account, password):
        account_len = len(account)
        password_len = len(password)
        flag = True
        if account_len == 0 or password_len == 0:
            flag = False
            messagebox.showerror(message='账户和密码不能为空', parent=self.root)
        elif account_len > 6:
            flag = False
            messagebox.showerror(message='账户最多为6位', parent=self.root)
        elif password_len > 6:
            flag = False
            messagebox.showerror(message='密码最多为6位', parent=self.root)
        return flag

    def btn_login_click_event(self):
        acc = self.ent_account.get()
        pwd = self.ent_password.get()
        if self.check_account_password(acc, pwd):
            if self.client.login(acc, pwd):
                messagebox.showinfo(message='登录成功！', parent=self.root)
                self.root.quit()
                self.root.destroy()
            else:
                messagebox.showerror(message='账号不存在或密码错误！', parent=self.root)

    def btn_register_click_event(self):
        register_window = RegisterPanel(self.root, self.client)
        register_window.run()

    def run(self):
        self.root.mainloop()


class RegisterPanel():
    def __init__(self, window:tk.Tk, client:TCPClient):
        self.root = tk.Toplevel(window)
        self.root.resizable(0, 0)
        self.root.attributes("-toolwindow", 1)
        self.root.wm_attributes("-topmost", 1)
        self.root.protocol("WM_DELETE_WINDOW", self.btn_cancel_click_event)
        self.root.title('注册')
        self.root.geometry('450x350+400+200')
        self.font = ("仿宋", 16, "bold")
        self.client = client
        tk.Label(self.root, text='注册', font=("仿宋", 22, "bold")).place(x=200, y=20)

        self.input = tk.Canvas(self.root, bg='#ffffff')
        self.input.place(x=0, y=60, height=290, width=450)

        self.btn_login = tk.Button(self.input, text='注册', bg='#99FFFF', command=self.btn_register_click_event)
        self.btn_login.place(x=120, y=220, heigh=50, width=100)
        self.btn_register = tk.Button(self.input, text='取消', bg='#FFFF99', command=self.btn_cancel_click_event)
        self.btn_register.place(x=280, y=220, height=50, width=100)

        self.lab_account = tk.Label(self.input, text='账户', font=self.font)
        self.lab_account.place(x=90, y=30)
        self.ent_account = tk.Entry(self.input, font=self.font)
        self.ent_account.place(x=160, y=30)

        self.lab_password = tk.Label(self.input, text='密码', font=self.font)
        self.lab_password.place(x=90, y=90)
        self.ent_password = tk.Entry(self.input, font=self.font, show='*')
        self.ent_password.place(x=160, y=90)

        self.lab_password_con = tk.Label(self.input, text='确认', font=self.font)
        self.lab_password_con.place(x=90, y=150)
        self.ent_password_con = tk.Entry(self.input, font=self.font, show='*')
        self.ent_password_con.place(x=160, y=150)

    def check(self, acc, pwd, pwd_con):
        acc_len = len(acc)
        pwd_len = len(pwd)
        pwd_con_len = len(pwd_con)
        flag = True
        if acc_len == 0 or pwd_len == 0 or pwd_con_len == 0:
            flag = False
            messagebox.showerror(message='请填写完整', parent=self.root)
        elif acc_len > 6 or pwd_len > 6:
            flag = False
            messagebox.showerror(message='账号或密码不能大于6位', parent=self.root)
        elif pwd != pwd_con:
            flag = False
            messagebox.showerror(message='密码两次输入不一致', parent=self.root)
        return flag

    def btn_register_click_event(self):
        acc, pwd = self.ent_account.get(), self.ent_password.get()
        if self.check(acc, pwd, self.ent_password_con.get()):
            if self.client.register(acc, pwd):
                messagebox.showinfo(message='注册成功', parent=self.root)
                self.root.quit()
                self.root.destroy()
            else:
                messagebox.showerror(message='注册失败，换一个账号试试', parent=self.root)

    def btn_cancel_click_event(self):
        self.root.quit()
        self.root.destroy()

    def run(self):
        self.root.mainloop()


class GroupManagePanel():
    def __init__(self, other: MainPanel, groups: dict):
        self.parent = other
        self.root = tk.Toplevel(other.root)
        self.root.title('用户组管理')
        self.root.geometry('600x500+300+300')
        self.font = ('仿宋', 18)
        self.root.protocol('WM_DELETE_WINDOW', self.quit)
        tk.Label(self.root, text='用户组', font=self.font).place(x=0, y=10, width=100)
        tk.Label(self.root, text='数量', font=self.font).place(x=100, y=10, width=100)
        tk.Label(self.root, text='用户', font=self.font).place(x=200, y=10, width=50)
        self.canvas = tk.Canvas(self.root, bg='white', scrollregion=(0, 0, 3000, 3000))
        self.canvas.place(x=0, y=50, width=600, height=350)
        self.hbar = tk.Scrollbar(self.canvas, orient=tk.HORIZONTAL)
        self.hbar.pack(side=tk.TOP, fill=tk.X)
        self.hbar.config(command=self.canvas.xview)
        self.vbar = tk.Scrollbar(self.canvas, orient=tk.VERTICAL)
        self.vbar.pack(side=tk.LEFT, fill=tk.Y)
        self.vbar.config(command=self.canvas.yview)
        self.canvas.config(xscrollcommand=self.hbar.set, yscrollcommand=self.vbar.set)
        self.canvas_frame = tk.Frame(self.canvas, bg='#00CC66')
        self.canvas_frame.place(x=100, y=100, anchor='nw')

        self.canvas.create_window(30, 15, window=self.canvas_frame, anchor='nw')

        self.frame = tk.Frame(self.root)
        self.frame.place(x=0, y=400, width=600, height=100)
        self.btn_ok = tk.Button(self.frame, bg='#00CC66', text='移动好友', command=self.btn_ok_event)
        self.group_choice = ttk.Combobox(self.frame, values=list(groups.keys()), state='readonly', )
        self.group_choice.current(list(groups.keys()).index('default'))
        self.btn_new = tk.Button(self.frame, bg='#FFFF00', text='新建群组', command=self.btn_new_event)
        self.btn_delete = tk.Button(self.frame, bg='#FF6633', text='删除好友', command=self.btn_delete_event)
        self.btn_edit = tk.Button(self.frame, bg='white', text='修改名称', command=self.btn_edit_group_name)

        self.btn_ok.pack(side='left')
        self.btn_new.pack(side='left')
        self.btn_edit.pack(side='left')
        self.btn_delete.pack(side='left')
        self.group_choice.pack(side='left')
        # self.btn_ok.place(x=10, y=30, width=80)
        # self.group_choice.place(x=100, y=30, width=180)
        # self.btn_new.place(x=320, y=30, width=80)
        # self.btn_edit.place()
        # self.btn_delete.place(x=460, y=30, width=80)

        self.groups = groups
        self.vars = {}
        self.show()

    def create_group_delete_button(self, group_name):
        return tk.Button(self.canvas_frame, bg='#FFFF99', text=f"{group_name}", font=self.font,
                         width=8, command=lambda :self.btn_delete_group_event(group_name))

    def show(self):
        self.group_choice.config(values=list(self.groups.keys()))
        self.group_choice.current(list(self.groups.keys()).index('default'))
        for widget in self.canvas_frame.winfo_children():
            widget.destroy()
        for row, (key, val) in enumerate(self.groups.items()):
            self.create_group_delete_button(key).grid(row=row, column=0)  # .pack(side='left') #.place(x=0, y=50*row)

            tk.Label(self.canvas_frame, text=f"{len(val[0])}", font=self.font, width=8).grid(row=row,
                                                                                             column=1)  # .pack(side='left', anchor='nw') #.place(x=100, y=50*row)
            self.vars[key] = [tk.BooleanVar(self.canvas, value=False) for _ in val[0]]
            for column, user in enumerate(val[0]):
                t = tk.Checkbutton(self.canvas_frame, variable=self.vars[key][column], onvalue=True, offvalue=False,
                                   text=user,
                                   font=self.font)  # .pack(side='left') #.place(x=200+column*100, y=50*row, width=100)
                t.grid(row=row, column=2 + column)
        self.canvas_frame.update()
        temp = [0, 0, 30, 30]
        for i in range(len(temp)):
            temp[i] += self.canvas_frame.bbox('all')[i]
        self.canvas.config(scrollregion=temp)
        self.parent.update_groups()

    def btn_edit_group_name(self):
        g = self.group_choice.get()
        if g == 'default':
            messagebox.showerror(message='默认群组无法修改', parent=self.root)
            return None
        ng = askstring(title='Edit Group', prompt='请输入新用户组名称', parent=self.root)
        if ng == None: return None

        temp = self.groups[g][0].copy()
        self.groups[g][1].destroy()
        if isinstance(self.groups[g][2], tk.Listbox): self.groups[g][2].destroy()
        del self.groups[g]
        self.parent.create_new_group(ng)
        self.groups[ng][0] = temp
        self.show()

    def btn_delete_group_event(self, key):
        if key == 'default':
            messagebox.showerror(message='默认群组无法删除', parent=self.root)
            return None
        if len(self.groups[key][0]) > 0:
            messagebox.showerror(message='请先移动好友，再删除群组', parent=self.root)
            return None
        self.groups[key][1].destroy()
        if isinstance(self.groups[key][2], tk.Listbox): self.groups[key][2].destroy()
        del self.groups[key]
        self.show()

    def btn_delete_event(self):
        for key, val in self.vars.items():
            idx = 0
            for var in val:
                if idx == len(val): break
                if var.get():
                    var.set(False)
                    del self.groups[key][0][idx]
                else:
                    idx += 1
        messagebox.showinfo(message='删除完毕', parent=self.root)
        self.show()

    def btn_ok_event(self):
        g = self.group_choice.get()
        for key, val in self.vars.items():
            idx = 0
            for var in val:
                if idx == len(val): break
                if var.get():
                    var.set(False)
                    if key == g:
                        idx += 1
                        continue
                    temp = self.groups[key][0][idx]
                    del self.groups[key][0][idx]
                    self.groups[g][0].append(temp)
                else:
                    idx += 1

        messagebox.showinfo(message='移动完毕', parent=self.root)
        self.show()

    def btn_new_event(self):
        group = askstring(title='Add Group', prompt='请输入新用户组', parent=self.root)
        if group == None: return None
        if len(group) > 6:
            messagebox.showerror(message='用户组不能超过6个字符！', parent=self.root)
            return None
        if group in self.groups:
            messagebox.showerror(message='用户组重复！', parent=self.root)
            return None
        # self.groups[group] = [[], tk.Button(self.parent.frame_right_bar, text=group, width=20, height=2), 0]
        self.parent.create_new_group(group)
        self.show()

    def quit(self):
        self.root.quit()
        self.root.destroy()

    def run(self):
        self.root.mainloop()


class AddUserPanel():
    def __init__(self, parent: tk.Tk, groups, client:TCPClient, update_groups_func):
        self.update_groups_func = update_groups_func
        self.clinet = client
        self.parent = parent
        self.root = tk.Toplevel(parent)
        self.root.title('添加联系人')
        self.root.geometry('360x160+300+300')
        self.font = ('仿宋', 18)
        self.root.protocol('WM_DELETE_WINDOW', self.quit)
        self.groups = groups
        self.user_accounts = set()
        for key, val in self.groups.items():
            [self.user_accounts.add(x) for x in val[0]]

        self.lb_ent_account = tk.Label(self.root, font=self.font, text='对方账户')
        self.ent_account = tk.Entry(self.root, font=self.font)
        self.lb_ent_account.grid(row=0, column=0)
        self.ent_account.grid(row=0, column=1)

        self.lb_groups = tk.Label(self.root, font=self.font, text='选择群组')
        self.group_choice = ttk.Combobox(self.root, values=list(groups.keys()), state='readonly', )
        self.group_choice.current(list(groups.keys()).index('default'))
        self.lb_groups.grid(row=1, column=0)
        self.group_choice.grid(row=1, column=1)

        self.btn_ok = tk.Button(self.root, text='提交', font=self.font, bg='#00CC66', command=self.btn_ok_event)
        self.btn_cancel = tk.Button(self.root, text='取消', font=self.font, bg='#FF6633', command=self.quit)
        self.btn_ok.place(x=110, y=100)
        self.btn_cancel.place(x=210, y=100)

        self.root.mainloop()


    def btn_ok_event(self):
        u, g = self.ent_account.get(), self.group_choice.get()
        if len(u) == 0 or len(g) == 0:
            messagebox.showerror(message='账号或群组不能为空!', parent=self.root)
        elif len(u) > 6:
            messagebox.showerror(message='账号不能大于6位', parent=self.root)
        elif u in self.user_accounts:
            messagebox.showerror(message='该好友已经添加', parent=self.root)
        elif u == self.clinet.username:
            messagebox.showerror(message='不能添加自己', parent=self.root)
        else:
            if self.clinet.search_user_exist(u):
                self.user_accounts.add(u)
                self.groups[g][0].append(u)
                self.update_groups_func()
                messagebox.showinfo(message='添加成功', parent=self.root)
            else:
                messagebox.showerror(message='该账户不存在', parent=self.root)
        self.ent_account.delete(0, 'end')

    def quit(self):
        self.root.quit()
        self.root.destroy()



if __name__ == '__main__':
    main_window = MainPanel()
    main_window.run()
    pass
