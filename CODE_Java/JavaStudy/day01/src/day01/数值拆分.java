package day01;
import java.util.Scanner;

public class 数值拆分 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int a= sc.nextInt();
        int k;
        k=a%10;
        System.out.println(k);
        a=(a-k)/10;
        k=a%10;
        System.out.println(k);
        a=(a-k)/10;
        k=a%10;
        System.out.println(k);
    }
}
