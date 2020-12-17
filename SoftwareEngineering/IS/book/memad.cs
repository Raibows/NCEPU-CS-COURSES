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

    public partial class memad : Form
    {
        public string str0 = null;
        public int p;
        string id1;
        string id2;

        public memad()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox3.Text == "" || textBox3.Text.Length > 10)
            { MessageBox.Show("请输入小于11位的密码！"); }
            else
            {
                string Adnumstr = str0;
                string Admimastr = textBox3.Text.Trim();
                string strUpdata = "Update Administrators Set Aid='" + Adnumstr 
                           + "',Apwd='" + Admimastr + "' Where Aid='" + Adnumstr + "'";
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    con.Open();
                    SqlCommand com = new SqlCommand("select Aid from Administrators where Aid='" + Adnumstr + "'", con);
                    SqlDataReader sdr = com.ExecuteReader();
                    if (sdr.HasRows)
                    {
                        sqlHelper.OperateTb(strUpdata);
                        MessageBox.Show("修改成功！");
                        this.Close();
                        con.Close();
                    }
                    else
                    {
                        MessageBox.Show("修改失败！不存在该用户");
               
                        textBox3.Text = null;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void memad_Load(object sender, EventArgs e)
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
                
                textBox3.Text = id2;
            }
        }


        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
