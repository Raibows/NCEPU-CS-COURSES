using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace book
{   
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.label4.Text = "系统启动时间：" + DateTime.Now.ToLongDateString() + DateTime.Now.ToShortTimeString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)  // 登录
        {
            string userid = textBox1.Text.Trim();
            string userpw = textBox2.Text.Trim();

            if (radioButton2.Checked == true)
            {
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    SqlCommand com = new SqlCommand("select Aid,Apwd from Administrators where Aid='" + userid + "' and Apwd='" + userpw + "'", con);
                    SqlDataAdapter da = new SqlDataAdapter(com);
                    DataSet ds = new DataSet();
                    int n = da.Fill(ds, "register");


                    if (n != 0)
                    {
                        Admin f = new Admin();
                        f.ShowDialog();
                        textBox1.Text = null;
                        textBox2.Text = null;
                    }
                    else
                    {
                        MessageBox.Show("请输入正确的账号和密码！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox2.Text = null;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    SqlCommand com = new SqlCommand("select Sid,Spwd from Students where Sid='" + userid + "' and Spwd='" + userpw + "'", con);
                    SqlDataAdapter da = new SqlDataAdapter(com);
                    DataSet ds = new DataSet();
                    int n = da.Fill(ds, "register");


                    if (n != 0)
                    {
                        Puser f = new Puser();
                        f.str0= userid;
                        f.ShowDialog();
                        textBox1.Text = null;
                        textBox2.Text = null;
                    }
                    else
                    {
                        MessageBox.Show("请输入正确的账号和密码！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox2.Text = null;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {

            string userid = textBox1.Text.Trim();
            string userpw = textBox2.Text.Trim();

            if (radioButton2.Checked == true)
            {
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    SqlCommand com = new SqlCommand("select Aid,Apwd from Administrators where Aid='" + userid + "' and Apwd='" + userpw + "'", con);
                    SqlDataAdapter da = new SqlDataAdapter(com);
                    DataSet ds = new DataSet();
                    int n = da.Fill(ds, "register");


                    if (n != 0)
                    {
                        memad f = new memad();
                        f.str0 = userid;
                        f.ShowDialog();
                        textBox1.Text = null;
                        textBox2.Text = null;
                    }
                    else
                    {
                        MessageBox.Show("请输入正确的账号和密码！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox2.Text = null;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    SqlCommand com = new SqlCommand("select Sid,Spwd from Students where Sid='" + userid + "' and Spwd='" + userpw + "'", con);
                    SqlDataAdapter da = new SqlDataAdapter(com);
                    DataSet ds = new DataSet();
                    int n = da.Fill(ds, "register");


                    if (n != 0)
                    {
                        mem f = new mem();
                        f.str0 = userid;
                        f.ShowDialog();
                        textBox1.Text = null;
                        textBox2.Text = null;
                    }
                    else
                    {
                        MessageBox.Show("请输入正确的账号和密码！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox2.Text = null;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                } 
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (radioButton2.Checked == true)
            {
                regad f = new regad();
                f.p = 0;
                f.ShowDialog();
            }
            else
            {
                reg f = new reg();
                f.p = 1;
                f.ShowDialog();
            }
        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
