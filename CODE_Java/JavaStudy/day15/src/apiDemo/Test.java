package apiDemo;

import java.util.Scanner;

public class Test {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int time= sc.nextInt();
        for(int i=time;i>=1;i--){
            System.out.println("还剩"+i+"秒");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        System.out.println("还剩0秒");
        System.out.println("计时结束");
    }
}
