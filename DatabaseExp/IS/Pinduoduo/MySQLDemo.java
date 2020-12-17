package Pin;

import java.sql.*;

public class MySQLDemo {
	static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
    static final String DB_URL = "jdbc:mysql://localhost:3306/shoppingmall?"
    							+ "useUnicode=true&characterEncoding=utf8"
    							+ "&useSSL=false&serverTimezone=GMT%2B8";
 
    static final String USER = "root";
    static final String PASS = "123456";
    Connection conn = null;
    
    // 连接数据库
    public void connect() {
        try{
            Class.forName(JDBC_DRIVER);
        
            System.out.println("连接数据库...");
            conn = DriverManager.getConnection(DB_URL, USER,PASS);
            if (!conn.isClosed()) {
            	System.out.print("数据库连接成功！！");
            }
            
        }catch(SQLException se){
            // 处理 JDBC 错误
            se.printStackTrace();
        }catch(Exception e){
            // 处理 Class.forName 错误
            e.printStackTrace();
        }
    }
    
    
    
    // 关闭连接
    public  void closed() {
    	try{
            if(conn!=null) conn.close();
        }catch(SQLException se){
            se.printStackTrace();
        } finally {
            System.out.println("Goodbye!");
        }
    }
}
