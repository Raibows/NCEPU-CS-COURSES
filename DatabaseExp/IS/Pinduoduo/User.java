package Pin;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

import javax.swing.*;
import javax.swing.border.TitledBorder;

@SuppressWarnings("serial")
public class User extends JFrame {
	private JLabel		l1		= new JLabel("用户账号");
	private JLabel		l2		= new JLabel();
	private JLabel		l3		= new JLabel("用户姓名");
	private JLabel		l4		= new JLabel();
	private JLabel		l5		= new JLabel("性别");
	private JLabel		l6		= new JLabel();
	private JLabel		l7		= new JLabel("密码");
	private JLabel		l8		= new JLabel();
	private	JButton		manu_b1	= new JButton("用户信息");
	private JButton		manu_b2	= new JButton("查看购物结果");
	private JButton		manu_b3	= new JButton("修改信息");
	private JButton		manu_b4	= new JButton("查看商城");
	private JButton		manu_b5	= new JButton("退出登录");
	private	JButton		b1		= new JButton("修改");
	private	JButton		b2		= new JButton("取消");
	private	JButton		b3		= new JButton("购买");
	private	JButton		b4		= new JButton("删除");
	private	JButton		b5		= new JButton("查找");
	private JMenuBar	mb 		= new JMenuBar();
	private	JTextField	t1		= new JTextField();
	private	JTextField	t2		= new JTextField();
	private	JTextField	t3		= new JTextField();
	private	JTextField	t4		= new JTextField();
	private JTable 		table	= null;
	private Object columnName[]	= {"商品账号", "商品名", "单价", "数量", "商家名"};
    private Object 		ar[][]	= new Object[80][5];
	private	int user_id;
	
	private	JPanel	panelCerter	=	new JPanel();

