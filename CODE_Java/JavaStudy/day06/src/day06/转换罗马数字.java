package day06;

import java.util.Scanner;
import java.util.StringJoiner;

public class 转换罗马数字 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        while(true){
            System.out.println("请输入一个长度小于10的数字");
            String number=sc.next();
            if(judge(number)==true){
                String[] romanNumber={"","I","II","III","IV","V","VI","VII","VIII","IX"};
                StringJoiner sj=new StringJoiner(" ");
                for(int i=0;i<number.length();i++){
                    sj.add(romanNumber[number.charAt(i)-'0']);
                }
                System.out.println(sj.toString());
                break;
            }else{
                System.out.println("请输入正确的数字!!!");
            }
        }
    }

    static boolean judge(String number) {
        if(number.length()>9){
            return false;
        }else{
            for(int i=0;i<number.length();i++){
                if(number.charAt(i)>'9'||number.charAt(i)<'0'){
                    return false;
                }
            }
            return true;
        }
    }
}
