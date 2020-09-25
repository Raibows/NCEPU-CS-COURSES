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
    public partial class Puser : Form
    {
        public string str0;//记录登录该页面的用户账号（编号）

        public Puser()
        {
            InitializeComponent();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void Puser_Load(object sender, EventArgs e)
        {
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;//选中整行
            panel1.Visible = false;
            panel2.Visible = false;
            panel3.Visible = false;
            panel4.Visible = false;
            panel5.Visible = false;


            /* try//捕获类别信息显示在下拉列表里
            {
                Sql1 sqlHelper = new Sql1();
                // string strQuery = "Select Bstate From Ttype";

                DataSet dataSetObj = sqlHelper.GetDataSet(strQuery);

                DataTable dt = dataSetObj.Tables[0];

                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    DataRow dr = dt.Rows[i];
                    comboBox1.Items.Add(dr["Bstate"]);
                }

                if (dt.Rows.Count > 0)
                    comboBox1.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }*/

        }

        private void 书籍查询ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel1.Visible = true;
            panel2.Visible = true;
            panel3.Visible = false;
            panel4.Visible = false;
            panel5.Visible = false;
            Sql1 sqlHelper = new Sql1();
            SqlConnection con = sqlHelper.GetConnection();
            con.Open();
            string strQuery = "select Bid as 书籍编号, Bname as 书名, Bpress as 出版社, Bstate as 状态, Bwriter as 作者, Bdate as 出版时间 from Books";
            try
            {
                DataSet ds = sqlHelper.GetDataSet(strQuery);
                DataTable dt = ds.Tables[0];

                dataGridView1.DataSource = dt;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 借阅书籍ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            panel3.Visible = true;
            panel2.Visible = true;
            panel1.Visible = false;
            panel4.Visible = false;
            panel5.Visible = false;
            textBox4.Text = DateTime.Now.ToShortDateString().ToString();
            Sql1 sqlHelper = new Sql1();
            SqlConnection con = sqlHelper.GetConnection();
            con.Open();
            string strQuery = "select Bid as 书籍编号, Bname as 书名, Bpress as 出版社, Bstate as 状态, Bwriter as 作者, Bdate as 出版时间 from Books";
            try
            {
                DataSet ds = sqlHelper.GetDataSet(strQuery);
                DataTable dt = ds.Tables[0];

                dataGridView1.DataSource = dt;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        
        }

        private void 我的借阅情况ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            panel4.Visible = true;
            panel5.Visible = true;
            panel1.Visible = false;
            panel2.Visible = true;
            panel3.Visible = false;
            textBox6.Text = DateTime.Now.ToShortDateString().ToString();
            Sql1 sqlHelper = new Sql1();
            SqlConnection con = sqlHelper.GetConnection();
            con.Open();
            string strQuery1 = "select Borrow.Bid as 书籍编号, Borrow.Sid as 读者编号, Borrowtime as 借出时间 From Borrow,Reback Where Returntime='未还        ' and Borrow.Bid=Reback.Bid and Borrow.Sid=Reback.Sid and Borrow.Sid='" + str0 + "'";
            string strQuery2 = "select Bid as 书籍编号, Sid as 读者编号, Returntime as 归还时间 from Reback Where Sid='" + str0 + "' and Returntime!='未还        '";
            try
            {
                DataSet ds1 = sqlHelper.GetDataSet(strQuery1);
                DataTable dt1 = ds1.Tables[0];
                dataGridView2.DataSource = dt1;

                DataSet ds2 = sqlHelper.GetDataSet(strQuery2);
                DataTable dt2 = ds2.Tables[0];
                dataGridView3.DataSource = dt2;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //查询书籍
            //string strnum = comboBox1.Items[comboBox1.SelectedIndex].ToString();
            string str = textBox1.Text.Trim();
            string strQuery = "Select Bid as 书籍编号, Bname as 书名, Bpress as 出版社, Bstate as 状态, Bwriter as 作者, Bdate as 出版时间 From Books ";
            /*if (strnum.Length > 0)
            {
                strQuery += " And Btapy='" + strnum + "'";
            }
            */
            if (str.Length > 0)
            {
                strQuery += " where Bname LIKE'%" + str + "%'";
            }

            try
            {
                Sql1 sqlHelper = new Sql1();
                DataSet ds = sqlHelper.GetDataSet(strQuery);
                DataTable dt = ds.Tables[0];

                dataGridView1.DataSource = dt;

                if (dt.Rows.Count == 0)
                { 
                    MessageBox.Show("没有符合条件的记录", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {

                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox2.Text == "" || textBox2.Text.Length > 10)
            {
                MessageBox.Show("请输入正确的书籍编号！");
            }
            else
            {

                //借阅书籍
                string str1 = textBox2.Text.Trim(); // 编号
                string str2 = textBox4.Text.Trim(); // 时间

                //检查是否可借
                string strQuery = "Select Bstate From Books Where Bid='" + str1 + "' ";
                //检查该用户是否已借过该书
                string strQuery0 = "Select Sid From Borrow Where Bid='" + str1 + "' AND Sid='" + str0 + "'";
                //更新状态
                string strUpdata = "Update Books Set Bstate='借出' Where Bid='" + str1 + "'AND Bid='" + str1 + "'";
                //增加借阅记录
                string strInsert2 = "Insert Into Borrow(Bid,Sid,Borrowtime) Values('"
                                + str1 + "','" + str0 + "','" + str2 + "')";
                //增加归还记录
                string strInsert3 = "Insert Into Reback(Bid,Sid,Returntime) Values('"
                               + str1 + "','" + str0 + "','未还')";
                string strDelete = "Delete From Reback Where Sid='" + str0 + "' AND Bid='" + str1 + "'";
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    SqlCommand cmd = new SqlCommand(strQuery, con);
                    SqlCommand cmd2 = new SqlCommand(strQuery0, con);
                    con.Open();
                    string id1 = (string)cmd.ExecuteScalar();
                    id1 = id1.Trim();
                    string id2 = (string)cmd2.ExecuteScalar();

                    if ((id1 == "可借") && (string.IsNullOrEmpty(id2)))
                    {
                        sqlHelper.OperateTb(strUpdata);
                        sqlHelper.OperateTb(strInsert2);
                        sqlHelper.OperateTb(strDelete);
                        sqlHelper.OperateTb(strInsert3);
                        MessageBox.Show("借阅成功");
                        借阅书籍ToolStripMenuItem_Click(null, null);//刷新页面
                        textBox2.Text = null;
                        textBox1.Text = null;
                    }
                    else if (id1 == "借出") // &&(string.IsNullOrEmpty(id2))
                    {
                        MessageBox.Show("书已借出，借书失败", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else // if (!string.IsNullOrEmpty(id2))
                    {
                        MessageBox.Show("已借阅过该书（不允许重复借阅）", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("该书籍编号不存在！");
                }
            }
        }
        /*
        private void button4_Click(object sender, EventArgs e)
        {
            //textBox3.Text = dataGridView2.SelectedRows[0].Cells["书籍编号"].Value.ToString();
            string str1 = textBox3.Text.Trim();
            string str2 = textBox5.Text.Trim();

            DateTime dtDate;

            if (DateTime.TryParse(str2, out dtDate))
            {
                string strQuery1 = "Select Bnum  From Borrow Where Bnum='" + str1 + "'AND Btime='" + str2 + "' AND Unum='" + str0 + "'";
                string strUpdata = "Update Borrow Set cost=0 Where Bnum='" + str1 + "'AND Btime='" + str2 + "' AND Unum='" + str0 + "'";
                
                Sql1 sqlHelper = new Sql1();
                SqlConnection con = sqlHelper.GetConnection();
                SqlCommand cmd1 = new SqlCommand(strQuery1, con);
                con.Open();
                string id1 = (string)cmd1.ExecuteScalar();
                if (string.IsNullOrEmpty(id1))
                {
                    MessageBox.Show("未查到该记录！请检查输入是否正确");
                    return;
                }
                
                try
                {
                    sqlHelper.OperateTb(strUpdata);
                    MessageBox.Show("缴纳成功");
                    我的借阅情况ToolStripMenuItem_Click(null, null);//刷新页面
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                MessageBox.Show("不是正确的日期格式类型！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }*/

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox2.Text == "" || textBox2.Text.Length > 10)
            {
                MessageBox.Show("请输入正确的书籍编号！");
            }
            else
            {
                string str1 = textBox3.Text.Trim();

                string str3 = textBox6.Text.Trim();

                //更改书籍状态为可借
                string strUpdata1 = "Update Books Set Bstate='可借' Where Bid='" + str1 + "'";
                //删除借阅记录
                string strDelete = "Delete From Borrow Where Sid='" + str0 + "' AND Bid='" + str1 + "'";
                //增加归还记录
                string strInsert2 = "Update Reback Set Returntime='" + str3 + "' Where Bid='" + str1 + "'And Sid='" + str0 + "'";

                string strQuery = "Select Bid From Borrow Where Sid='" + str0 + "' and Bid='" + str1 + "'";

                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    SqlCommand cmd = new SqlCommand(strQuery, con);
                    con.Open();

                    string id2 = (string)cmd.ExecuteScalar();

                    if (string.IsNullOrEmpty(id2))
                    {
                        MessageBox.Show("未借阅该书！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        sqlHelper.OperateTb(strUpdata1);
                        sqlHelper.OperateTb(strInsert2);
                        sqlHelper.OperateTb(strDelete);
                        MessageBox.Show("还书成功");
                        我的借阅情况ToolStripMenuItem_Click(null, null);//刷新页面
                        textBox3.Text = null;
                        textBox6.Text = null;

                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
