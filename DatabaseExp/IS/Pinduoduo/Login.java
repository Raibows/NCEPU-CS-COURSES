package Pin;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.swing.*;

@SuppressWarnings("serial")
public class Login extends JFrame {
	private	JPanel	panelNorth	=	new JPanel();
	private	JPanel	panelCerter	=	new JPanel();
	private	JPanel	panelSouth	=	new JPanel();
	
	private	JLabel		l		=	new JLabel("<html><font color=red size='7'><i>超市管理系统</i></font>", SwingConstants.CENTER);
	private	JLabel		label1	=	new JLabel("输入用户    ", SwingConstants.CENTER);
	private	JLabel		label2	=	new JLabel("用户密码    ", SwingConstants.CENTER);
	private	JTextField		t1	=	new JTextField(18);
	private	JPasswordField	p1	=	new JPasswordField(18);
	private	JButton		b1		=	new JButton("登录");
	private	JButton		b2		=	new JButton("注册");
	private	JRadioButton	rb1	=	new JRadioButton("用户", true);
	private	JRadioButton	rb2	=	new JRadioButton("商家");
	private ButtonGroup	group	=	new ButtonGroup();
	
	public Login(String title){
		super(title);
		Container	cp	=	this.getContentPane();
		
		group.add(rb1);
		group.add(rb2);
		panelNorth.add(l);
		panelCerter.add(label1, BorderLayout.CENTER);
		panelCerter.add(t1, BorderLayout.CENTER);
		panelCerter.add(label2, BorderLayout.CENTER);
		panelCerter.add(p1, BorderLayout.CENTER);
		panelCerter.add(rb1, BorderLayout.CENTER);
		panelCerter.add(rb2, BorderLayout.CENTER);
		panelSouth.add(b1);
		panelSouth.add(b2);
		
		cp.add(panelNorth, BorderLayout.NORTH);
		cp.add(panelCerter, BorderLayout.CENTER);
		cp.add(panelSouth, BorderLayout.SOUTH);
	
		Toolkit kit=Toolkit.getDefaultToolkit();
		Dimension screen=kit.getScreenSize();
		int x=screen.width;
		int y=screen.height;
		this.setSize(300,300);			
	    int xcenter=(x-300)/2;
	    int ycenter=(y-300)/2;
	    this.setLocation(xcenter,ycenter);
		
		b1.addActionListener(new MyActionListener());
		b2.addActionListener(new MyActionListener());
		this.setResizable(false);
		this.setVisible(true);
		panelCerter.setBackground(new Color(0,204,255));
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private class MyActionListener implements  ActionListener {
		public void actionPerformed(ActionEvent e) {
			String b = e.getActionCommand();
			if (b.equals("登录")) {
				MySQLDemo login_con = new MySQLDemo();
				login_con.connect();
				
				try {
					Statement sql = login_con.conn.createStatement();
					if(rb1.isSelected()) {
						String uid			= t1.getText().trim();
						@SuppressWarnings("deprecation")
						String password			= p1.getText().trim();
						String queryPassword	="select * from user where user_id = '" + uid + "' and password = '" + password + "';";
						
						ResultSet rs = sql.executeQuery(queryPassword);
						
						 if(rs.next())
						{
							 String uname	= rs.getString("user_name");
							 int user_id			= rs.getInt("user_id");
							 JOptionPane.showMessageDialog(null,"登录成功");
							 Login.this.dispose();
							 new User(uname, user_id);
				         }else{
								JOptionPane.showMessageDialog(null,"请输入正确的账号和密码！","提示！", JOptionPane.YES_NO_OPTION);
								
								t1.setText("");
								p1.setText("");
				            }
						} else {
						String pid	= t1.getText().trim();
						@SuppressWarnings("deprecation")
						String password			= p1.getText().trim();
						String queryPassword	="select * from producer where producer_id = '" + pid + "' and password = '" + password + "';";
						
						ResultSet rs = sql.executeQuery(queryPassword);
						
						 if(rs.next())
							{
							 	String uname	= rs.getString("producer_name");
								int producer_id			= rs.getInt("producer_id");
							 JOptionPane.showMessageDialog(null,"登录成功");
							 Login.this.dispose();
							 
							 new Producer(uname, producer_id);
				            }else{
								JOptionPane.showMessageDialog(null,"请输入正确的账号和密码！","提示！", JOptionPane.YES_NO_OPTION);
								
								t1.setText("");
								p1.setText("");
				            }
					}
					
				} catch (SQLException e1) {
					e1.printStackTrace();
				} finally {
					login_con.closed();
				}
			} else {
				new Sign("注册"); 
			}
		}
	}
}

