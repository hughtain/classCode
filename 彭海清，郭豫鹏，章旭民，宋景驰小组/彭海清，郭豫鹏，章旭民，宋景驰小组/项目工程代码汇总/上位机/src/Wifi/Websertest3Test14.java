
package Wifi;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.StandardChartTheme;
import org.jfree.data.time.TimeSeries;




public class Websertest3Test14 extends JFrame implements ActionListener{
	
	  boolean f;
	  boolean Controlflag;
	  ServerSocket server=null;
	  Socket client=null;
	  InputStream i=null;
	  OutputStream o=null;
	 byte[] buf =null; //�洢�׽���ͨ���ж����ķ���������������ַ���  
	  //BufferedOutputStream b=null;
/*************��������ť��������******************************/	 
	 String wenduadd="?closf?";
	 String wendudown="?openf?";
	 
	 String shiduadd="shiduadd";
	 String shidudown="shidudown";
	 
	 String lianduadd="?openLsen?";
	 String liandudown="?closeLsen?";
	 
	 String auto="autom";
	 String man="manmm";
/*************��������ť��������******************************/
	 
	 
	 
	 
	 
	  
	  private static final long serialVersionUID = 1L;  
	    private static TimeSeries timeSeries;  
	    JTabbedPane tp = new JTabbedPane();
	
	JPanel mainp1 =new JPanel(new BorderLayout());
	JPanel mainp2 =new JPanel(new BorderLayout());
	JPanel mainp3= new JPanel(new BorderLayout());
	JPanel mainp111 =new JPanel(new GridLayout(3, 1));
	JPanel mainp11 =new JPanel(new GridLayout(11, 1));
	JPanel mainp12 =new JPanel(new BorderLayout());
	JPanel mainp21 =new JPanel(new BorderLayout());
	
	
	JPanel second1 =new JPanel(new BorderLayout());
	JPanel second11 =new JPanel(new BorderLayout());
	
	JPanel second13 =new JPanel(new GridLayout(2, 4));
	
	
	
	
	
	JPanel second12 =new JPanel(new GridLayout(2, 4));
	JLabel l8=new JLabel("     ");
	JTextField T2=new JTextField(      );
	JButton Sendbutton=new JButton("����");
	
	
	JLabel l1=new JLabel("�����˿�");
	JTextField T1=new JTextField("8080");
	JButton Attackbutton=new JButton("����");
	JButton producebutton=new JButton("��������ͼ");
	JButton produceAtivePhotobutton=new JButton("�¶ȶ�̬����ͼ");
	JButton produceAtivePhotobutton1=new JButton("ʪ�ȶ�̬����ͼ");
	JButton produceAtivePhotobutton2=new JButton("���ȶ�̬����ͼ");
	JButton produceAtivePhotobutton3=new JButton("PMֵ��̬����ͼ");
	
	JButton produceAtivePhotobutton4=new JButton("O2ֵ��̬����ͼ");
	JButton produceAtivePhotobutton5=new JButton("CO2ֵ��̬����ͼ");
	JButton produceAtivePhotobutton6=new JButton("N2ֵ��̬����ͼ");
	JButton produceAtivePhotobutton7=new JButton("��ѹֵ��̬����ͼ");
	
	 JPanel mainp13 =new JPanel(new GridLayout(16, 2));
	 
	 JLabel l13=new JLabel("                                         �¶����ֵ(��):");
	 JLabel l14=new JLabel("                                         �¶����ֵ(��):");
	 JTextField T4=new JTextField();
	 JTextField T5=new JTextField();
	 
	 JLabel l15=new JLabel("                                        ʪ�����ֵ(RH):");
	 JLabel l16=new JLabel("                                        ʪ�����ֵ(RH):");
	 JTextField T6=new JTextField();
	 JTextField T7=new JTextField();
	 
	 JLabel l17=new JLabel("                                    ������ֵ(cd/m2):");
	 JLabel l18=new JLabel("                                    ������ֵ(cd/m2):");
	 JTextField T8=new JTextField();
	 JTextField T9=new JTextField();
	 
	 JLabel l19=new JLabel("                                         �������ֵ(%):");
	 JLabel l20=new JLabel("                                         �������ֵ(%):");
	 JTextField T10=new JTextField();
	 JTextField T11=new JTextField();
	 
	 JLabel l21=new JLabel("                                    ������̼���ֵ(%):");
	 JLabel l22=new JLabel("                                    ������̼���ֵ(%):");
	 JTextField T12=new JTextField();
	 JTextField T13=new JTextField();
	 
	 JLabel l23=new JLabel("                                         �������ֵ(%):");
	 JLabel l24=new JLabel("                                         �������ֵ(%):");
	 JTextField T14=new JTextField();
	 JTextField T15=new JTextField();
	 
	 JLabel l25=new JLabel("                                        ��ѹ���ֵ(Pa):");
	 JLabel l26=new JLabel("                                        ��ѹ���ֵ(Pa):");
	 JTextField T16=new JTextField();
	 JTextField T17=new JTextField();
	 
