
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
	 byte[] buf =null; //存储套接字通道中读到的服务器端输出流的字符流  
	  //BufferedOutputStream b=null;
/*************发送区按钮变量设置******************************/	 
	 String wenduadd="?closf?";
	 String wendudown="?openf?";
	 
	 String shiduadd="shiduadd";
	 String shidudown="shidudown";
	 
	 String lianduadd="?openLsen?";
	 String liandudown="?closeLsen?";
	 
	 String auto="autom";
	 String man="manmm";
/*************发送区按钮变量设置******************************/
	 
	 
	 
	 
	 
	  
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
	JButton Sendbutton=new JButton("发送");
	
	
	JLabel l1=new JLabel("监听端口");
	JTextField T1=new JTextField("8080");
	JButton Attackbutton=new JButton("连接");
	JButton producebutton=new JButton("生成折线图");
	JButton produceAtivePhotobutton=new JButton("温度动态折线图");
	JButton produceAtivePhotobutton1=new JButton("湿度动态折线图");
	JButton produceAtivePhotobutton2=new JButton("亮度动态折线图");
	JButton produceAtivePhotobutton3=new JButton("PM值动态折线图");
	
	JButton produceAtivePhotobutton4=new JButton("O2值动态折线图");
	JButton produceAtivePhotobutton5=new JButton("CO2值动态折线图");
	JButton produceAtivePhotobutton6=new JButton("N2值动态折线图");
	JButton produceAtivePhotobutton7=new JButton("气压值动态折线图");
	
	 JPanel mainp13 =new JPanel(new GridLayout(16, 2));
	 
	 JLabel l13=new JLabel("                                         温度最高值(℃):");
	 JLabel l14=new JLabel("                                         温度最低值(℃):");
	 JTextField T4=new JTextField();
	 JTextField T5=new JTextField();
	 
	 JLabel l15=new JLabel("                                        湿度最高值(RH):");
	 JLabel l16=new JLabel("                                        湿度最低值(RH):");
	 JTextField T6=new JTextField();
	 JTextField T7=new JTextField();
	 
	 JLabel l17=new JLabel("                                    光度最高值(cd/m2):");
	 JLabel l18=new JLabel("                                    光度最低值(cd/m2):");
	 JTextField T8=new JTextField();
	 JTextField T9=new JTextField();
	 
	 JLabel l19=new JLabel("                                         氧气最高值(%):");
	 JLabel l20=new JLabel("                                         氧气最低值(%):");
	 JTextField T10=new JTextField();
	 JTextField T11=new JTextField();
	 
	 JLabel l21=new JLabel("                                    二氧化碳最高值(%):");
	 JLabel l22=new JLabel("                                    二氧化碳最低值(%):");
	 JTextField T12=new JTextField();
	 JTextField T13=new JTextField();
	 
	 JLabel l23=new JLabel("                                         氮气最高值(%):");
	 JLabel l24=new JLabel("                                         氮气最低值(%):");
	 JTextField T14=new JTextField();
	 JTextField T15=new JTextField();
	 
	 JLabel l25=new JLabel("                                        气压最高值(Pa):");
	 JLabel l26=new JLabel("                                        气压最低值(Pa):");
	 JTextField T16=new JTextField();
	 JTextField T17=new JTextField();
	 
	 JLabel l27=new JLabel("                                 pm2.5最高值(μg/m3):");
	 JLabel l28=new JLabel("                                 pm2.5最低值(μg/m3):");
	 JTextField T18=new JTextField();
	 JTextField T19=new JTextField();
	 
	 
	 
	 JButton startGame = new JButton("温度正常");
	 JButton startGame1 = new JButton("湿度正常");
	 JButton startGame2 = new JButton("光度正常");
	 JButton startGame3 = new JButton("氧气正常");
	 JButton startGame4 = new JButton("CO2正常");
	 JButton startGame5 = new JButton("氮气正常");
	 JButton startGame6 = new JButton("气压正常");
	 JButton startGame7 = new JButton("PM值正常");
	 
	 JButton startGame8 = new JButton("升温");
	 JButton startGame9 = new JButton("增高湿度");
	 JButton startGame10 = new JButton("增加亮度");
	 JButton startGame11= new JButton("发送");
	 JButton startGame12= new JButton("降温");
	 JButton startGame13= new JButton("降低湿度");
	 JButton startGame14= new JButton("降低亮度");
	 JButton startGame15= new JButton("发送");
	 
	 JButton startGame16= new JButton("自动");
	 JLabel l29=new JLabel("控制模式");
	 
	 
	 
	 
	 
	 
	 JLabel l4=new JLabel("     ");
	
	JLabel l5=new JLabel("     ");
	JLabel l7=new JLabel("     ");
	
	JLabel l6=new JLabel("接收窗口：");
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
		  jta.setFont(new Font("标楷体", Font.BOLD, 16));
		  jta.setLineWrap(true);// 激活自动换行功能
		  jta.setWrapStyleWord(true);// 激活断行不断字功能
		  jta.setBackground(Color.white);
		  
		  //startGame.setOpaque(false);  

		 // startGame.setContentAreaFilled(false);  
		//去掉聚焦线
		  //startGame.setFocusPainted(false);
		//去掉边框
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
               jta.updateUI();//利用当前外观的值重置 UI 属性。 也可以保证滚动条随时的更新
         
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
		startGame8 .setFont(new java.awt.Font("宋体", 1, 19));
		startGame9.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame9 .setFont(new java.awt.Font("宋体", 1, 19));
		startGame10.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame10 .setFont(new java.awt.Font("宋体", 1, 19));
		startGame11.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame11 .setFont(new java.awt.Font("宋体", 1, 19));
		startGame12.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame12 .setFont(new java.awt.Font("宋体", 1, 19));
		startGame13.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame13 .setFont(new java.awt.Font("宋体", 1, 19));
		
		startGame14.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame14 .setFont(new java.awt.Font("宋体", 1, 19));
		
		startGame15.setBorder(BorderFactory.createRaisedBevelBorder());
		startGame15 .setFont(new java.awt.Font("宋体", 1, 19));
		
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
		
		  tp.addTab( "接收窗口", jsp );
		  tp.addTab( "阀值设置窗口", mainp13 );
		
		
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
		
		setTitle("SIM800接收窗口test");
		setBounds(450, 80, 680, 600);
		setVisible(true);
		
		
    }
	
	public void addBorder()
	{
		Thread t1=new Thread(){ 
			public void run()
			{
			try{
			Border border=BorderFactory.createEtchedBorder(Color.BLACK,Color.BLACK); //以上是创建边框  createEtchedBorder创建凹凸边框 Color.BLACK,Color.BLUE阴影颜色    //边框标题  
	    Border title=BorderFactory.createTitledBorder(border,"警示窗口",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("黑体",Font.ITALIC, 16),Color.RED);
	
		Border title1=BorderFactory.createTitledBorder(border,"操作窗口",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("黑体",Font.ITALIC, 16),Color.RED);
		
		Border title2=BorderFactory.createTitledBorder(border,"接收窗口",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("黑体",Font.ITALIC, 16),Color.RED);
		Border title3=BorderFactory.createTitledBorder(border,"发送窗口",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("黑体",Font.ITALIC, 16),Color.RED);
		Border title4=BorderFactory.createTitledBorder(border,"设阀值窗口",TitledBorder.LEFT,
	    		TitledBorder.TOP,new Font("黑体",Font.ITALIC, 16),Color.RED);
		
		
	    
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
						  startGame.setText("温度超"+String.valueOf(f-fh)+"℃");
						  //o.write("wendutaigao".getBytes());
					  }else
						  if(f<fd)
					  {
						  startGame.setText("温度低"+String.valueOf(fd-f)+"℃");
						  //o.write("wendutaidi".getBytes());
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame.setText("温度正常");
						  }
			 startGame.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(200);
	          //startGame.setText("温度");
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
						  startGame1.setText("湿度超"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame1.setText("湿度低"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame1.setText("湿度正常");
							  startGame1.setBackground(Color.white);
						  }
			 startGame1.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(300);
	          //startGame.setText("温度");
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
						  startGame2.setText("光度超"+String.valueOf(f-fh)+"cd/m2");
					  }else
						  if(f<fd)
					  {
						  startGame2.setText("光度低"+String.valueOf(fd-f)+"cd/m2");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame2.setText("光度正常");
							  startGame2.setBackground(Color.white);
						  }
			 startGame2.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(350);
	          //startGame.setText("温度");
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
						  startGame3.setText("氧气超"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame3.setText("氧气低"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame3.setText("光度正常");
							  startGame3.setBackground(Color.white);
						  }
			 startGame3.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(390);
	          //startGame.setText("温度");
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
						  startGame4.setText("CO2超"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame4.setText("CO2低"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame4.setText("CO2正常");
							  startGame4.setBackground(Color.white);
						  }
			 startGame4.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(100);
	          //startGame.setText("温度");
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
						  startGame5.setText("N2超"+String.valueOf(f-fh)+"%");
					  }else
						  if(f<fd)
					  {
						  startGame5.setText("N2低"+String.valueOf(fd-f)+"%");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame5.setText("N2正常");
							  startGame5.setBackground(Color.white);
						  }
			 startGame5.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(400);
	          //startGame.setText("温度");
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
						  startGame6.setText("气压超"+String.valueOf(f-fh)+"Pa");
					  }else
						  if(f<fd)
					  {
						  startGame6.setText("气压低"+String.valueOf(fd-f)+"Pa");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame6.setText("气压正常");
							  startGame6.setBackground(Color.white);
						  }
			 startGame6.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(400);
	          //startGame.setText("温度");
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
						  startGame7.setText("PM超"+String.valueOf(f-fh)+"μg/m3");
					  }else
						  if(f<fd)
					  {
						  startGame7.setText("PM低"+String.valueOf(fd-f)+"μg/m3");
					  }else 
						  if(fd<=f&&f<=fh)
						  {
							  startGame7.setText("PM正常");
							  startGame7.setBackground(Color.white);
						  }
			 startGame7.setBackground(Color.WHITE);
					//startGame.setText("警示");
	          Thread.sleep(400);
	          //startGame.setText("温度");
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

//自动按钮

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
        standardChartTheme.setExtraLargeFont(new Font("微软雅黑", Font.BOLD, 20));  
        standardChartTheme.setRegularFont(new Font("微软雅黑", Font.PLAIN, 15));  
        standardChartTheme.setLargeFont(new Font("微软雅黑", Font.PLAIN, 15));  
        ChartFactory.setChartTheme(standardChartTheme);  
        
        JDialog d=new JDialog();
        RealTimeChartTest21 realTimeChart = new RealTimeChartTest21("温度变化曲线", "温度变化图", "温度值(℃)"); 
       // RealTimeChart realTimeChart = new RealTimeChart("随机数折线图", "随机数", "数值");  
        d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
        d.pack();  
        d.setBounds(0, 350, 600, 400);
        d.setVisible(true);
        d.setTitle("温度测试1");
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
       standardChartTheme.setExtraLargeFont(new Font("微软雅黑", Font.BOLD, 20));  
       standardChartTheme.setRegularFont(new Font("微软雅黑", Font.PLAIN, 15));  
       standardChartTheme.setLargeFont(new Font("微软雅黑", Font.PLAIN, 15));  
       ChartFactory.setChartTheme(standardChartTheme);  
       
       JDialog d=new JDialog();
       RealTimeChartTest22 realTimeChart = new RealTimeChartTest22("湿度变化曲线", "湿度变化图", "湿度值(%)"); 
      // RealTimeChart realTimeChart = new RealTimeChart("随机数折线图", "随机数", "数值");  
       d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
       d.pack();  
       d.setBounds(0, 350, 600, 400);
       d.setVisible(true);
       d.setTitle("温度测试1");
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
       standardChartTheme.setExtraLargeFont(new Font("微软雅黑", Font.BOLD, 20));  
       standardChartTheme.setRegularFont(new Font("微软雅黑", Font.PLAIN, 15));  
       standardChartTheme.setLargeFont(new Font("微软雅黑", Font.PLAIN, 15));  
       ChartFactory.setChartTheme(standardChartTheme);  
       
       JDialog d=new JDialog();
       RealTimeChartTest23 realTimeChart = new RealTimeChartTest23("亮度变化曲线", "亮度变化图", "亮度值(%)"); 
      // RealTimeChart realTimeChart = new RealTimeChart("随机数折线图", "随机数", "数值");  
       d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
       d.pack();  
       d.setBounds(0, 350, 600, 400);
       d.setVisible(true);
       d.setTitle("温度测试1");
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
       standardChartTheme.setExtraLargeFont(new Font("微软雅黑", Font.BOLD, 20));  
       standardChartTheme.setRegularFont(new Font("微软雅黑", Font.PLAIN, 15));  
       standardChartTheme.setLargeFont(new Font("微软雅黑", Font.PLAIN, 15));  
       ChartFactory.setChartTheme(standardChartTheme);  
       
       JDialog d=new JDialog();
       RealTimeChartTest24 realTimeChart = new RealTimeChartTest24("PM值变化曲线", "PM值变化图", "PM值(μg/m3)"); 
      // RealTimeChart realTimeChart = new RealTimeChart("随机数折线图", "随机数", "数值");  
       d.getContentPane().add(realTimeChart, new BorderLayout().CENTER);  
       d.pack();  
       d.setBounds(0, 350, 600, 400);
       d.setVisible(true);
       d.setTitle("温度测试1");
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
			if(file.exists()){//存在
				FileWriter fw = new FileWriter(file);//文件写IO
				fw.write(str);
				fw.flush();
				fw.close();
			}else{
				file.createNewFile();//不存在直接创建
				FileWriter fw = new FileWriter(file);//文件写IO
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
			BufferedReader br = new BufferedReader(fr);//文件读IO
			while((temp = br.readLine())!=null){//读到结束为止
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
			  if(Attackbutton.getText()=="连接")
			  {   
				  Attackbutton.setText("断开");
				 
				  
				  
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
						            
						             
						              o= client.getOutputStream();//服务器端打开自己的输出流  
						              //b= new BufferedOutputStream(o);//使用带缓存的输出流  
						   
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
												     startGame.setText("温度正常");
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
												     startGame1.setText("湿度正常");
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
												     startGame2.setText("光度正常");
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
									     startGame3.setText("氧气正常");
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
								     startGame4.setText("CO2正常");
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
								     startGame5.setText("N2正常");
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
								     startGame6.setText("气压正常");
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
								     startGame7.setText("PM值正常");
								   }};break;
											   
									
										  
							  }
						      
							  
									 
						
	                             //  DataBase1(s1,s2,s3);//数据存储
				     
				          jta.append(ss);
				          jsb = jsp.getVerticalScrollBar();
			               jta.updateUI();//利用当前外观的值重置 UI 属性。 也可以保证滚动条随时的更新
			         
			            jsp.getViewport().setViewPosition(new Point(0, jsp.getVerticalScrollBar().getMaximum()));
				         // System.out.println(new String(buf,0,len));//客户端--》服务器 。new String(buf,0,len)是将字符数组buf从下标零到len的每个字符构成一个字符串
			            
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
				  if(Attackbutton.getText()=="断开")
				  {   f=false;
					  Attackbutton.setText("连接");
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
					
					 if(startGame16.getText()=="自动")
					 {  String s='?'+auto+'?'+T4.getText()+'?'+T5.getText()+'?'+T6.getText()+'?'+T7.getText()+'?'+T8.getText()+'?'+T9.getText()+'?';
						 o.write(s.getBytes());
						 
						
		                // BT8.setflag(true);
    		           
						 
						 startGame16.setText("手动");
						 l29.setText("当前控制模式为自动模式，该模式将为自动控制下位机达到各个条件情况正常为止");
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
						 if(startGame16.getText()=="手动")
						 {  
							 String s='?'+man+'?';
							 
							 o.write(s.getBytes());
							 
							
			                //BT8.setflag(false);
	    		            
							 
							 startGame16.setText("自动");
							 l29.setText("当前控制模式为手动模式，该模式将由客户控制按钮来达到正常");
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
					 
					 if (e.getSource() ==startGame8)//升温按钮
						
							 {
						  
						 
							o.write(wenduadd.getBytes());
						
						 }else
							 if (e.getSource() ==startGame12) //降温按钮
							 {
								  
								 
									o.write(wendudown.getBytes());
								
								 }else 
									 
					       if (e.getSource() ==startGame9) //增高湿度按钮
					       {
									  
									 
					    	   o.write(T5.getText().getBytes());
									
									 }
					       else 
								 
						       if (e.getSource() ==startGame13) //降低湿度按钮
						       {
										  
										 
											o.write(shidudown.getBytes());
										
										 }
						       else 
									 
							       if (e.getSource() ==startGame10)//增加亮度按钮
							       {
											  
											 
												o.write(lianduadd.getBytes());
											
											 }
							       else 
										 
								       if (e.getSource() ==startGame14) //降低亮度按钮
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
				String user = "sa";// 这里替换成你自已的数据库用户名
				String password = "sa";// 这里替换成你自已的数据库用户密码
				
				Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
				Connection con = DriverManager.getConnection(url,user,password);
				
					PreparedStatement st = con.prepareStatement("INSERT INTO tem(wendu,shijian,wenduvalue) VALUES(?,?,?);"); 
				     st.setString(1,s1);  //替换sql语句中的第一个“？”
				     st.setString(2, s2); //替换sql语句中的第二个“？”
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

