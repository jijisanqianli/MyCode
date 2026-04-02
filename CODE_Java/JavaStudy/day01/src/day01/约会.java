package day01;
import java.util.Scanner;

public class 约会 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入两个魅力值");
        int I= sc.nextInt();
        int her= sc.nextInt();
        System.out.println(I>her);
    }
}
