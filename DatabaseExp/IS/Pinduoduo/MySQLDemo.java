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
    
    // �������ݿ�
    public void connect() {
        try{
            Class.forName(JDBC_DRIVER);
        
            System.out.println("�������ݿ�...");
            conn = DriverManager.getConnection(DB_URL, USER,PASS);
            if (!conn.isClosed()) {
            	System.out.print("���ݿ����ӳɹ�����");
            }
            
        }catch(SQLException se){
            // ���� JDBC ����
            se.printStackTrace();
        }catch(Exception e){
            // ���� Class.forName ����
            e.printStackTrace();
        }
    }
    
    
    
    // �ر�����
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
