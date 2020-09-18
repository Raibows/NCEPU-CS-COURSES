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
namespace WindowsFormsApp4
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }
        private string _ip = string.Empty;
        private int _port = 0;
        private Socket _socket = null;
        private byte[] buffer = new byte[1024 * 1024 * 2];
        static int StartHeck_flag = 0;
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="ip">连接服务器的IP</param>
        /// <param name="port">连接服务器的端口</param>
/*      public void SocketClient(string ip, int port)
         {
            this._ip = ip;
            this._port = port;
         }
*/
        public void SocketClient(string socket_ip, int socket_port)
        {
            this._ip = socket_ip;
            this._port = socket_port;
        }

        /// <summary>
        /// 开启服务,连接服务端
        /// </summary>
        static String FtpReturn_Str = null;
        static int Time_Out = 0;
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
                /*if (TimeoutObject.WaitOne(1000, false))//1s超时
                {
                    MessageBox.Show("网络正常");
                }
                else
                {
                    MessageBox.Show("连接超时");
                }
                //接收返回值
                byte[] buffer = new byte[1024 * 1024 * 3];
                //实际接收到的有效字节数
                int FtpReturn_len = _socket.Receive(buffer);//获取buffer（int）
                FtpReturn_Str = Encoding.UTF8.GetString(buffer, 0, FtpReturn_len);//FTPsocket返回值,UTF8编码buffer转为string格式
          */
                if (TimeoutObject.WaitOne(1000, false))//1s超时//StartHeck_flag为0时，破解按钮没被开启，能弹窗“网络正常”
                {
                    if (StartHeck_flag == 0)
                    {
                        MessageBox.Show("网络正常，端口开放！");
                        WriteSeachInfo(textBox1.Text);
                        WriteSeachInfo(textBox4.Text);
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
            }
            catch (Exception ex)
            {
                // _socket.Shutdown(SocketShutdown.Both);
                _socket.Close();
                MessageBox.Show(ex.Message);//远程主机强迫关闭了一个连接/无法连接/连接失败/通讯失败
            }
            //            Thread.Sleep(2000);
            //            MessageBox.Show("发送消息结束");
        }

        private readonly ManualResetEvent TimeoutObject = new ManualResetEvent(false);
        /// <summary> 
        /// Socket连接请求       
        /// </summary>     
        ///<param name="remoteEndPoint">网络端点</param>      
        ///<param name="timeoutMSec">超时时间</param> 

        //--异步回调方法       
        private void CallBackMethod(IAsyncResult asyncresult)
        {
            //使阻塞的线程继续        
            TimeoutObject.Set();
        }

        

        //rdp自动登陆delay函数
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

        //rdp建立连接用通用函数
        private void StartConnection(string IpName, String UserName, String PassWord)
        {
            rdp.Server = IpName;  //rdp为窗体名字,rdp.Server设置IP
            rdp.UserName = UserName; //用户名
            IMsTscNonScriptable secured = (IMsTscNonScriptable)rdp.GetOcx();
            secured.ClearTextPassword = PassWord;//密码
            rdp.Connect();
        }

        //rdp密码登陆检测事件，成功则执行
        static int password_flag = 1;//为1则执行循环
        private void password_det(object s, System.EventArgs e)
        {
            password_flag = 0;//为0表示登陆成功
            //MessageBox.Show("连接成功。");
        }


        //远程连接按钮（需要手动输入IP、用户名、密码，没有Disconnect只能尝试一次）
        private void rdp_button_Click(object sender, EventArgs e)
        {
            StartConnection(textBox1.Text, textBox2.Text, textBox3.Text);
        }


        //写入地址段信息
        private void WriteSeachInfo(string txt)
        {

            FileStream fs = new FileStream(@"C:\FTP\MS1.txt", FileMode.Append, FileAccess.Write);
            //System.IO.File.SetAttributes(@"C:\FTP\MS1.txt", FileAttributes.Hidden);
            StreamWriter sr = new StreamWriter(fs);
            sr.WriteLine(txt);//开始写入值
            sr.Close();
            fs.Close();


        }
        private void Start_IpSearch()
        {
            StartHeck_flag = 1;//防止跳窗

            string IpSearch_Begin = "192.168.157.";
            string IpSearch_End = "192.168.157.";
            string IpSearch_Reflash = "192.168.157.";//用于刷新动态IP

            string Box6_IP = textBox6.Text;//获取box6的输入IP
            string Box7_IP = textBox7.Text;//获取box7的输入IP
            int Box_Flag = int.Parse(Box6_IP); ;//动态boxIP


            IpSearch_Begin += textBox6.Text;//起始IP
            IpSearch_End += textBox7.Text;//截止IP
            string IpSearch_Flag = IpSearch_Begin;//动态IP

            while (IpSearch_Flag != IpSearch_End)
            {
                Form2 client = new Form2();
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
        private void Search_Info(string Info_Search)
        {
            if (Time_Out == 0)
            {
                listBox2.Items.Add("IP地址：" + Info_Search + "，3389端口开放\r\n");
                listBox2.SelectedIndex = listBox2.Items.Count - 1;//滚动条添加。
                WriteSeachInfo(Info_Search);
                WriteSeachInfo(textBox4.Text);
            }
            else
            {
                listBox2.Items.Add("IP地址：" + Info_Search + "，3389端口未开放\r\n");
                listBox2.SelectedIndex = listBox2.Items.Count - 1;//滚动条添加。
            }
            Time_Out = 0;
        }
        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form2 client = new Form2();
            client.SocketClient(textBox1.Text, int.Parse(textBox4.Text));
            client.StartClient();
            client.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Start_IpSearch();
        }
    }
}
