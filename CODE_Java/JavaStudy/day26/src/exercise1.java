import java.io.*;

public class exercise1 {
    public static void main(String[] args) throws IOException {
        // 先读取
        BufferedInputStream bis = new BufferedInputStream(new FileInputStream("day26/src/record.txt"));
        char b=(char)bis.read();
        bis.close();

        if(b<='3' && b>'0') {

            System.out.println("欢迎您的第"+b+"次使用");
            // 读完再写入，避免 FileOutputStream 清空文件影响读取
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("day26/src/record.txt"));
            bos.write((char)(b+1));
            bos.flush();
            bos.close();

        }else{
            System.out.println("已经超过使用次数限制");
        }

    }
}
