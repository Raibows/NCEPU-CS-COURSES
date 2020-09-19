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
	private	JButton		manu_b1	= new JButton("�鿴��Ʒ");
	private JButton		manu_b2	= new JButton("������Ʒ");
	private JButton		manu_b3	= new JButton("ɾ����Ʒ");
	private JButton		manu_b5	= new JButton("�޸���Ʒ");
	private JButton		manu_b4	= new JButton("�˳���¼");
	private JMenuBar	mb 		= new JMenuBar();//�����˵���
	private JTable 		table	= null;
	private Object columnName[]	= {"��Ʒ�˺�", "��Ʒ��", "����", "����", "�̼���"};
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
		int x=screen.width;					// ȡ����ʾ�����ڵĿ��
		int y=screen.height;
		setSize(500,650);		// ��ϵͳ����ƽ��������ʾ������
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
			if (b.equals("�鿴��Ʒ")) {
				Producer.this.viewThing(producer_id);
			} else if (b.equals("������Ʒ")) {
				Producer.this.addThing(producer_id);
			} else if (b.equals("ɾ����Ʒ")) {
				Producer.this.delete();
			} else if (b.equals("�޸���Ʒ")) {
				Producer.this.alter(producer_id);
			}else if (b.equals("�˳���¼")) {
				Producer.this.logout();;
			}
		}
	}
	//��ͼ
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
	    	scrollpane.setBounds(2, 2, 490, 590);//�ƶ�������������С��x,y,kuan,chang
			panelCerter.repaint();//�ػ����
		
			view_con.closed();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	private void alter(int pid) {
		
		if(table==null)
		{
			JOptionPane.showMessageDialog(null,"���ȵ���鿴��Ʒ��ť��");
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
    			System.out.println("���³ɹ�");
    			JOptionPane.showMessageDialog(null,"�޸ĳɹ���");
    		}
			
			smt.close();
			sql.close();
			add_con.closed();
			
			
		} catch (SQLException e) {
			e.printStackTrace();
		}catch (NumberFormatException e) {
			JOptionPane.showMessageDialog(null,"����Ҫ�޸ĵ���Ʒ��Ϣ��");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null,"���������޸���Ʒ��");
		}finally {
			
			Producer.this.viewThing(pid);
		}
		}
	}
	//���
	private void addThing(int pid) {
		if(table==null)
		{
			JOptionPane.showMessageDialog(null,"���ȵ���鿴��Ʒ��ť��");
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
				if (smt.executeUpdate() > 0) {//executeUpdate�ķ���ֵ��һ��������ָʾ��Ӱ�������
					JOptionPane.showMessageDialog(null,"��ӳɹ�");
					Producer.this.viewThing(pid);
					
					smt.close();
					sql.close();
				}
				
			}//end if
			else {
				JOptionPane.showMessageDialog(null,"��Ʒ�Ѿ�����,��ֹ���,���������룡");
				Producer.this.viewThing(pid);
			}
			
			add_con.closed();
		} catch (SQLException e) {
			e.printStackTrace();
			//JOptionPane.showMessageDialog(null,"�������������Ʒ��");
		}catch (NumberFormatException e) {
			JOptionPane.showMessageDialog(null,"�����������Ʒ��Ϣ��");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null,"�������������Ʒ��");
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
			//JOptionPane.showMessageDialog(null,"�������������Ʒ��");
			
			
		} finally {
			return num;
		}
	}
	//�޸�
	private void delete() {
		if(table==null)
		{
			JOptionPane.showMessageDialog(null,"���ȵ���鿴��Ʒ��ť��");
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
						System.out.println("ɾ���ɹ�");
						JOptionPane.showMessageDialog(null,"ɾ���ɹ���");
						}
					
					sql.close();
					delete_con.closed();
				} else {
					JOptionPane.showMessageDialog(null,"����ɾ����");
				}
				
			} }catch (SQLException e) {
				e.printStackTrace();
			} catch (NumberFormatException e) {
				JOptionPane.showMessageDialog(null,"��ѡ��Ҫɾ������Ʒ��");
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null,"��������ɾ����Ʒ��");
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
		JOptionPane.showMessageDialog(null,"лл���٣�ף��������¡��");
		Producer.this.dispose();
		new Login("��ӭ����");
	}
}
