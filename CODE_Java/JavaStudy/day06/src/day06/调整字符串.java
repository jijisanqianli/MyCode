package day06;

import java.util.Scanner;

public class 调整字符串 {
        /*给定两个字符串，A 和 B。
        A 的旋转操作就是将 A 最左边的字符移动到最右边。
        例如，若 A = 'abcde'，在移动一次之后结果就是'bcd'ea'。
        如果在若干次调整操作之后，A 能变成 B，那么返回True。
        如果不能匹配成功，则返回false*/
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入两个字符串，中间用空格隔开");
        String A=sc.next();String B=sc.next();
        System.out.println(giveResult(A,B));
    }

    static String rotating(String A) {
        StringBuilder sb=new StringBuilder(A.substring(1));
        sb.append(A.charAt(0));
        return sb.toString();
    }

    static boolean giveResult(String A,String B) {
        String result=A;
        if(A.equals(B)){
            return true;
        }else{
            do{
                result=rotating(result);
                if(result.equals(B)){
                    return true;
                }
            }while(result.equals(A)==false);
            return false;
        }
    }
}
