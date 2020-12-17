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
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }
        static int StartHeck_flag = 0;
        static int password_flag = 0;
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

        /// <summary>
        /// 开启服务,连接服务端
        /// </summary>
        public void StartClient()
        {
            try
            {

                _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress address = IPAddress.Parse(_ip);
                IPEndPoint endPoint = new IPEndPoint(address, _port);
                _socket.BeginConnect(endPoint, CallBackMethod, _socket);
                if (TimeoutObject.WaitOne(1000, false))
                {
                    if (StartHeck_flag == 0)
                    {
                        MessageBox.Show("网络正常，端口开放！");
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

        //FtpReturn_Str返回值
        static String FtpReturn_Str = null;
        
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

        //开始IP搜寻
        private void Start_IpSearch()
        {
            StartHeck_flag = 1;//防止跳窗
            string IpSearch_Begin = "192.168.0.";
            string IpSearch_End = "192.168.0.";
            string IpSearch_Reflash = "192.168.0.";//用于刷新动态IP
            string Box6_IP = textBox6.Text;//获取box6的输入IP
            string Box7_IP = textBox7.Text;//获取box7的输入IP
            int Box_Flag = int.Parse(Box6_IP); ;//动态boxIP
            IpSearch_Begin += textBox6.Text;//起始IP
            IpSearch_End += textBox7.Text;//截止IP
            string IpSearch_Flag = IpSearch_Begin;//动态IP
            while (IpSearch_Flag != IpSearch_End)
            {
                Form4 client = new Form4();
                client.SocketClient(IpSearch_Flag, int.Parse(textBox4.Text));
                client.StartClient();
                Search_Info(IpSearch_Flag);
                client.Close();
                Box_Flag++;
                IpSearch_Flag = IpSearch_Reflash + Convert.ToInt32(Box_Flag);
            }
            StartHeck_flag = 0;
        }

        //搜寻IP返回信息
        static int Time_Out = 0;
        private void Search_Info(string Info_Search)
        {
            if (Time_Out == 0)
            {
                listBox2.Items.Add("IP地址：" + Info_Search + "，21端口开放\r\n");
                listBox2.SelectedIndex = listBox2.Items.Count - 1;//滚动条添加。
                WriteSeachInfo(Info_Search);
                WriteSeachInfo(textBox2.Text);
            }
            else
            {
                listBox2.Items.Add("IP地址：" + Info_Search + "，21端口未开放\r\n");
                listBox2.SelectedIndex = listBox2.Items.Count - 1;//滚动条添加。
            }
            Time_Out = 0;
        }

        //写入地址段信息
        private void WriteSeachInfo(string txt)
        {
            /*if (!System.IO.File.Exists(@"‪‪C:\FTP\ftp1.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\ftp1.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                //System.IO.File.SetAttributes(@"‪C:\FTP\ftp1.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                sw.WriteLine(txt);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {*/
                FileStream fs = new FileStream(@"C:\FTP\ftp1.txt", FileMode.Append, FileAccess.Write);
                //System.IO.File.SetAttributes(@"C:\FTP\ftp1.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                sr.WriteLine(txt);//开始写入值
                sr.Close();
                fs.Close();

            //}

        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            Start_IpSearch();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }
        private void button1_Click(object sender, EventArgs e)
        {
            Form4 client = new Form4();
            client.SocketClient(textBox3.Text, int.Parse(textBox4.Text));
            client.StartClient();
            client.Close();
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {

        }
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
        private void button2_Click(object sender, EventArgs e)
        {
            Form4 client = new Form4();
            client.SocketClient(textBox3.Text, int.Parse(textBox4.Text));
            StartLogIn();
        }

        private void Form4_Load(object sender, EventArgs e)
        {

        }
    }
}
