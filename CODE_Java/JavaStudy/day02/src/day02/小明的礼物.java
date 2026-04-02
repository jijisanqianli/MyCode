package day02;
import java.util.Scanner;

public class 小明的礼物 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int grade= sc.nextInt();
        if(grade>=95&&grade<=100){
            System.out.println("自行车");
        }else if (grade<=94&&grade>=90) {
            System.out.println("游乐场");
        }else if(grade>=80&&grade<=89){
            System.out.println("变形金刚");
        }else{
            System.out.println("啥都没有");
        }
    }
}
