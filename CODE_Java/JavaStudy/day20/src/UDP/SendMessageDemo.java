package UDP;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class SendMessageDemo {
    static void main(String[] args) throws IOException {
        //建立快递公司，确定由哪个端口发送
        DatagramSocket datagramSocket=new DatagramSocket(22222);
        //处理发送的信息
        String str="你好啊！！！Ciallo～(∠・ω< )⌒★";
        byte[] bytes=str.getBytes();
        //定义目标ip
        InetAddress address=InetAddress.getByName("127.0.0.1");
        //确定发送向哪个端口
        int port=10086;
        //打包
        DatagramPacket datagramPacket=new DatagramPacket(bytes,bytes.length,address,port);
        //发送
        datagramSocket.send(datagramPacket);
        //释放资源
        datagramSocket.close();
    }
}
