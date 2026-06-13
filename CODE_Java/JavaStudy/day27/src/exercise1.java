import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;

public class exercise1 {
    static void main(String[] args) throws IOException {
        FileUtils.copyFile(new File("day24/src/c.txt"),new File("day27//src/c.txt"));
    }
}
