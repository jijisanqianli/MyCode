package apiDemo;

import java.io.IOException;

public class RuntimeDemo {
    static void main(String[] args) {
        Runtime r1=Runtime.getRuntime();
        System.out.println(r1.availableProcessors());
        System.out.println(r1.maxMemory()/1024/1024);
        System.out.println(r1.totalMemory()/1024/1024);
        System.out.println(r1.freeMemory()/1024/1024);
        try {
            r1.exec("notepad");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        try {
            r1.exec("shutdown -s -a");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
