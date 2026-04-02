package day06;

import java.util.Scanner;

public class 最后一个单词长度 {
    static void main(String[] args) {
        System.out.println("请输入一个由多个单词组成的字符串，中间用空格隔开");
        Scanner sc=new Scanner(System.in);
        String wordString=sc.nextLine();
        int i;
        for(i=wordString.length()-1;i>=0;i--){
            if(wordString.charAt(i)==' '){
                break;
            }
        }
        if(i==0){
            System.out.println(wordString.length());
        }else{
            System.out.println(wordString.length()-i-1);
        }
    }
}
