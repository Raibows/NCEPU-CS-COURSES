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
    public partial class Admin : Form
    {
        int K;  // 用于170行dataGridView1_SelectionChanged函数判断，仅当 K = 0 即选择书籍管理时才会显示

        public Admin()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {}

        private void Admin_Load(object sender, EventArgs e)
        {
            panel1.Visible = false;
            panel4.Visible = false;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;//选中整行

        }

        private void 书籍查询ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            panel1.Visible = false;
            panel4.Visible = false;
            panel6.Visible = true;
            panel5.Visible = true;
            Sql1 sqlHelper = new Sql1();
            SqlConnection con = sqlHelper.GetConnection();
            con.Open();
            string strQuery = "select Bid as 书籍编号, Bname as 书名, Bpress as 出版社, Bstate as 状态, Bwriter as 作者, Bdate as 出版时间 from Books";
            try
            {
                DataSet ds = sqlHelper.GetDataSet(strQuery);
                DataTable dt = ds.Tables[0];

                dataGridView6.DataSource = dt;


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 书籍管理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            K = 0;
            //初始显示
            panel1.Visible = true;
            panel4.Visible = false;
            panel6.Visible = false;
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

        private void 用户管理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            K = 1;

            panel1.Visible = false;
            panel4.Visible = true;
            panel6.Visible = false;
            panel5.Visible = false;
            Sql1 sqlHelper = new Sql1();
            SqlConnection con = sqlHelper.GetConnection();
            con.Open();
            string strQuery = "select Sid as 学号, Sname as 姓名 from Students";
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

        private void 书籍借阅管理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            K = 2;

            panel1.Visible = false;
            panel4.Visible = false;
            panel6.Visible = false;
            panel5.Visible = false;
            Sql1 sqlHelper = new Sql1();
            SqlConnection con = sqlHelper.GetConnection();
            con.Open();
            string strQuery = "select Borrow.Bid as 书籍编号, Borrow.Sid as 读者编号, Borrowtime as 借出时间, Returntime as 归还时间 From Borrow, Reback Where Borrow.Bid=Reback.Bid";
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

        private void button3_Click(object sender, EventArgs e)
        {
            //刷新显示
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
            textBox1.Text = null;
            textBox2.Text = null;
            textBox3.Text = null;
            comboBox1.Text = null;
            textBox5.Text = null;
            dateTimePicker1.Value = DateTime.Now;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //添加书籍
            DateTime dt = new DateTime();
            dt = DateTime.Now;
            if (textBox1.Text.Trim() == "")
            { MessageBox.Show("请输入书籍编号！"); }
            else if (textBox2.Text.Trim() == "")
            { MessageBox.Show("请输入书名！"); }
            else if (textBox3.Text.Trim() == "")
            { MessageBox.Show("请输入出版社！"); }
            else if (comboBox1.Text.Trim() == "")
            { MessageBox.Show("请输入状态！"); }
            else if (textBox5.Text.Trim() == "")
            { MessageBox.Show("请输入作者！"); }
            else if (DateTime.Compare(dateTimePicker1.Value.Date, dt) > 0)
            { MessageBox.Show("日期超前，请选择正确日期！"); }
            else
            {
                string Bid = textBox1.Text.Trim();
                string Bname = textBox2.Text.Trim();
                string Bpress = textBox3.Text.Trim();
                string Bstate = comboBox1.Text.Trim();
                string Bwriter = textBox5.Text.Trim();
                string Bdate = dateTimePicker1.Value.Date.ToShortDateString();
                string strInsert = "Insert Into Books(Bid,Bname,Bpress,Bstate,Bwriter,Bdate) Values('"
                                + Bid + "','" + Bname + "','" + Bpress + "','" + Bstate + "','" + Bwriter + "','" + Bdate + "')";

                //string strQuery1 = "Select Bstate as 状态 From Books Where Bstate='" + comboBox1.Text + "' ";
                Sql1 sqlHelper = new Sql1();
                SqlConnection con = sqlHelper.GetConnection();
               // SqlCommand cmd1 = new SqlCommand(strQuery1, con);
                con.Open();
               // string id1 = (string)cmd1.ExecuteScalar();

                try
                {
                    //con.Open();
                    SqlCommand com = new SqlCommand("select Bid from Books where Bid='" + Bid + "'", con);
                    SqlDataReader sdr = com.ExecuteReader();
                    if (sdr.HasRows)
                    { MessageBox.Show("该书籍已存在！"); }
                    else
                    {
                        int intResult = sqlHelper.OperateTb(strInsert);
                        MessageBox.Show("成功添加" + intResult + "记录！");
                        书籍管理ToolStripMenuItem_Click(null, null);
                    }
                    con.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //修改书籍
            DateTime dt = new DateTime();
            dt = DateTime.Now;
            if (textBox1.Text.Trim() == "")
            { MessageBox.Show("请输入书籍编号！"); }
            else if (textBox2.Text.Trim() == "")
            { MessageBox.Show("请输入书名！"); }
            else if (textBox3.Text.Trim() == "")
            { MessageBox.Show("请输入出版社！"); }
            else if (comboBox1.Text.Trim() == "")
            { MessageBox.Show("请输入状态！"); }
            else if (textBox5.Text.Trim() == "")
            { MessageBox.Show("请输入作者！"); }
            else if (DateTime.Compare(dateTimePicker1.Value.Date, dt) > 0)
            { MessageBox.Show("日期超前，请选择正确日期！"); }
            else
            {

                string Bid = textBox1.Text.Trim();
                string Bname = textBox2.Text.Trim();
                string Bpress = textBox3.Text.Trim();
                string Bstate = comboBox1.Text.Trim();
                string Bwriter = textBox5.Text.Trim();
                string Bdate = dateTimePicker1.Value.Date.ToShortDateString();

                string strUpdata = "Update Books Set Bid='" + Bid + "',Bname='" + Bname + "',Bpress='" + Bpress + "',Bstate='" + Bstate + "',Bwriter='" + Bwriter + "',Bdate='" + Bdate + "' Where Bid='" + Bid + "'";
                
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    SqlConnection con = sqlHelper.GetConnection();
                    con.Open();
                    SqlCommand com = new SqlCommand("select Bid from Books where Bid='" + Bid + "'", con);
                    SqlDataReader sdr = com.ExecuteReader();
                    if (sdr.HasRows)
                    {
                        sqlHelper.OperateTb(strUpdata);
                        MessageBox.Show("修改成功！");
                        书籍管理ToolStripMenuItem_Click(null, null);
                    }
                    else
                    {
                        MessageBox.Show("修改失败！不存在该书籍");
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //删除书籍
            if (textBox1.Text.Trim() == "")
            {
                MessageBox.Show("请输入书籍编号！");
            }
            else
            {
                string Bid = textBox1.Text.Trim();
                DialogResult dialogResult = MessageBox.Show("你确定要删除编号为：" + Bid + "的这本书籍的信息吗？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (dialogResult == DialogResult.No)
                {
                    return;
                }
                string strSelect = "Select Bid From Books Where Bid='" + Bid + "'";
                string strDelete = "Delete From Books Where Bid='" + Bid + "'";

                Sql1 sqlHelper = new Sql1();
                SqlConnection con = sqlHelper.GetConnection();
                SqlCommand cmd = new SqlCommand(strSelect, con);
                con.Open();
                if (cmd.ExecuteScalar() == null)
                {
                    MessageBox.Show("不存在该书籍编号！");
                }
                else
                {
                    try
                    {
                        sqlHelper.OperateTb(strDelete);
                        MessageBox.Show("删除成功！");
                        书籍管理ToolStripMenuItem_Click(null, null);
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {  
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            if ((dataGridView1.SelectedRows.Count > 0)&&(K==0))
            {
                textBox1.Text = dataGridView1.SelectedRows[0].Cells["书籍编号"].Value.ToString();
                textBox2.Text = dataGridView1.SelectedRows[0].Cells["书名"].Value.ToString();
                textBox3.Text = dataGridView1.SelectedRows[0].Cells["出版社"].Value.ToString();
                comboBox1.Text = dataGridView1.SelectedRows[0].Cells["状态"].Value.ToString();
                textBox5.Text = dataGridView1.SelectedRows[0].Cells["作者"].Value.ToString();
            }
        }

       
    
        private void button6_Click(object sender, EventArgs e)
        {
            reg f = new reg();
            f.ShowDialog();
            用户管理ToolStripMenuItem_Click(null, null);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows[0].Cells["学号"].Value == null)
            {
                MessageBox.Show("请选择用户！");
            }
            else
            {
                string Unum = dataGridView1.SelectedRows[0].Cells["学号"].Value.ToString();
                DialogResult dialogResult = MessageBox.Show("你确定要删除学号为：" + Unum + "的这名用户的所有信息吗？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

                if (dialogResult == DialogResult.No)
                    return;

                string strDelete1 = "Delete From Students Where Sid='" + Unum + "'";
                //string strDelete2 = "Delete From Borrow Where Unum='" + Unum + "'";
                //string strDelete3 = "Delete From Reback Where Unum='" + Unum + "'";
                try
                {
                    Sql1 sqlHelper = new Sql1();
                    sqlHelper.OperateTb(strDelete1);
                    //sqlHelper.OperateTb(strDelete2);
                    //sqlHelper.OperateTb(strDelete3);
                    用户管理ToolStripMenuItem_Click(null, null);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows[0].Cells["学号"].Value == null)
            {
                MessageBox.Show("请选择用户！");
            }
            else
            {
                string Unum = dataGridView1.SelectedRows[0].Cells["学号"].Value.ToString();
                mem f = new mem();
                f.str0 = Unum;
                f.ShowDialog();
                用户管理ToolStripMenuItem_Click(null, null);
            }
        }

        private void panel4_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }


        private void comboBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        

        private void panel6_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dataGridView6_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void panel5_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            //查询书籍
            //string strnum = comboBox1.Items[comboBox1.SelectedIndex].ToString();
            string str = textBox4.Text.Trim();
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

                dataGridView6.DataSource = dt;

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

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void panel3_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
