using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;

namespace book
{
    class Sql1
    {
        public SqlConnection GetConnection()    // 连接数据库
        {
            string strConn = "Data Source=DESKTOP-NG5CL71;Initial Catalog=Library_Manage_System;Persist Security Info=True;User ID=sa;Password=123456";
            SqlConnection conn = new SqlConnection(strConn);
            conn.ConnectionString = strConn;
            return conn;
        }

        public DataSet GetDataSet(string strQuery)  // 获取数据
        {
            DataSet ds = new DataSet();
            try
            {
                SqlConnection sqlConn = GetConnection();
                SqlDataAdapter adapter = new SqlDataAdapter(strQuery, sqlConn);
                adapter.Fill(ds);
            }
            catch (Exception ex)
            {
                throw ex;
            }
            return ds;
        }

        public int OperateTb(string strCommandText) // 修改
        {
            int intResult = 0;
            SqlConnection conn = new SqlConnection();
            try
            {
                conn = GetConnection();
                SqlCommand cmn = new SqlCommand();
                cmn.Connection = conn;
                cmn.CommandText = strCommandText;

                conn.Open();
                intResult = cmn.ExecuteNonQuery();

            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                if (conn.State == ConnectionState.Open)
                    conn.Close();
            }

            return intResult;
        }
    }
}
