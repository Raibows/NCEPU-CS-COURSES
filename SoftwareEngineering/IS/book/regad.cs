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

    public partial class regad : Form
    {
        public string str0 = null;
        public int p;
        string id1;
        string id2;

        public regad()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "" || textBox1.Text.Length > 10)
            { MessageBox.Show("请输入小于11位的工号！"); }

            else if (textBox3.Text == "" || textBox3.Text.Length > 10)
            { MessageBox.Show("请输入小于11位的密码！"); }
            else
            {
                string Adnumstr = textBox1.Text.Trim();
                string Admimastr = textBox3.Text.Trim();
                string strInsert = "Insert Into Administrators(Aid,Apwd) Values('"
                                + Adnumstr + "','" + Admimastr + "')";
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    con.Open();
                    SqlCommand com = new SqlCommand("select Aid from Administrators where Aid='" + Adnumstr + "'", con);
                    SqlDataReader sdr = com.ExecuteReader();
                    if (sdr.HasRows)
                    { MessageBox.Show("管理员已存在！"); }
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

        private void regad_Load(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(str0))
            { }
            else
            {
                string strQuery1 = "Select Aid as 工号 From Administrators Where Aid='" + str0 + "' ";
                string strQuery2 = "Select Apwd as 密码 From Administrators Where Aid='" + str0 + "' ";
                Sql1 sqlHelper = new Sql1();
                SqlConnection con = sqlHelper.GetConnection();
                SqlCommand cmd1 = new SqlCommand(strQuery1, con);
                SqlCommand cmd2 = new SqlCommand(strQuery2, con);
                con.Open();
                id1 = (string)cmd1.ExecuteScalar();
                id2 = (string)cmd2.ExecuteScalar();

                textBox1.Text = str0;

                textBox3.Text = id2;
            }
        }


        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }
    }
}
