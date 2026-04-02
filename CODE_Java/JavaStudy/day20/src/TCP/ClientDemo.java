package TCP;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class ClientDemo {
    static void main(String[] args) throws IOException {
        Socket socket=new Socket("127.0.0.1",10000);
        //从连接通道中获取字节输出流
        OutputStream os=socket.getOutputStream();
        //转换流
        OutputStreamWriter osw=new OutputStreamWriter(os,"UTF-8");
        //搭配一个缓冲流
        BufferedWriter bw=new BufferedWriter(osw);
        //可一步完成：BufferedWriter bw=new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(),"UTF-8"));
        bw.write("你好啊，这是转换流的中文");
        //立即发送
        bw.flush();
        //结束
        bw.close();
    }
}
