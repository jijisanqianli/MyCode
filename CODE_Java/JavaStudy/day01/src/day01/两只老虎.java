package day01;
import java.util.Scanner;

public class 两只老虎 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("输入第一只老虎重量");
        int tiger1= sc.nextInt();
        System.out.println("输入第二只老虎重量");
        int tiger2= sc.nextInt();
//        boolean result=tiger1==tiger2;
//        System.out.println(result);
        System.out.println(tiger1==tiger2?"相同":"不同");
    }
}
