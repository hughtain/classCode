package Wifi;

import java.awt.BorderLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

public class test extends JFrame implements Runnable {
	
	
	 ImageIcon icon = new ImageIcon("image\\unem.png");
	 ImageIcon icon1 = new ImageIcon("image\\em.png");
	 JButton startGame = new JButton();
	 
	 
	 
	 JLabel l13=new JLabel("�¶����ֵ(��):");
	 JLabel l14=new JLabel("�¶����ֵ(��):");
	 JTextField T4=new JTextField();
	 JTextField T5=new JTextField();
	 
	 JLabel l15=new JLabel("ʪ�����ֵ(RH):");
	 JLabel l16=new JLabel("ʪ�����ֵ(RH):");
	 JTextField T6=new JTextField();
	 JTextField T7=new JTextField();
	 
	 JLabel l17=new JLabel("������ֵ(cd/m2):");
	 JLabel l18=new JLabel("������ֵ(cd/m2):");
	 JTextField T8=new JTextField();
	 JTextField T9=new JTextField();
	 
	 JLabel l19=new JLabel("�������ֵ(%):");
	 JLabel L20=new JLabel("�������ֵ(%):");
	 JTextField T10=new JTextField();
	 JTextField T11=new JTextField();
	 
	 JLabel l21=new JLabel("������̼���ֵ(%):");
	 JLabel l22=new JLabel("������̼���ֵ(%):");
	 JTextField T12=new JTextField();
	 JTextField T13=new JTextField();
	 
	 JLabel l23=new JLabel("�������ֵ(%):");
	 JLabel l24=new JLabel("�������ֵ(%):");
	 JTextField T14=new JTextField();
	 JTextField T15=new JTextField();
	 
	 JLabel l25=new JLabel("��ѹ���ֵ(Pa):");
	 JLabel l26=new JLabel("��ѹ���ֵ(Pa):");
	 JTextField T16=new JTextField();
	 JTextField T17=new JTextField();
	 
	 JLabel l27=new JLabel("pm2.5���ֵ(��g/m3):");
	 JLabel l28=new JLabel("pm2.5���ֵ(��g/m3):");
	 JTextField T18=new JTextField();
	 JTextField T19=new JTextField();
	 
	
	public void setContent()
	{
		   startGame.setHorizontalTextPosition(SwingConstants.CENTER);
		    
		    getContentPane().setLayout(new BorderLayout());
		    getContentPane().add(startGame,BorderLayout.SOUTH);
		  

			setResizable(false);
			setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
			setTitle("SIM800���մ���");
			setBounds(450, 80, 600, 300);
			setVisible(true);
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		  startGame.setOpaque(false);  

		  startGame.setContentAreaFilled(false);  
		//ȥ���۽���
		  startGame.setFocusPainted(false);
		//ȥ���߿�
		  startGame.setBorder(null); 
		
		try {
			while(true)
		{
          startGame.setIcon(icon1);
          setContent();
		  Thread.sleep(200);
          startGame.setIcon(icon);
          setContent();
	      Thread.sleep(200);
		}
		}catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}  
		}
		
		
		}
		
 
		
	


