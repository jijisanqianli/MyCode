package day01;
import java.util.Scanner;

public class 数字6 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int a=sc.nextInt();
        int b=sc.nextInt();
        boolean result=(a==6||b==6||(a+b)%6==0);
        System.out.println(result);
    }
}
