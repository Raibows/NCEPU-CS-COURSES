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
    public partial class reg : Form
    {
        public string str0 = null;
        public int p;
        string id1;
        string id2;

        public reg()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "" || textBox1.Text.Length > 10)
            { MessageBox.Show("请输入小于11位的学号！"); }
            else if (textBox2.Text == "")
            { MessageBox.Show("请输入姓名！"); }
            else if (textBox3.Text == "" || textBox3.Text.Length > 10)
            { MessageBox.Show("请输入小于11位的密码！"); }

            else
            {
                string Unumstr = textBox1.Text.Trim();
                string Unamestr = textBox2.Text.Trim();
                string Upwdstr = textBox3.Text.Trim();

                string strInsert = "Insert Into Students(Sid,Sname,Spwd) Values('"
                                + Unumstr + "','" + Unamestr + "','" + Upwdstr + "')";
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    con.Open();
                    SqlCommand com = new SqlCommand("select Sid from Students where Sid='" + Unumstr + "'", con);
                    SqlDataReader sdr = com.ExecuteReader();
                    if (sdr.HasRows)
                    { MessageBox.Show("用户已存在！"); }
                    else
                    {
                        int intResult = sqlHelper.OperateTb(strInsert);
                        MessageBox.Show("添加成功！");
                    }
                    this.Close();
                    con.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                this.Close();
            }
        }

        private void reg_Load(object sender, EventArgs e)
        {

            if (string.IsNullOrEmpty(str0))
            { }
            else
            {
                string strQuery1 = "Select Sname as 用户姓名 From Students Where Sid='" + str0 + "' ";
                string strQuery2 = "Select Spwd as 密码 From Students Where Sid='" + str0 + "' ";

                Sql1 sqlHelper = new Sql1();
                SqlConnection con = sqlHelper.GetConnection();
                SqlCommand cmd1 = new SqlCommand(strQuery1, con);
                SqlCommand cmd2 = new SqlCommand(strQuery2, con);

                con.Open();
                id1 = (string)cmd1.ExecuteScalar();
                id2 = (string)cmd2.ExecuteScalar();


                textBox1.Text = str0;
                textBox2.Text = id1;
                textBox3.Text = id2;
            }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged_1(object sender, EventArgs e)
        {

        }
    }
}
