package day03;

import java.util.Scanner;

public class 卖飞机票 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int month,mode;
        double realPrice=0,price;
        price=sc.nextInt();
        month=sc.nextInt();
        mode=sc.nextInt();//1为头等舱2为经济舱
        switch (month){
            case 1,2,3,4,11,12:
                if(mode==1){
                    realPrice=price*0.90;
                }else{
                    realPrice=price*0.85;
                }
                break;
            case 5,6,7,8,9,10:
                if(mode==1){
                    realPrice=price*0.7;
                }else{
                    realPrice=price*0.65;
                }
                break;
            default:
                System.out.println("请输入合理数据");
        }
        System.out.println(realPrice);
    }
}