	public User(String title, int uid) {
		super(title);
		user_id = uid;
		Container	cp	=	this.getContentPane();
		l1.setFont(new Font("宋体", Font.BOLD, 20));
		l3.setFont(new Font("宋体", Font.BOLD, 20));
		l5.setFont(new Font("宋体", Font.BOLD, 20));
		l7.setFont(new Font("宋体", Font.BOLD, 20));
		l8.setFont(new Font("宋体", Font.BOLD, 20));
		b1.setFont(new Font("宋体", Font.BOLD, 20));
		b2.setFont(new Font("宋体", Font.BOLD, 20));
		b3.setFont(new Font("宋体", Font.BOLD, 20));
		b4.setFont(new Font("宋体", Font.BOLD, 20));
		b5.setFont(new Font("宋体", Font.BOLD, 20));
		
		mb.add(manu_b1);
		mb.add(manu_b2);
		mb.add(manu_b3);
		mb.add(manu_b4);
		mb.add(manu_b5);
		panelCerter.setBorder(BorderFactory.createTitledBorder(BorderFactory
				.createLineBorder(Color.black, 2),null, 
				TitledBorder.CENTER, TitledBorder.TOP));
		panelCerter.setLayout(null);
		cp.add(mb,"North");
		cp.add(panelCerter,"Center");
		
		Toolkit kit=Toolkit.getDefaultToolkit();
		Dimension screen=kit.getScreenSize();
		int x=screen.width;					// 取得显示器窗口的宽度
		int y=screen.height;
		setSize(500,650);		// 让系统窗口平铺整个显示器窗口
	    int xcenter=(x-500)/2;
	    int ycenter=(y-650)/2;
	    setLocation(xcenter,ycenter);
	    
	    manu_b1.addActionListener(new MyActionListener());
	    manu_b2.addActionListener(new MyActionListener());
	    manu_b3.addActionListener(new MyActionListener());
	    manu_b4.addActionListener(new MyActionListener());
	    manu_b5.addActionListener(new MyActionListener());
	    b1.addActionListener(new MyActionListener());
	    b2.addActionListener(new MyActionListener());
	    b3.addActionListener(new MyActionListener());
	    b4.addActionListener(new MyActionListener());
	    b5.addActionListener(new MyActionListener());
	    this.setResizable(false);
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private class MyActionListener implements  ActionListener {
		public void actionPerformed(ActionEvent e) {
			String b = e.getActionCommand();
			if (b.equals("用户信息")) {
				User.this.view(User.this.user_id);
			} else if (b.equals("修改")) {
				User.this.updateInfo(User.this.user_id);
			} else if (b.equals("取消")) {
				User.this.cancel();
			} else if (b.equals("查看购物结果")) {
				User.this.viewCart(User.this.user_id);
			} else if (b.equals("删除")) {
				User.this.deleteCart(User.this.user_id);
			} else if (b.equals("修改信息")) {
				User.this.update(User.this.user_id);
			} else if (b.equals("购买")) {
				User.this.addToCart(User.this.user_id);
			} else if (b.equals("查找")) {
				User.this.search();
			} else if (b.equals("查看商城")) {
				User.this.viewShop();
			} else if (b.equals("退出登录")) {
				User.this.logout();
			}
		}
	}
	
	private void view(int id) {
		MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql		= view_con.conn.createStatement();
			String		view	= "select user_id, user_name, sex from user where user_id = '" + id + "';";
			
			ResultSet rs = sql.executeQuery(view);
			if(rs.next()) {
				int uid			= rs.getInt("user_id");
                String uname	= rs.getString("user_name");
                int sex			= rs.getInt("sex");
                String usex		= null;
                if (sex == 0) {
                	usex = "男";
                } else {
                	usex = "女";
                }
                
                l2.setText("" + uid);
                l2.setFont(new Font("宋体", Font.BOLD, 20));
                l4.setText(uname);
                l4.setFont(new Font("宋体", Font.BOLD, 20));
                l6.setText(usex);
                l6.setFont(new Font("宋体", Font.BOLD, 20));

                panelCerter.removeAll();
                panelCerter.add(l1);
                l1.setBounds(0, 0, 100, 30);
                panelCerter.add(l2);
                l2.setBounds(130, 0, 500, 30);
                panelCerter.add(l3);
                l3.setBounds(0, 30, 100, 30);
                panelCerter.add(l4);
                l4.setBounds(130, 30, 500, 30);
                panelCerter.add(l5);
                l5.setBounds(0, 60, 100, 30);
                panelCerter.add(l6);
                l6.setBounds(130, 60, 500, 30);
                panelCerter.revalidate();
                panelCerter.repaint();
                
                sql.close();
                view_con.closed();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	private void update(int id) {
		MySQLDemo update_con = new MySQLDemo();
		update_con.connect();
		
		try {
			Statement	sql		= update_con.conn.createStatement();
			String		view	= "select user_id, user_name, sex, password from user where user_id = '" + id + "';";
			
			ResultSet rs = sql.executeQuery(view);
			if(rs.next()) {
				int uid			= id;
                String uname	= rs.getString("user_name");
                int sex			= rs.getInt("sex");
                String upass	= rs.getString("password");
                String usex		= null;
                if (sex == 0) {
                	usex = "男";
                } else {
                	usex = "女";
                }
                
                l8.setText("" + uid);
                t1.setFont(new Font("宋体", Font.BOLD, 20));
                t2.setText(uname);
                t2.setFont(new Font("宋体", Font.BOLD, 20));
                t3.setText(usex);
                t3.setFont(new Font("宋体", Font.BOLD, 20));
                t4.setText(upass);
                t4.setFont(new Font("宋体", Font.BOLD, 20));

                panelCerter.removeAll();
                panelCerter.add(l1);
                l1.setBounds(0, 0, 100, 30);
                panelCerter.add(l8);
                l8.setBounds(130, 3, 300, 30);
                panelCerter.add(l3);
                l3.setBounds(0, 30, 100, 30);
                panelCerter.add(t2);
                t2.setBounds(130, 33, 300, 30);
                panelCerter.add(l5);
                l5.setBounds(0, 60, 100, 30);
                panelCerter.add(t3);
                t3.setBounds(130, 63, 30, 30);
                panelCerter.add(l7);
                l7.setBounds(0, 90, 100, 30);
                panelCerter.add(t4);
                t4.setBounds(130, 93, 300, 30);
                panelCerter.add(b1);
                b1.setBounds(130, 183, 100, 30);
                panelCerter.add(b2);
                b2.setBounds(270, 183, 100, 30);
                panelCerter.revalidate();
                panelCerter.repaint();
        		
                sql.close();
                rs.close();
                update_con.closed();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

}
	
	private void updateInfo(int id) {
		MySQLDemo updateInfo_con = new MySQLDemo();
 		updateInfo_con.connect();
		PreparedStatement pstmt	= null;
        String updateInfo 		= null;
   
        try {
        	int uid			= id;
            String sex		= t3.getText();
            int usex		= 0;          
            Statement sql	= updateInfo_con.conn.createStatement();
            
			int i = 0;
        	if (t2.getText() != null) {
				updateInfo 	= "update user set user_name=? where user_id= '" + uid + "' ;";
                pstmt		=	updateInfo_con.conn.prepareStatement(updateInfo);
				pstmt.setString(1, t2.getText());
				
				int res1 = pstmt.executeUpdate();
				if(res1 > 0){
					System.out.println("更新数据成功");
					i ++;
				}
				
				if (sex != null) {
					if (sex.equals("男")) {
						usex = 0;
					} else if(sex.equals("女")) {
						usex = 1;
					}
					
					updateInfo 		= "update user set sex=? where user_id= '" + uid + "' ;";
	                pstmt	=	updateInfo_con.conn.prepareStatement(updateInfo);
					pstmt.setInt(1, usex);
					
					int res2 = pstmt.executeUpdate();
					if(res2 > 0){
						System.out.println("更新数据成功");
						i ++;
					}
				}
				
				if (t4.getText() != null) {
					updateInfo 		= "update user set password=? where user_id= '" + uid + "' ;";
	                pstmt	=	updateInfo_con.conn.prepareStatement(updateInfo);
	                pstmt.setString(1, t4.getText());
	                
	                int res3 = pstmt.executeUpdate();
	    			if(res3 > 0){
	    				System.out.println("更新数据成功");
	    				i ++;
	    			}
				}
			}
        	
        	if (i > 0) {
        		JOptionPane.showMessageDialog(null,"修改成功");
        		panelCerter.removeAll();
        		panelCerter.repaint();
        	}

			pstmt.close();
			sql.close();
			updateInfo_con.closed();
		} catch (SQLException e2) {
			e2.printStackTrace();
		} finally {
			User.this.view(id);
		}
	}

	private void cancel() {
		panelCerter.removeAll();
		panelCerter.repaint();
	}
	
	private void viewShop() {
		MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql 	= view_con.conn.createStatement();
			String 		s		= "select thing_id, thing_name, price, num, producer_name"
								+ " from thing inner join producer on thing.producer_id = producer.producer_id;";
			ResultSet 	rs		= sql.executeQuery(s);
		  
				int i = 79;
				while(i>=0)
				{	
					ar[i][0]="";
					ar[i][1]="";
					ar[i][2]="";
					ar[i][3]="";
					ar[i][4]="";
					i--;
				}
				
				i = 0;
				while(rs.next() && Integer.parseInt(rs.getString(4)) != 0){
				    String thing_id		= rs.getString(1);
					String thing_name	= rs.getString(2);
					String price		= rs.getString(3);
					String num			= rs.getString(4);
					String produce_name	= rs.getString(5);
					ar[i][0]	= thing_id;
					ar[i][1]	= thing_name;
					ar[i][2]	= price;
					ar[i][3]	= num;
					ar[i][4]	= produce_name;
					i++;
				}
				
				panelCerter.removeAll();
				table = new JTable(ar, columnName);
				table.setRowHeight(20);
		    	JScrollPane scrollpane = new JScrollPane(table);
		    	panelCerter.add(scrollpane);
		    	scrollpane.setBounds(2, 2, 490, 550);
		    	panelCerter.add(b3);
		    	b3.setBounds(135, 553, 100, 35);
		    	panelCerter.add(b5);
		    	b5.setBounds(235, 553, 100, 35);
				panelCerter.repaint();
				
		    	sql.close();
		    	rs.close();
				view_con.closed();
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	private void search() {
		String input = JOptionPane.showInputDialog("查找商品");
		
		if(input == null) {
			User.this.viewShop();
		} else {
			MySQLDemo search_con = new MySQLDemo();
			search_con.connect();
			
			try {
				Statement	sql		= search_con.conn.createStatement();
				String		view	= "select thing_id, thing_name, price, num, producer_name "
									+ "from thing inner join producer on thing.producer_id = producer.producer_id "
									+ "where thing_name like '%" + input + "%';";
				ResultSet rs = sql.executeQuery(view);
				
				int i = 79;
				while(i>=0)
				{	
					ar[i][0]="";
					ar[i][1]="";
					ar[i][2]="";
					ar[i][3]="";
					ar[i][4]="";
					i--;
				}
				
				i = 0;
				while(rs.next() && Integer.parseInt(rs.getString(4)) != 0){
				    String thing_id		= rs.getString(1);
					String thing_name	= rs.getString(2);
					String price		= rs.getString(3);
					String num			= rs.getString(4);
					String produce_name	= rs.getString(5);
					ar[i][0]	= thing_id;
					ar[i][1]	= thing_name;
					ar[i][2]	= price;
					ar[i][3]	= num;
					ar[i][4]	= produce_name;
					i++;
				}
				
				panelCerter.removeAll();
				table = new JTable(ar, columnName);
				table.setRowHeight(20);
		    	JScrollPane scrollpane = new JScrollPane(table);
		    	panelCerter.add(scrollpane);
		    	scrollpane.setBounds(2, 2, 490, 550);
		    	panelCerter.add(b3);
		    	b3.setBounds(199, 553, 100, 30);
				panelCerter.repaint();
				
		    	sql.close();
		    	rs.close();
		    	search_con.closed();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void addToCart(int id) {
		int count = table.getSelectedRow();
		if(count >= 0) {
			int thing_id		= Integer.parseInt(table.getValueAt(count, 0).toString());
			String thing_name	= table.getValueAt(count, 1).toString();
			int num				= Integer.parseInt(table.getValueAt(count, 3).toString());
			int cnum			= 0;
			
			// 加入购物车
			try {
				MySQLDemo add_con = new MySQLDemo();
				add_con.connect();
				Statement	sql	= add_con.conn.createStatement();
				String		add	= null;
				
				cnum = User.this.haveThing(thing_id);
				System.out.println(cnum);
				if(num >= 1) {
					num --;
					
					if (cnum != 0) {
						cnum ++;
						System.out.println(cnum);
						add = "update cart set num = ? where user_id= '" + id + "' and thing_id = '" + thing_id + "' ;";
						
						PreparedStatement smt	= add_con.conn.prepareStatement(add);
						smt.setInt(1, cnum);
						int res = smt.executeUpdate();
						System.out.println(res);
						if(res > 0){
		    				System.out.println("更新成功");
		    				JOptionPane.showMessageDialog(null,"添加成功");
		    			}
						smt.close();
						
					} else if(cnum == 0) {
						add = "insert into cart values(?, ?, ?, ?);";
						
						PreparedStatement smt	= add_con.conn.prepareStatement(add);
						smt.setInt(1, id);
						smt.setInt(2, thing_id);
						smt.setString(3, thing_name);
						smt.setInt(4, 1);
						
						if (smt.executeUpdate() > 0) {
							JOptionPane.showMessageDialog(null,"添加成功");
						}
						smt.close();
					}
					
					sql.close();
					add_con.closed();
				}
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			// 更新商城
			try {
				MySQLDemo add_con = new MySQLDemo();
				add_con.connect();
				
				Statement	sql	= add_con.conn.createStatement();
				String		update	= null;
				
				update = "update thing set num = ? where thing_id = '" + thing_id + "' ;";
				PreparedStatement smt	= add_con.conn.prepareStatement(update);
				smt.setInt(1, num);
				int res = smt.executeUpdate();

				if(res > 0){
	    			System.out.println("更新成功");
	    		}
				
				smt.close();
				sql.close();
				add_con.closed();
			} catch (SQLException e) {
				e.printStackTrace();
			} finally {
				User.this.viewCart(id);
			}
		}
	}
	
	@SuppressWarnings({ "finally" })
	private int haveThing(int thing_id) {
		int num = 0;
		MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql		= view_con.conn.createStatement();
			String		view	= "select num from cart where thing_id = '" + thing_id + "'and user_id = '" + user_id + "';";
			ResultSet rs = sql.executeQuery(view);
			
			if(rs.next()) {
				num = rs.getInt("num");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			return num;
		}
	}

	private void viewCart(int id) {
		MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql		= view_con.conn.createStatement();
			String		view	= "select cart.thing_id, cart.thing_name, thing.price, cart.num, producer_name"
								+ " from cart,thing, producer "
								+ "where cart.thing_id = thing.thing_id and thing.producer_id = producer.producer_id "
								+ "and user_id = '" + id + "';";
			
			ResultSet rs = sql.executeQuery(view);
			int i = 79;
			while(i>=0)
			{	
				ar[i][0]="";
				ar[i][1]="";
				ar[i][2]="";
				ar[i][3]="";
				ar[i][4]="";
				i--;
			}
			
			i = 0;
			while(rs.next()) {
				int tid			= rs.getInt("thing_id");
                String tname	= rs.getString("thing_name");
                int price			= rs.getInt("price");
                int num			= rs.getInt("num");
                String pname	= rs.getString("producer_name");
                
                ar[i][0]	= tid;
				ar[i][1]	= tname;
				ar[i][2]	= price;
				ar[i][3]	= num;
				ar[i][4]	= pname;
				i ++;
			}
			
			panelCerter.removeAll();
			table = new JTable(ar, columnName);
			table.setRowHeight(20);
	    	JScrollPane scrollpane = new JScrollPane(table);
	    	panelCerter.add(scrollpane);
	    	scrollpane.setBounds(2, 2, 490, 550);
	    	panelCerter.add(b4);
	    	b4.setBounds(199, 553, 100, 35);
			panelCerter.repaint();
			
			view_con.closed();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	private void deleteCart(int id) {
		int count = table.getSelectedRow();
		if(count >= 0) {
			int thing_id		= Integer.parseInt(table.getValueAt(count, 0).toString());
			
			if(JOptionPane.showConfirmDialog(null, "是否删除？", "删除", JOptionPane.YES_NO_OPTION) == 0) {
				try {
					MySQLDemo delete_con = new MySQLDemo();
					delete_con.connect();
					Statement	sql	= delete_con.conn.createStatement();
					
					String		delete	= "delete from cart where thing_id = '" + thing_id +  "' and user_id = '" +  id + "';";
					int 			res = sql.executeUpdate(delete);
					
					if(res > 0){
						System.out.println("删除成功");
						JOptionPane.showMessageDialog(null,"删除成功！");
					}
					
					sql.close();
					delete_con.closed();
				} catch (SQLException e) {
					e.printStackTrace();
				}
				
				try {
					MySQLDemo delete_con = new MySQLDemo();
					delete_con.connect();
					Statement	sql	= delete_con.conn.createStatement();
					
					if(User.this.producerThingNum(thing_id) == 0) {
						String		delete	= "delete from thing where thing_id = '" + thing_id + "';";
						int 			res = sql.executeUpdate(delete);
						
						if(res > 0){
							System.out.println("删除成功");
						}
						
						sql.close();
						delete_con.closed();
					}
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
			
			User.this.viewCart(id);
		}
	}
	
	@SuppressWarnings("finally")
	private int producerThingNum(int tid) {
		int num = 0;
		
		MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql		= view_con.conn.createStatement();
			String		view	= "select num from thing where thing_id = '" + tid + "';";
			ResultSet rs = sql.executeQuery(view);
			
			if(rs.next()) {
				num = rs.getInt("num");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			return num;
		}
	}
	
	private void logout() {
		JOptionPane.showMessageDialog(null,"谢谢光临！");
		User.this.dispose();
		new Login("欢迎光临");
	}
}