	 JLabel l27=new JLabel("                                 pm2.5���ֵ(��g/m3):");
	 JLabel l28=new JLabel("                                 pm2.5���ֵ(��g/m3):");
	 JTextField T18=new JTextField();
	 JTextField T19=new JTextField();
	 
	 
	 
	 JButton startGame = new JButton("�¶�����");
	 JButton startGame1 = new JButton("ʪ������");
	 JButton startGame2 = new JButton("�������");
	 JButton startGame3 = new JButton("��������");
	 JButton startGame4 = new JButton("CO2����");
	 JButton startGame5 = new JButton("��������");
	 JButton startGame6 = new JButton("��ѹ����");
	 JButton startGame7 = new JButton("PMֵ����");
	 
	 JButton startGame8 = new JButton("����");
	 JButton startGame9 = new JButton("����ʪ��");
	 JButton startGame10 = new JButton("��������");
	 JButton startGame11= new JButton("����");
	 JButton startGame12= new JButton("����");
	 JButton startGame13= new JButton("����ʪ��");
	 JButton startGame14= new JButton("��������");
	 JButton startGame15= new JButton("����");
	 
	 JButton startGame16= new JButton("�Զ�");
	 JLabel l29=new JLabel("����ģʽ");
	 
	 
	 
	 
	 
	 
	 JLabel l4=new JLabel("     ");
	
	JLabel l5=new JLabel("     ");
	JLabel l7=new JLabel("     ");
	
	JLabel l6=new JLabel("���մ��ڣ�");
	JLabel l11=new JLabel("       ");
	JLabel l9=new JLabel("       ");
	JLabel l10=new JLabel("       ");
	JTextField accept=new JTextField();
	
	JTextArea jta = null;
	 JScrollPane jsp=new JScrollPane();
	 JScrollBar jsb=null;
	
	
	
