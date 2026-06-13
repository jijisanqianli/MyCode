import java.io.FileOutputStream;
import java.io.IOException;

public class exercise1 {
    public static void main(String[] args) throws IOException {
        FileOutputStream fos = new FileOutputStream("day24/src/a.txt");
        fos.write("Hello World".getBytes());
        fos.write("\r\n".getBytes());
        fos.write("Jerry".getBytes());
        fos.close();
    }
}
