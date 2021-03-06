
package Wifi;



import org.jfree.chart.ChartFactory;  
import org.jfree.chart.ChartPanel;  
import org.jfree.chart.JFreeChart;  
import org.jfree.chart.axis.ValueAxis;  
import org.jfree.data.time.Millisecond;  
import org.jfree.data.time.TimeSeries;  
import org.jfree.data.time.TimeSeriesCollection;  
  
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;  
  
public class RealTimeChartTest24 extends ChartPanel implements Runnable {  
  
    private static final long serialVersionUID = 1L;  
    private static TimeSeries timeSeries;  
   // public  String s11=null;
    
  
    public RealTimeChartTest24(String chartContent, String title, String yAxisName) {  
        super(createChart(chartContent, title, yAxisName));  
    }  
  
  

	

	private static JFreeChart createChart(String chartContent, String title, String yAxisName) {  
        timeSeries = new TimeSeries(chartContent);  
        TimeSeriesCollection timeseriescollection = new TimeSeriesCollection(timeSeries);  
        JFreeChart jfreechart = ChartFactory.createTimeSeriesChart(title, "时间(秒)", yAxisName, timeseriescollection, true, true, false);  
        ValueAxis valueaxis = jfreechart.getXYPlot().getDomainAxis();  
        valueaxis.setAutoRange(true);  
        valueaxis.setFixedAutoRange(30000D);  
        return jfreechart;  
    }  
	static String readFile() {
		String str = "", temp = null;
		try {
			File file = new File("data\\pmval.txt");
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

   
    @Override  
    public void run() {  
    
    	  test t=new test();
    	
        while (true) {  
            try {     
                   String s3= readFile();
				   Float b=Float.valueOf(s3);
				
              timeSeries.add(new Millisecond(),b);  
                Thread.sleep(200);  
            } catch (InterruptedException e) {  
            }  
        }  
    }  
  
   
}  
