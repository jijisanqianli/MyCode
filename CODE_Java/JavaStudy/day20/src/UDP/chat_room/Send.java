package UDP.chat_room;

import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class Send {
    static void main(String[] args) throws IOException {
        Scanner sc=new Scanner(System.in);
        DatagramSocket ds=new DatagramSocket();
        InetAddress addressGoal=InetAddress.getByName("127.0.0.1");
        int portGoal=8888;
        while(true){
            String sentenceInitial=sc.nextLine();
            byte[] sentence=sentenceInitial.getBytes();
            DatagramPacket dp=new DatagramPacket(sentence,0,sentence.length,addressGoal,portGoal);
            ds.send(dp);
            if(sentenceInitial.equals("886")){
                System.out.println("成功发送消息:"+sentenceInitial);
                break;
            }
            System.out.println("成功发送消息:"+sentenceInitial+",请继续发送您的消息");
        }
        ds.close();
        System.out.println("本次会话已结束...");
    }
}
