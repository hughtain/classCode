package Wifi;

import java.awt.Font;
import java.awt.RenderingHints;
import java.io.FileOutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.jfree.chart.ChartColor;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartFrame;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.title.TextTitle;
import org.jfree.data.category.DefaultCategoryDataset;

public class producephoto {
	
	public producephoto()
	{
		 ResultSet s5= getDatebase7();
		 DefaultCategoryDataset dataset1 = new DefaultCategoryDataset();

		 
		 try {
					 while(s5.next())
		    {
			  dataset1.addValue(s5.getFloat(2), "�¶�",String.valueOf(s5.getTime(1) ));
			  //addValue(s5.getFloat(1), "�¶�",s5.getInt(2));
			
			} 
		    }
		 catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		JFreeChart chart = ChartFactory.createLineChart("�¶�ֵͼ ", "ʱ��", "�¶�",  
                dataset1, PlotOrientation.VERTICAL, true, true, true);  
  
        CategoryPlot cp = chart.getCategoryPlot();  
        cp.setBackgroundPaint(ChartColor.WHITE); // ����ɫ����  
        cp.setRangeGridlinePaint(ChartColor.GRAY); // ������ɫ����  
		
        processChart(chart);  
        
        // 4. chart���ͼƬ  
        writeChartAsImage(chart);  
  
        // 5. chart ��swing��ʽ���  
        ChartFrame pieFrame = new ChartFrame("XXX", chart);  
        pieFrame.pack();  
        pieFrame.setVisible(true);  
        pieFrame.setBounds(0, 0, 600, 400);
	}
	
	
	public ResultSet getDatebase7()
	 {     
		
		
	   
	    String  sqr="select shijian,value,riqi from tem1";
	
	    String url = "jdbc:sqlserver://localhost:1433;DatabaseName=ch1";
		String user = "sa";// �����滻�������ѵ����ݿ��û���
		String password = "sa";// �����滻�������ѵ����ݿ��û�����
		 ResultSet rs=null;
		  
		
		try{
			 Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		Connection con = DriverManager.getConnection(url,user,password);
	    PreparedStatement st = con.prepareStatement(sqr);
	   
	   rs=st.executeQuery();
		}catch( Exception e)
		{
			System.out.println(e.getMessage());
		}
		return rs;
	 }
	private static void processChart(JFreeChart chart) {  
        CategoryPlot plot = chart.getCategoryPlot();  
        CategoryAxis domainAxis = plot.getDomainAxis();  
        ValueAxis rAxis = plot.getRangeAxis();  
        chart.getRenderingHints().put(RenderingHints.KEY_TEXT_ANTIALIASING,  
                RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);  
        TextTitle textTitle = chart.getTitle();  
        textTitle.setFont(new Font("����", Font.PLAIN, 20));  
        domainAxis.setTickLabelFont(new Font("sans-serif", Font.PLAIN, 11));  
        domainAxis.setLabelFont(new Font("����", Font.PLAIN, 12));  
        rAxis.setTickLabelFont(new Font("sans-serif", Font.PLAIN, 12));  
        rAxis.setLabelFont(new Font("����", Font.PLAIN, 12));  
        chart.getLegend().setItemFont(new Font("����", Font.PLAIN, 12));  
        // renderer.setItemLabelGenerator(new LabelGenerator(0.0));  
        // renderer.setItemLabelFont(new Font("����", Font.PLAIN, 12));  
        // renderer.setItemLabelsVisible(true);  
    }  
    /** 
     * ���ͼƬ 
     *  
     * @param chart 
     */  
    private static void writeChartAsImage(JFreeChart chart) {  
        FileOutputStream fos_jpg = null;  
        try {  
            fos_jpg = new FileOutputStream("D:\\test\\fruit.jpg");  
            ChartUtilities.writeChartAsJPEG(fos_jpg, 1, chart, 400, 300, null);  
        } catch (Exception e) {  
            e.printStackTrace();  
        } finally {  
            try {  
                fos_jpg.close();  
            } catch (Exception e) {  
            }  
        }  
    }  

}
