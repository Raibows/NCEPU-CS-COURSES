package Pin;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

import javax.swing.*;

@SuppressWarnings("serial")
public class Sign extends JFrame {
	private	JPanel	panelCerter	=	new JPanel();
	private	JPanel	panelSouth	=	new JPanel();
	
	private	JLabel		label1	=	new JLabel("姓名", SwingConstants.CENTER);
	private	JLabel		label2	=	new JLabel("id     ", SwingConstants.CENTER);
	private	JLabel		label3	=	new JLabel("密码", SwingConstants.CENTER);
	private	JLabel		label4	=	new JLabel("性别    ", SwingConstants.CENTER);
	private	JTextField		t1	=	new JTextField(18);
	private	JTextField		t2	=	new JTextField(18);
	private	JPasswordField	p1	=	new JPasswordField(18);
	private	JRadioButton	rb1	=	new JRadioButton("男", true);
	private	JRadioButton	rb2	=	new JRadioButton("女");
	private ButtonGroup	group	=	new ButtonGroup();
	private	JButton		b1		=	new JButton("确定");
	private	JButton		b2		=	new JButton("取消");
	
	public Sign(String title) {
		super(title);
		Container	cp	=	this.getContentPane();
		
		group.add(rb1);
		group.add(rb2);
		panelCerter.add(label1, BorderLayout.CENTER);
		panelCerter.add(t1, BorderLayout.CENTER);
		panelCerter.add(label2, BorderLayout.CENTER);
		panelCerter.add(t2, BorderLayout.CENTER);
		panelCerter.add(label3, BorderLayout.CENTER);
		panelCerter.add(p1, BorderLayout.CENTER);
		panelCerter.add(label4, BorderLayout.CENTER);
		panelCerter.add(rb1, BorderLayout.CENTER);
		panelCerter.add(rb2, BorderLayout.CENTER);
		panelSouth.add(b1);
		panelSouth.add(b2);
		
		cp.add(panelCerter, BorderLayout.CENTER);
		cp.add(panelSouth, BorderLayout.SOUTH);
	
		Toolkit kit=Toolkit.getDefaultToolkit();
		Dimension screen=kit.getScreenSize();
		int x=screen.width;
		int y=screen.height;
		this.setSize(250,300);			
	    int xcenter=(x-250)/2;
	    int ycenter=(y-300)/2;
	    this.setLocation(xcenter,ycenter);
		
		b1.addActionListener(new MyActionListener());
		b2.addActionListener(new MyActionListener());
		this.setResizable(false);
		this.setVisible(true);
		this.setBackground(new Color(0,204,255));
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	}
	
	private class MyActionListener implements  ActionListener {
		public void actionPerformed(ActionEvent e) {
			String b = e.getActionCommand();
			if (b.equals("确定")) {
				MySQLDemo con = new MySQLDemo();
				con.connect();
				try {
					String uname			= t1.getText().trim();
					@SuppressWarnings("deprecation")
					String password		= p1.getText().trim();
					String uid			= t2.getText().trim();
					int	sex	=	0;
					if (rb2.isSelected()) {
						sex = 1;
					}
					String queryPassword	="insert into user values(?, ?, ?, ?);";
					PreparedStatement smt	= con.conn.prepareStatement(queryPassword);
					smt.setString(1, uid);
					smt.setString(2, uname);
					smt.setInt(3, sex);
					smt.setString(4, password);
					if (smt.executeUpdate() > 0) {
						JOptionPane.showMessageDialog(null,"注册成功");
						Sign.this.dispose();
					}
					
				} catch (Exception e1) {
					e1.printStackTrace();
					JOptionPane.showMessageDialog(null,"请正确填写信息！");
				} finally {
					con.closed();
				}
			} else {
				Sign.this.dispose();
			}
		}
	}
}
