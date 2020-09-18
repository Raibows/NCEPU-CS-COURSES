package Pin;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.swing.*;
import javax.swing.border.TitledBorder;


@SuppressWarnings("serial")
public class Producer extends JFrame {
	private	JButton		manu_b1	= new JButton("查看商品");
	private JButton		manu_b2	= new JButton("增加商品");
	private JButton		manu_b3	= new JButton("删除商品");
	private JButton		manu_b5	= new JButton("修改商品");
	private JButton		manu_b4	= new JButton("退出登录");
	private JMenuBar	mb 		= new JMenuBar();//创建菜单栏
	private JTable 		table	= null;
	private Object columnName[]	= {"商品账号", "商品名", "单价", "数量", "商家名"};
    private Object 		ar[][]	= new Object[80][5];
	private	int producer_id;
	
	private	JPanel	panelCerter	=	new JPanel();
	
	public Producer(String title, int pid) {
		super(title);
		producer_id = pid;
		
		Container cp	=	this.getContentPane();
		mb.add(manu_b1);
		mb.add(manu_b2);
		mb.add(manu_b3);
		mb.add(manu_b5);
		mb.add(manu_b4);
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
	    manu_b5.addActionListener(new MyActionListener());
	    manu_b4.addActionListener(new MyActionListener());
	    
	    this.setResizable(false);
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private class MyActionListener implements  ActionListener {
		public void actionPerformed(ActionEvent e) {
			String b = e.getActionCommand();
			if (b.equals("查看商品")) {
				Producer.this.viewThing(producer_id);
			} else if (b.equals("增加商品")) {
				Producer.this.addThing(producer_id);
			} else if (b.equals("删除商品")) {
				Producer.this.delete();
			} else if (b.equals("修改商品")) {
				Producer.this.alter(producer_id);
			}else if (b.equals("退出登录")) {
				Producer.this.logout();;
			}
		}
	}
	//视图
	private void viewThing(int pid) {
    	MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql 	= view_con.conn.createStatement();
			String 		s		= "select thing_id, thing_name, price, num, producer_name"
								+ " from thing inner join producer on thing.producer_id = producer.producer_id where producer.producer_id = '"
								+ pid + "';";
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
			while(rs.next()){
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
	    	scrollpane.setBounds(2, 2, 490, 590);//移动组件并调整其大小，x,y,kuan,chang
			panelCerter.repaint();//重绘组件
		
			view_con.closed();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	private void alter(int pid) {
		
		if(table==null)
		{
			JOptionPane.showMessageDialog(null,"请先点击查看商品按钮！");
		}else{
			try{
			int count = table.getSelectedRow();
			int thing_id		= Integer.parseInt(table.getValueAt(count, 0).toString());
			String thing_name	= table.getValueAt(count, 1).toString();
			System.out.println(thing_name);
			int num				= Integer.parseInt(table.getValueAt(count, 3).toString());
			int price			= Double.valueOf(Double.parseDouble(table.getValueAt(count, 2).toString())).intValue();
			
			MySQLDemo add_con = new MySQLDemo();
			add_con.connect();
			
			Statement	sql	= add_con.conn.createStatement();
			String		update1	= null;
			System.out.println(thing_id);

			System.out.println(num);

			System.out.println(price);

			System.out.println(thing_name);
			
			update1 = "update thing set thing_name = ?,price = ? ,num = ? where thing_id = '" + thing_id + "' ;";
			PreparedStatement smt	= add_con.conn.prepareStatement(update1);
			smt.setString(1, thing_name);
			smt.setInt(2, price);
			smt.setInt(3, num);
			
			int res1 = smt.executeUpdate();

			if(res1 > 0){
    			System.out.println("更新成功");
    			JOptionPane.showMessageDialog(null,"修改成功！");
    		}
			
			smt.close();
			sql.close();
			add_con.closed();
			
			
		} catch (SQLException e) {
			e.printStackTrace();
		}catch (NumberFormatException e) {
			JOptionPane.showMessageDialog(null,"请点击要修改的商品信息！");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null,"请点击表栏修改商品！");
		}finally {
			
			Producer.this.viewThing(pid);
		}
		}
	}
	//添加
	private void addThing(int pid) {
		if(table==null)
		{
			JOptionPane.showMessageDialog(null,"请先点击查看商品按钮！");
		}
		else{
			
			try {
				int count 			= table.getSelectedRow();
				int thing_id        = Integer.parseInt(table.getValueAt(count, 0).toString());
				String thing_name	= table.getValueAt(count, 1).toString();
				int price			= Double.valueOf(Double.parseDouble(table.getValueAt(count, 2).toString())).intValue();
				int num				= Integer.parseInt(table.getValueAt(count, 3).toString());
		
		
				MySQLDemo add_con = new MySQLDemo();
				add_con.connect();
		
		
			if(Producer.this.inProducer(thing_id) == 0) {
				Statement	sql 	= add_con.conn.createStatement();
				String 		s		= "insert into thing values(?, ?, ?, ?, ?);";
				
				PreparedStatement smt	= add_con.conn.prepareStatement(s);
				smt.setInt(1, thing_id);
				smt.setString(2, thing_name);
				smt.setInt(3, price);
				smt.setInt(4, num);
				smt.setInt(5, pid);
				if (smt.executeUpdate() > 0) {//executeUpdate的返回值是一个整数，指示受影响的行数
					JOptionPane.showMessageDialog(null,"添加成功");
					Producer.this.viewThing(pid);
					
					smt.close();
					sql.close();
				}
				
			}//end if
			else {
				JOptionPane.showMessageDialog(null,"商品已经存在,禁止添加,请重新输入！");
				Producer.this.viewThing(pid);
			}
			
			add_con.closed();
		} catch (SQLException e) {
			e.printStackTrace();
			//JOptionPane.showMessageDialog(null,"请点击表栏添加商品！");
		}catch (NumberFormatException e) {
			JOptionPane.showMessageDialog(null,"请完整添加商品信息！");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null,"请点击表栏添加商品！");
		}
		}
	}


	@SuppressWarnings({ "finally" })
	private int inProducer(int tid) {
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
			//JOptionPane.showMessageDialog(null,"请点击表栏添加商品！");
			
			
		} finally {
			return num;
		}
	}
	//修改
	private void delete() {
		if(table==null)
		{
			JOptionPane.showMessageDialog(null,"请先点击查看商品按钮！");
		}
		else{
			try {
				int count = table.getSelectedRow();
		
				if(count >= 0) {
					int thing_id		= Integer.parseInt(table.getValueAt(count, 0).toString());
			
			
					if(!Producer.this.inCart(thing_id)) {
						MySQLDemo delete_con = new MySQLDemo();
						delete_con.connect();
						Statement	sql	= delete_con.conn.createStatement();
					
						String		delete	= "delete from thing where thing_id = '" + thing_id + "';";
						int 			res = sql.executeUpdate(delete);
					
						if(res > 0){
						System.out.println("删除成功");
						JOptionPane.showMessageDialog(null,"删除成功！");
						}
					
					sql.close();
					delete_con.closed();
				} else {
					JOptionPane.showMessageDialog(null,"不能删除！");
				}
				
			} }catch (SQLException e) {
				e.printStackTrace();
			} catch (NumberFormatException e) {
				JOptionPane.showMessageDialog(null,"请选择要删除的商品！");
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null,"请点击表栏删除商品！");
			}finally {
				Producer.this.viewThing(Producer.this.producer_id);
			}
		}

	}
	
	@SuppressWarnings("finally")
	private boolean inCart(int tid) {
		boolean num = false;
		
		MySQLDemo view_con = new MySQLDemo();
		view_con.connect();
		
		try {
			Statement	sql		= view_con.conn.createStatement();
			String		view	= "select * from cart where thing_id = '" + tid + "';";
			ResultSet rs = sql.executeQuery(view);
			
			if(rs.next()) {
				num = true;
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			return num;
		}
	}
	
	private void logout() {
		JOptionPane.showMessageDialog(null,"谢谢光临，祝您生意兴隆！");
		Producer.this.dispose();
		new Login("欢迎光临");
	}
}
