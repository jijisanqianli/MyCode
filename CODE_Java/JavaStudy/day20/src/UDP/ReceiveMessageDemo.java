package UDP;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class ReceiveMessageDemo {
    static void main(String[] args) throws IOException {
        //创建快递公司,需要绑定端口接收信息
        DatagramSocket datagramSocket=new DatagramSocket(10086);
        //创建接收数据的包
        byte[] bytes=new byte[1024];
        DatagramPacket datagramPacket=new DatagramPacket(bytes, bytes.length);
        //接收数据
        datagramSocket.receive(datagramPacket);
        //解析数据包
        byte[] dataInitial=datagramPacket.getData();
        int len=datagramPacket.getLength();
        String dataProcessed=new String(dataInitial,0,len);
        InetAddress address=datagramPacket.getAddress();
        int portGet=datagramSocket.getLocalPort();
        int portSource=datagramPacket.getPort();
        //输出
        System.out.println("从端口:"+portGet+"接收到数据:"+dataProcessed);
        System.out.println("数据长度:"+len);
        System.out.println("数据来源ip:"+address);
        System.out.println("数据来源端口:"+portSource);
        //释放资源
        datagramSocket.close();
    }
}
