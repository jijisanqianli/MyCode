package UDP.chat_room;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class Receive {
    static void main(String[] args) throws IOException {
        DatagramSocket ds=new DatagramSocket(8888);
        byte[] source=new byte[1024];
        while(true){
            DatagramPacket dp=new DatagramPacket(source, source.length);
            ds.receive(dp);
            byte[] dataInitial=dp.getData();
            String dataProcessed=new String(dataInitial,0,dp.getLength());
            InetAddress addressFrom=dp.getAddress();
            System.out.println("ip为"+addressFrom+"的用户说:"+dataProcessed);
            if(dataProcessed.equals("886")){
                break;
            }
        }
        ds.close();
        System.out.println("本次会话已结束...");
    }
}
