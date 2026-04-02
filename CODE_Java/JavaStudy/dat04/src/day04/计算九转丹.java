package day04;

import java.util.Scanner;

public class 计算九转丹 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        while (true){
            int begin= sc.nextInt();
            int qianneng= sc.nextInt();
            double result=qianneng*1.0*0.77-begin*1.0;
            int jiuzhuandan=(int) Math.ceil (result/10000);
            System.out.println(jiuzhuandan);
            if(qianneng==0){
                break;
            }
        }
    }
}
