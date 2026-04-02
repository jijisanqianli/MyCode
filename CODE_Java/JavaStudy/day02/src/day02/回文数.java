package day02;
import java.util.Scanner;

public class 回文数 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int x= sc.nextInt();
        int num1=x,num2=0,i;
        while(num1!=0){
            i=num1%10;
            num1=(num1-i)/10;
            num2=num2*10+i;
        }
        System.out.println(x==num2);
    }
}
