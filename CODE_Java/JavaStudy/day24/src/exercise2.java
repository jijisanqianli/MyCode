import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class exercise2 {
    public static void main(String[] args) throws IOException {
        FileInputStream fis = new FileInputStream("day24/src/a.txt");
        int b=0;
        while ((b=fis.read()) != -1) {
            System.out.print((char)b);
        }
        fis.close();
    }
}
