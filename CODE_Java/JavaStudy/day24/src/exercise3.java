import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class exercise3 {
    public static void main(String[] args) throws IOException {
        FileInputStream fis = new FileInputStream("day24/src/a.txt");
        FileOutputStream fos =new FileOutputStream("day24/src/c.txt");
        int b,count=0;
        byte[] bytes = new byte[10];
        while((b=fis.read(bytes))!=-1){
            fos.write(bytes,0,b);
            count++;
        }
        fis.close();
        fos.close();
        System.out.println(count);
    }
}
