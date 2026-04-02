package day06;

import java.util.Scanner;

public class 反转字符串 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("输入一个字符串：");
        String theString=sc.nextLine();
        for (int i = theString.length()-1; i >= 0; i--) {
            System.out.print(theString.charAt(i));
        }
    }
}
