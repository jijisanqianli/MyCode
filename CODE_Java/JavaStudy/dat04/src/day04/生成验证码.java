package day04;

/*五位验证码前四位大写字母或小写字母最后一位数字*/

import java.util.Random;

public class 生成验证码 {
    static void main(String[] args) {
        Random r=new Random();
        for(int i=0;i<5;i++){
            if(i<4){
                int big= r.nextInt(2);//抽取大小写
                char x;
                if(big==1){
                    int Bet= r.nextInt(26);
                    x=(char)('A'+Bet);
                }else{
                    int bet=r.nextInt(26);
                    x=(char)('a'+bet);
                }
                System.out.print(x);
            }else{
                int num=r.nextInt(10);
                System.out.print(num);
            }
        }
    }

}
