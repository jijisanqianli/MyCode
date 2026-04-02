package day06;

import java.util.Scanner;

public class SringDemo2 {
    //遍历字符串的练习
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入一个字符串");
        String example=sc.nextLine();
        for(int i=0;i<example.length();i++) {
            System.out.println("第"+(i+1)+"个字符为:'"+example.charAt(i)+"'");
        }
    }
}