	public  Websertest3Test14()
	{
		
		  jta = new JTextArea(10, 15);
		  jta.setTabSize(4);
		  jta.setFont(new Font("�꿬��", Font.BOLD, 16));
		  jta.setLineWrap(true);// �����Զ����й���
		  jta.setWrapStyleWord(true);// ������в����ֹ���
		  jta.setBackground(Color.white);
		  
		  //startGame.setOpaque(false);  

		 // startGame.setContentAreaFilled(false);  
		//ȥ���۽���
		  //startGame.setFocusPainted(false);
		//ȥ���߿�
		 // startGame.setBorder(null); 
		 // startGame.setIcon(icon1);
		  startGame.setBackground(Color.WHITE);
		  startGame1.setBackground(Color.WHITE);
		  startGame2.setBackground(Color.WHITE);
		  startGame3.setBackground(Color.WHITE);
		  
		  startGame4.setBackground(Color.WHITE);
		  startGame5.setBackground(Color.WHITE);
		  startGame6.setBackground(Color.WHITE);
		  startGame7.setBackground(Color.WHITE);
		  
		  T4.setText("31");
		  T5.setText("30");
		 
		  T6.setText("80");
		  T7.setText("30");
		 
		  T8.setText("80");
		  T9.setText("30");
		 
		  T10.setText("80");
		  T11.setText("30");
		 
		  T12.setText("80");
		  T13.setText("30");
		 
		  T14.setText("80");
		  T15.setText("30");
		 
		  T16.setText("80");
		  T17.setText("30");
		 
		  T18.setText("80");
		  T19.setText("30");

		mainp111.add(l1);
		mainp111.add(T1);
		mainp111.add(Attackbutton);
		mainp11.add(producebutton);
	    mainp11.add(produceAtivePhotobutton);
	    mainp11.add(produceAtivePhotobutton1);
	    mainp11.add(produceAtivePhotobutton2);
	    mainp11.add(produceAtivePhotobutton3);
		mainp11.add(produceAtivePhotobutton4);
		mainp11.add(produceAtivePhotobutton5);
		mainp11.add(produceAtivePhotobutton6);
		mainp11.add(produceAtivePhotobutton7);
		
		mainp11.add(l7);
		mainp3.add(mainp111,BorderLayout.NORTH);
		mainp3.add(mainp11,BorderLayout.CENTER);
		jsp.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
                jsp = new JScrollPane(jta);
            jsb = jsp.getVerticalScrollBar();
               jta.updateUI();//���õ�ǰ��۵�ֵ���� UI ���ԡ� Ҳ���Ա�֤��������ʱ�ĸ���
         
            jsp.getViewport().setViewPosition(new Point(0, jsp.getVerticalScrollBar().getMaximum()));
	     
	   
		Attackbutton.addActionListener(this);
		Sendbutton.addActionListener(this);
		producebutton.addActionListener(this);
	    produceAtivePhotobutton.addActionListener(this);
	    produceAtivePhotobutton1.addActionListener(this);
	    produceAtivePhotobutton2.addActionListener(this);
	    produceAtivePhotobutton3.addActionListener(this);
	    startGame16.addActionListener(this);
	    
	    startGame8.addActionListener(this);
	    startGame9.addActionListener(this);
	    startGame10.addActionListener(this);
	    startGame11.addActionListener(this);
	    startGame12.addActionListener(this);
	    startGame13.addActionListener(this);
	    startGame14.addActionListener(this);
	    startGame15.addActionListener(this);
	    

		second11.add(T2,BorderLayout.CENTER);
		second11.add(Sendbutton,BorderLayout.EAST);
		second11.add(l29,BorderLayout.NORTH);
		second11.add(startGame16,BorderLayout.WEST);
		second12.add(startGame);
		second12.add(startGame1);
		second12.add(startGame2);
		second12.add(startGame3);
		second12.add(startGame4);
		second12.add(startGame5);
		second12.add(startGame6);
		second12.add(startGame7);
		
		
	
		startGame8.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame8 .setFont(new java.awt.Font("����", 1, 19));
		startGame9.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame9 .setFont(new java.awt.Font("����", 1, 19));
		startGame10.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame10 .setFont(new java.awt.Font("����", 1, 19));
		startGame11.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame11 .setFont(new java.awt.Font("����", 1, 19));
		startGame12.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame12 .setFont(new java.awt.Font("����", 1, 19));
		startGame13.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame13 .setFont(new java.awt.Font("����", 1, 19));
		
		startGame14.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame14 .setFont(new java.awt.Font("����", 1, 19));
		
		startGame15.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame15 .setFont(new java.awt.Font("����", 1, 19));
		
		startGame9.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame10.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame11.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame12.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame13.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame14.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame15.setBorder(BorderFactory.createRaisedBevelBorder());
		
		second13.add(startGame8);
		second13.add(startGame9);
		second13.add(startGame10);
		second13.add(startGame11);
		
		second13.add(startGame12);
		second13.add(startGame13);
		second13.add(startGame14);
		second13.add(startGame15);
		
		mainp13.add(l13);
		mainp13.add(T4);
		mainp13.add(l14);
		mainp13.add(T5);
		
		
		
		mainp13.add(l15);
		mainp13.add(T6);
		mainp13.add(l16);
		mainp13.add(T7);
		
		mainp13.add(l17);
		mainp13.add(T8);
		mainp13.add(l18);
		mainp13.add(T9);
		
		mainp13.add(l19);
		mainp13.add(T10);
		mainp13.add(l20);
		mainp13.add(T11);
		
		
		mainp13.add(l21);
		mainp13.add(T12);
		mainp13.add(l22);
		mainp13.add(T13);
		
		mainp13.add(l23);
		mainp13.add(T14);
		mainp13.add(l24);
		mainp13.add(T15);
		
		
		mainp13.add(l25);
		mainp13.add(T16);
		mainp13.add(l26);
		mainp13.add(T17);
		

		mainp13.add(l27);
		mainp13.add(T18);
		mainp13.add(l28);
		mainp13.add(T19);
		
		
		
		addBorder();
		
		second1.add(second11,BorderLayout.NORTH);
		second1.add(second13,BorderLayout.CENTER);
		
		  tp.addTab( "���մ���", jsp );
		  tp.addTab( "��ֵ���ô���", mainp13 );
		
		
		mainp12.add(second12, BorderLayout.NORTH);
		mainp12.add(tp, BorderLayout.CENTER);
		mainp12.add(second1, BorderLayout.SOUTH);
		
		//mainp11.setBackground(Color.gray);
		//second12.setBackground(Color.gray);
		
		mainp1.add(mainp3, BorderLayout.WEST);
		mainp1.add(mainp12, BorderLayout.CENTER);
		//mainp1.add(mainp13, BorderLayout.EAST);
	
		getContentPane().add(mainp1);
		
		setResizable(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setTitle("SIM800���մ���test");
		setBounds(450, 80, 680, 600);
		setVisible(true);
		
		
    }
	
	public void addBorder()
	{
		Thread t1=new Thread(){ 
			public void run()
			{
			try{
			Border border=BorderFactory.createEtchedBorder(Color.BLACK,Color.BLACK); //�����Ǵ����߿�  createEtchedBorder������͹�߿� Color.BLACK,Color.BLUE��Ӱ��ɫ    //�߿����  
	    Border title=BorderFactory.createTitledBorder(border,"��ʾ����",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("����",Font.ITALIC, 16),Color.RED);
	
		Border title1=BorderFactory.createTitledBorder(border,"��������",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("����",Font.ITALIC, 16),Color.RED);
		
		Border title2=BorderFactory.createTitledBorder(border,"���մ���",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("����",Font.ITALIC, 16),Color.RED);
		Border title3=BorderFactory.createTitledBorder(border,"���ʹ���",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("����",Font.ITALIC, 16),Color.RED);
		Border title4=BorderFactory.createTitledBorder(border,"�跧ֵ����",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("����",Font.ITALIC, 16),Color.RED);
		
		
	    
	  second12.setBorder(title);
	  mainp11.setBorder(title1);
	 
	  second1.setBorder(title3);
	
		
			}catch(Exception  e)
			{
				System.out.println(e.getMessage());
			}
			}
		
		};
		t1.start();
		
	}
	class buttonChange implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{       
					
					Float f = (float) 0;
					 Float fh= (float) 0;
					  Float fd= (float) 0;
					String s=readFile("wendu");
					if(s!="")
					{
					  f=Float.valueOf(s);
					 
					}
					 
					  if((T4.getText().length()!=0&&T5.getText().length()!=0))
					  {
						  fh=Float.valueOf(T4.getText());
		 		             fd=Float.valueOf(T5.getText());
					  }
					  else
					  {
						  fh=(float) 31;
	 		            	 fd=(float) 30;
					  }
					
					  if(f>fh)
					  {
						  startGame.setText("�¶ȳ�"+String.valueOf(f-fh)+"��");
						  //o.write("wendutaigao".getBytes());
					  }else
						  if(f<fd)
					  {
						  startGame.setText("�¶ȵ�"+String.valueOf(fd-f)+"��");
						  //o.write("wendutaidi".getBytes());
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame.setText("�¶�����");
						  }
			 startGame.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(200);
	          //startGame.setText("�¶�");
               startGame.setBackground(Color.RED);
		      Thread.sleep(200);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						//Thread.currentThread().interrupt();
					} 
	    	 }
			
		}
	class buttonChange1 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					Float f=(float)0;
					 Float fh=(float)0;
					  Float fd=(float)0;
					String s=readFile("shidu");
					 
					  if(s!="")
						{
						  f=Float.valueOf(s);
						 
						}
				
					 
					 
					  if((T6.getText().length()!=0&&T7.getText().length()!=0))
					  {
						  fh=Float.valueOf(T6.getText());
		 		             fd=Float.valueOf(T7.getText());
					  }
					
					  if(f>fh)
					  {
						  startGame1.setText("ʪ�ȳ�"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame1.setText("ʪ�ȵ�"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame1.setText("ʪ������");
							  startGame1.setBackground(Color.white);
						  }
			 startGame1.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(300);
	          //startGame.setText("�¶�");
               startGame1.setBackground(Color.yellow);
		      Thread.sleep(320);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}
	class buttonChange2 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{        Float f=(float)0;
			        Float fh=(float)0;
			       Float fd=(float)0;
					String s=readFile("guadu");
					 
					  if(s!="")
						{
						  f=Float.valueOf(s);
						 
						}
					  if((T8.getText().length()!=0&&T9.getText().length()!=0))
					  {
						  fh=Float.valueOf(T8.getText());
		 		             fd=Float.valueOf(T9.getText());
					  }
					 
					 
					  if(f>fh)
					  {
						  startGame2.setText("��ȳ�"+String.valueOf(f-fh)+"cd/m2");
					  }else
						  if(f<fd)
					  {
						  startGame2.setText("��ȵ�"+String.valueOf(fd-f)+"cd/m2");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame2.setText("�������");
							  startGame2.setBackground(Color.white);
						  }
			 startGame2.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(350);
	          //startGame.setText("�¶�");
               startGame2.setBackground(Color.blue);
		      Thread.sleep(350);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}
	class buttonChange3 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					String s=readFile("yanqi");
					  Float f=Float.valueOf(s);
					  Float fh=Float.valueOf(T10.getText());
					  Float fd=Float.valueOf(T11.getText());
					  if(f>fh)
					  {
						  startGame3.setText("������"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame3.setText("������"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame3.setText("�������");
							  startGame3.setBackground(Color.white);
						  }
			 startGame3.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(390);
	          //startGame.setText("�¶�");
               startGame3.setBackground(Color.GREEN);
		      Thread.sleep(390);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}
	class buttonChange4 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					String s=readFile("eyhta");
					  Float f=Float.valueOf(s);
					  Float fh=Float.valueOf(T12.getText());
					  Float fd=Float.valueOf(T13.getText());
					  if(f>fh)
					  {
						  startGame4.setText("CO2��"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame4.setText("CO2��"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame4.setText("CO2����");
							  startGame4.setBackground(Color.white);
						  }
			 startGame4.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(100);
	          //startGame.setText("�¶�");
               startGame4.setBackground(Color.PINK);
		      Thread.sleep(400);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}
	class buttonChange5 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					String s=readFile("danqi");
					  Float f=Float.valueOf(s);
					  Float fh=Float.valueOf(T14.getText());
					  Float fd=Float.valueOf(T15.getText());
					  if(f>fh)
					  {
						  startGame5.setText("N2��"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame5.setText("N2��"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame5.setText("N2����");
							  startGame5.setBackground(Color.white);
						  }
			 startGame5.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(400);
	          //startGame.setText("�¶�");
               startGame5.setBackground(Color.CYAN);
		      Thread.sleep(500);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}

	class buttonChange6 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					String s=readFile("qiyaa");
					  Float f=Float.valueOf(s);
					  Float fh=Float.valueOf(T16.getText());
					  Float fd=Float.valueOf(T17.getText());
					  if(f>fh)
					  {
						  startGame6.setText("��ѹ��"+String.valueOf(f-fh)+"Pa");
					  }else
						  if(f<fd)
					  {
						  startGame6.setText("��ѹ��"+String.valueOf(fd-f)+"Pa");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame6.setText("��ѹ����");
							  startGame6.setBackground(Color.white);
						  }
			 startGame6.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(400);
	          //startGame.setText("�¶�");
               startGame6.setBackground(Color.MAGENTA);
		      Thread.sleep(370);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}
	class buttonChange7 implements Runnable
	{      private  boolean flag8;
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					String s=readFile("pmval");
					  Float f=Float.valueOf(s);
					  Float fh=Float.valueOf(T18.getText());
					  Float fd=Float.valueOf(T19.getText());
					  if(f>fh)
					  {
						  startGame7.setText("PM��"+String.valueOf(f-fh)+"��g/m3");
					  }else
						  if(f<fd)
					  {
						  startGame7.setText("PM��"+String.valueOf(fd-f)+"��g/m3");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame7.setText("PM����");
							  startGame7.setBackground(Color.white);
						  }
			 startGame7.setBackground(Color.WHITE);
					//startGame.setText("��ʾ");
	          Thread.sleep(400);
	          //startGame.setText("�¶�");
               startGame7.setBackground(Color.ORANGE);
		      Thread.sleep(300);
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} 
	    	 }
			
		}

//�Զ���ť

	class buttonChange8 implements Runnable
	{      private  boolean flag8;
	       String s1="?autom?";
//	volatile
	     public void setflag(boolean flag)
	     {
	    	 this.flag8=flag;
	     }
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				while(flag8)
			{ 
					 o.write(s1.getBytes());
	              Thread.sleep(4000);
	          
		    }
			}catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Thread.currentThread().interrupt();
					} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
	    	 }
			
		}
   public void activeChartLine()
    {Thread t2;
    	  
		 t2=new Thread(){ 
				public void run()
				{
					
        StandardChartTheme standardChartTheme = new StandardChartTheme("CN");  
        standardChartTheme.setExtraLargeFont(new Font("΢���ź�", Font.BOLD, 20));  
        standardChartTheme.setRegularFont(new Font("΢���ź�", Font.PLAIN, 15));  
        standardChartTheme.setLargeFont(new Font("΢���ź�", Font.PLAIN, 15));  
        ChartFactory.setChartTheme(standardChartTheme);  
        
        JDialog d=new JDialog();
        RealTimeChartTest21 realTimeChart = new RealTimeChartTest21("�¶ȱ仯����", "�¶ȱ仯ͼ", "�¶�ֵ(��)"); 
       // RealTimeChart realTimeChart = new RealTimeChart("���������ͼ", "�����", "��ֵ");  
        d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
        d.pack();  
        d.setBounds(0, 350, 600, 400);
        d.setVisible(true);
        d.setTitle("�¶Ȳ���1");
        (new Thread(realTimeChart)).start();  
					
				}
				
			};
			t2.start();
    	
    }
   public void activeChartLine1()
   {Thread t2;
   	  
		 t2=new Thread(){ 
				public void run()
				{
					
       StandardChartTheme standardChartTheme = new StandardChartTheme("CN");  
       standardChartTheme.setExtraLargeFont(new Font("΢���ź�", Font.BOLD, 20));  
       standardChartTheme.setRegularFont(new Font("΢���ź�", Font.PLAIN, 15));  
       standardChartTheme.setLargeFont(new Font("΢���ź�", Font.PLAIN, 15));  
       ChartFactory.setChartTheme(standardChartTheme);  
       
       JDialog d=new JDialog();
       RealTimeChartTest22 realTimeChart = new RealTimeChartTest22("ʪ�ȱ仯����", "ʪ�ȱ仯ͼ", "ʪ��ֵ(%)"); 
      // RealTimeChart realTimeChart = new RealTimeChart("���������ͼ", "�����", "��ֵ");  
       d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
       d.pack();  
       d.setBounds(0, 350, 600, 400);
       d.setVisible(true);
       d.setTitle("�¶Ȳ���1");
       (new Thread(realTimeChart)).start();  
					
				}
				
			};
			t2.start();
   	
   }
   public void activeChartLine2()
   {Thread t2;
   	  
		 t2=new Thread(){ 
				public void run()
				{
					
       StandardChartTheme standardChartTheme = new StandardChartTheme("CN");  
       standardChartTheme.setExtraLargeFont(new Font("΢���ź�", Font.BOLD, 20));  
       standardChartTheme.setRegularFont(new Font("΢���ź�", Font.PLAIN, 15));  
       standardChartTheme.setLargeFont(new Font("΢���ź�", Font.PLAIN, 15));  
       ChartFactory.setChartTheme(standardChartTheme);  
       
       JDialog d=new JDialog();
       RealTimeChartTest23 realTimeChart = new RealTimeChartTest23("���ȱ仯����", "���ȱ仯ͼ", "����ֵ(%)"); 
      // RealTimeChart realTimeChart = new RealTimeChart("���������ͼ", "�����", "��ֵ");  
       d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
       d.pack();  
       d.setBounds(0, 350, 600, 400);
       d.setVisible(true);
       d.setTitle("�¶Ȳ���1");
       (new Thread(realTimeChart)).start();  
					
				}
				
			};
			t2.start();
   	
   }
   public void activeChartLine3()
   {Thread t2;
   	  
		 t2=new Thread(){ 
				public void run()
				{
					
       StandardChartTheme standardChartTheme = new StandardChartTheme("CN");  
       standardChartTheme.setExtraLargeFont(new Font("΢���ź�", Font.BOLD, 20));  
       standardChartTheme.setRegularFont(new Font("΢���ź�", Font.PLAIN, 15));  
       standardChartTheme.setLargeFont(new Font("΢���ź�", Font.PLAIN, 15));  
       ChartFactory.setChartTheme(standardChartTheme);  
       
       JDialog d=new JDialog();
       RealTimeChartTest24 realTimeChart = new RealTimeChartTest24("PMֵ�仯����", "PMֵ�仯ͼ", "PMֵ(��g/m3)"); 
      // RealTimeChart realTimeChart = new RealTimeChart("���������ͼ", "�����", "��ֵ");  
       d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
       d.pack();  
       d.setBounds(0, 350, 600, 400);
       d.setVisible(true);
       d.setTitle("�¶Ȳ���1");
       (new Thread(realTimeChart)).start();  
					
				}
				
			};
			t2.start();
   	
   }
    static void writeFile(String str,String s) {
    	 String txt=null;
    	 switch(s)
    	 {case "wendu":txt=s+".txt";break;
    	  case "shidu":txt=s+".txt";break;
    	  case "guadu":txt=s+".txt";break;
    	  case "yanqi":txt=s+".txt";break;
    	  
    	  case "eyhta":txt=s+".txt";break;
    	  case "danqi":txt=s+".txt";break;
    	  case "qiyaa":txt=s+".txt";break;
    	  case "pmval":txt=s+".txt";break;
    	   
    	 }
    	 
		try {
			File file = new File("data\\"+txt);
			if(file.exists()){//����
				FileWriter fw = new FileWriter(file);//�ļ�дIO
				fw.write(str);
				fw.flush();
				fw.close();
			}else{
				file.createNewFile();//������ֱ�Ӵ���
				FileWriter fw = new FileWriter(file);//�ļ�дIO
				fw.write(str);
				fw.flush();
				fw.close();
			}
			
			
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
    static String readFile(String s) {
		String str = "", temp = null;
		String txt=null;
   	 switch(s)
   	 {case "wendu":txt=s+".txt";break;
   	  case "shidu":txt=s+".txt";break;
   	  case "guadu":txt=s+".txt";break;
   	  case "yanqi":txt=s+".txt";break;
   	  
   	  case "eyhta":txt=s+".txt";break;
   	  case "danqi":txt=s+".txt";break;
   	  case "qiyaa":txt=s+".txt";break;
   	  case "pmval":txt=s+".txt";break;
   	   
   	 }
		try {
			File file = new File("data\\"+txt);
			FileReader fr = new FileReader(file);
			BufferedReader br = new BufferedReader(fr);//�ļ���IO
			while((temp = br.readLine())!=null){//��������Ϊֹ
				str += (temp+"\n");
			}
			br.close();
			fr.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return str;
	} 
	@SuppressWarnings("null")
	public void actionPerformed(ActionEvent e) {
		
		buttonChange8   BT8=new buttonChange8();
		Thread th8;
		
		
		
		  if (e.getSource() == Attackbutton) {
			  if(Attackbutton.getText()=="����")
			  {   
				  Attackbutton.setText("�Ͽ�");
				 
				  
				  
				  Thread t1=new Thread(){ 
						@SuppressWarnings({ "deprecation", "static-access" })
					
						public void run()
						{
							buttonChange   BT0=new buttonChange();
							buttonChange1   BT1=new buttonChange1();
							buttonChange2   BT2=new buttonChange2();
							buttonChange3   BT3=new buttonChange3();
							buttonChange4   BT4=new buttonChange4();
							buttonChange5   BT5=new buttonChange5();
							buttonChange6   BT6=new buttonChange6();
							buttonChange7   BT7=new buttonChange7();
							
							Thread th0;
							Thread th1;
							Thread th2;
							Thread th3;
							Thread th4;
							Thread th5;
							Thread th6;
							Thread th7;
							
							 
					    	  try{  
					    		  int port =Integer.valueOf(T1.getText()).intValue();
					    	
					    		 
					    	  
							         server= new ServerSocket(port); 
							         
						             client = server.accept(); 
						            
						             
						              o= client.getOutputStream();//�������˴��Լ��������  
						              //b= new BufferedOutputStream(o);//ʹ�ô�����������  
						   
						     while(true)  
						      {   
						           i= client.getInputStream();
						           buf=new byte[100];
						        
						           int len = i.read(buf);
						           String ss=new String(buf,0,len);
						           
						           String s1=ss.substring(0, 5);
								   String s2=ss.substring(6, 11);
								   String s3=ss.substring(12, 15);
								
								   float b= Float.valueOf(s3);
								   
								   
								   
								  switch(s1)
								  {
								  case "wendu":{   writeFile(s3,"wendu");
									            th0=new Thread(BT0);
								                 BT0.setflag(true);
						    		             th0.start();
						    		             float fh=(float)0;
						    		             float fd=(float)0;;
						    		             if((T4.getText().length()!=0&&T5.getText().length()!=0))
						   					  {
						   						  fh=Float.valueOf(T4.getText());
						   		 		             fd=Float.valueOf(T5.getText());
						   					  }
						   					 
						    		             
												   if(b>fh||b<fd)
												   {
													   BT0.setflag(true);
												   }else
												   { 
												       BT0.setflag(false);
												     startGame.setBackground(Color.white);
												     startGame.setText("�¶�����");
												   }};break;
								  case "shidu":{   writeFile(s3,"shidu");
									            th1=new Thread(BT1);
								                 BT1.setflag(true);
						    		             th1.start();
						    		             float fh=(float)0;
						    		             float fd=(float)0;;
						    		             if((T6.getText().length()!=0&&T7.getText().length()!=0))
						   					  {
						   						  fh=Float.valueOf(T6.getText());
						   		 		             fd=Float.valueOf(T7.getText());
						   					  }
						    		             
						    		             
												   if(b>fh||b<fd)
												   {
													   BT1.setflag(true);
												   }else
												   { 
												     
												     startGame1.setBackground(Color.white);
												     startGame1.setText("ʪ������");
												     BT1.setflag(false);
												   }};break;
								  case "guadu":{   writeFile(s3,"guadu");
									            th2=new Thread(BT2);
								                 BT2.setflag(true);
						    		             th2.start();
						    		             float fh;
						    		             float fd;
						    		        
						    		            
						    		             fh=Float.valueOf(T8.getText());
						    		             fd=Float.valueOf(T9.getText());
						    		             
						    		             
												   if(b>fh||b<fd)
												   {
													   BT2.setflag(true);
												   }else
												   { 
												     
												     startGame2.setBackground(Color.white);
												     startGame2.setText("�������");
												     BT2.setflag(false);
												   }};break;
								  case "yanqi":{   writeFile(s3,"yanqi");
						            th3=new Thread(BT3);
					                 BT3.setflag(true);
			    		             th3.start();
			    		             float fh;
			    		             float fd;
			    		          
			    		            
			    		             fh=Float.valueOf(T10.getText());
			    		             fd=Float.valueOf(T11.getText());
			    		             
			    		             
									   if(b>fh||b<fd)
									   {
										   BT3.setflag(true);
									   }else
									   { 
									       BT3.setflag(false);
									     startGame3.setBackground(Color.white);
									     startGame3.setText("��������");
									   }};break;		   
												   
										
											  
								  
						      case "eyhta":{   writeFile(s3,"eyhta");
					            th4=new Thread(BT4);
				                 BT4.setflag(true);
		    		             th4.start();
		    		             float fh;
		    		             float fd;
		    		          
		    		            
		    		             fh=Float.valueOf(T12.getText());
		    		             fd=Float.valueOf(T13.getText());
		    		             
		    		             
								   if(b>fh||b<fd)
								   {
									   BT4.setflag(true);
								   }else
								   { 
								       BT4.setflag(false);
								     startGame4.setBackground(Color.white);
								     startGame4.setText("CO2����");
								   }};break;
						      case "danqi":{   writeFile(s3,"danqi");
					            th5=new Thread(BT5);
				                 BT5.setflag(true);
		    		             th5.start();
		    		             float fh;
		    		             float fd;
		    		          
		    		            
		    		             fh=Float.valueOf(T14.getText());
		    		             fd=Float.valueOf(T15.getText());
		    		             
		    		             
								   if(b>fh||b<fd)
								   {
									   BT5.setflag(true);
								   }else
								   { 
								       BT5.setflag(false);
								     startGame5.setBackground(Color.white);
								     startGame5.setText("N2����");
								   }};break;
						      case "qiyaa":{   writeFile(s3,"qiyaa");
					            th6=new Thread(BT6);
				                 BT6.setflag(true);
		    		             th6.start();
		    		             float fh;
		    		             float fd;
		    		          
		    		            
		    		             fh=Float.valueOf(T16.getText());
		    		             fd=Float.valueOf(T17.getText());
		    		             
		    		             
								   if(b>fh||b<fd)
								   {
									   BT6.setflag(true);
								   }else
								   { 
								       BT6.setflag(false);
								     startGame6.setBackground(Color.white);
								     startGame6.setText("��ѹ����");
								   }};break;
						      case "pmval":{   writeFile(s3,"pmval");
					            th7=new Thread(BT7);
				                 BT7.setflag(true);
		    		             th7.start();
		    		             float fh;
		    		             float fd;
		    		          
		    		            
		    		             fh=Float.valueOf(T18.getText());
		    		             fd=Float.valueOf(T19.getText());
		    		             
		    		             
								   if(b>fh||b<fd)
								   {
									   BT7.setflag(true);
								   }else
								   { 
								       BT7.setflag(false);
								     startGame7.setBackground(Color.white);
								     startGame7.setText("PMֵ����");
								   }};break;
											   
									
										  
							  }
						      
							  
									 
						
	                             //  DataBase1(s1,s2,s3);//���ݴ洢
				     
				          jta.append(ss);
				          jsb = jsp.getVerticalScrollBar();
			               jta.updateUI();//���õ�ǰ��۵�ֵ���� UI ���ԡ� Ҳ���Ա�֤��������ʱ�ĸ���
			         
			            jsp.getViewport().setViewPosition(new Point(0, jsp.getVerticalScrollBar().getMaximum()));
				         // System.out.println(new String(buf,0,len));//�ͻ���--�������� ��new String(buf,0,len)�ǽ��ַ�����buf���±��㵽len��ÿ���ַ�����һ���ַ���
			            
						      }
						} catch(Exception e1)
						  {
							  e1.printStackTrace();  
						  }
			            
				     }
				 };
				 
					t1.start();
					
			  }
		  
						else
				  if(Attackbutton.getText()=="�Ͽ�")
				  {   f=false;
					  Attackbutton.setText("����");
					 // t1.interrupt();
				  }
	}
				 
		 
					  else if (e.getSource() == Sendbutton) {
		  
		 
		 }else
			 if (e.getSource() ==producebutton) {
			  
			 new producephoto();
			 }
			 else
		 if (e.getSource() ==produceAtivePhotobutton) {
			  
			 activeChartLine();
			 } else
				 if (e.getSource() ==produceAtivePhotobutton1) {
					  
					 activeChartLine1();
					 }  
				 else
					 if (e.getSource() ==produceAtivePhotobutton2) {
						  
						 activeChartLine2();
						 }  
					 else
						 if (e.getSource() ==produceAtivePhotobutton3) {
							  
							 activeChartLine3();
							 }  
			 
		 else 
			 
			 try 
		  {
				 if (e.getSource() ==startGame16) {
					 //th8=new Thread(BT8);
					 //BT8.setflag(true);
					 //th8.start();
					
					 if(startGame16.getText()=="�Զ�")
					 {  String s='?'+auto+'?'+T4.getText()+'?'+T5.getText()+'?'+T6.getText()+'?'+T7.getText()+'?'+T8.getText()+'?'+T9.getText()+'?';
						 o.write(s.getBytes());
						 
						
		                // BT8.setflag(true);
    		           
						 
						 startGame16.setText("�ֶ�");
						 l29.setText("��ǰ����ģʽΪ�Զ�ģʽ����ģʽ��Ϊ�Զ�������λ���ﵽ���������������Ϊֹ");
						 Controlflag=true;
						 startGame8.setEnabled(false);
						 startGame9.setEnabled(false);
						 startGame10.setEnabled(false);
						 startGame11.setEnabled(false);
						 
						 startGame12.setEnabled(false);
						 startGame13.setEnabled(false);
						 startGame14.setEnabled(false);
						 startGame15.setEnabled(false);
						 
					 }else
						 if(startGame16.getText()=="�ֶ�")
						 {  
							 String s='?'+man+'?';
							 
							 o.write(s.getBytes());
							 
							
			                //BT8.setflag(false);
	    		            
							 
							 startGame16.setText("�Զ�");
							 l29.setText("��ǰ����ģʽΪ�ֶ�ģʽ����ģʽ���ɿͻ����ư�ť���ﵽ����");
							 Controlflag=false;
							 startGame8.setEnabled(true);
							 startGame9.setEnabled(true);
							 startGame10.setEnabled(true);
							 startGame11.setEnabled(true);
							 
							 startGame12.setEnabled(true);
							 startGame13.setEnabled(true);
							 startGame14.setEnabled(true);
							 startGame15.setEnabled(true);
						 }
					  
					
					} 
				 else
					 
					 if (e.getSource() ==startGame8)//���°�ť
						
							 {
						  
						 
							o.write(wenduadd.getBytes());
						
						 }else
							 if (e.getSource() ==startGame12) //���°�ť
							 {
								  
								 
									o.write(wendudown.getBytes());
								
								 }else 
									 
					       if (e.getSource() ==startGame9) //����ʪ�Ȱ�ť
					       {
									  
									 
					    	   o.write(T5.getText().getBytes());
									
									 }
					       else 
								 
						       if (e.getSource() ==startGame13) //����ʪ�Ȱ�ť
						       {
										  
										 
											o.write(shidudown.getBytes());
										
										 }
						       else 
									 
							       if (e.getSource() ==startGame10)//�������Ȱ�ť
							       {
											  
											 
												o.write(lianduadd.getBytes());
											
											 }
							       else 
										 
								       if (e.getSource() ==startGame14) //�������Ȱ�ť
								       {
												  
												 
													
														o.write(liandudown.getBytes());
													
													}
		  } catch(Exception e1)
		  {
			  e1.printStackTrace();  
		  }
								      
												
												 }
					 
	
		 
	
	public void DataBase1(String s1,String s2,String s3) 
	{ 
	  
		try
		{     
			 
				String url = "jdbc:sqlserver://localhost:1433;DatabaseName=ch1";
				String user = "sa";// �����滻�������ѵ����ݿ��û���
				String password = "sa";// �����滻�������ѵ����ݿ��û�����
				
				Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
				Connection con = DriverManager.getConnection(url,user,password);
				
					PreparedStatement st = con.prepareStatement("INSERT INTO tem(wendu,shijian,wenduvalue) VALUES(?,?,?);"); 
				     st.setString(1,s1);  //�滻sql����еĵ�һ��������
				     st.setString(2, s2); //�滻sql����еĵڶ���������
				     st.setString(3, s3);
				     st.executeUpdate();
				
			    
			     
			    
		}catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
		  
	
	public static void main(String[] args)
	{
		new Websertest3Test14();
	}
	
	
}

