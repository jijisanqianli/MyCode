import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class exercise1 {
    public static void main(String[] args) throws IOException {
        FileReader fr = new FileReader("day25/src/a.txt");
        int ch;
        while((ch=fr.read())!=-1){
            System.out.print((char)ch);
        }
        fr.close();
    }
}
