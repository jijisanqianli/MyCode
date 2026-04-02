package day06;

import java.util.Scanner;

public class 对称字符串 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        StringBuilder sb=new StringBuilder();
        String theString=sc.nextLine();
        sb.append(theString).reverse();
        if(theString.equals(sb.toString())){
            System.out.println("是对称字符串");
        }else{
            System.out.println("不是对称字符串");
        }
    }
}
