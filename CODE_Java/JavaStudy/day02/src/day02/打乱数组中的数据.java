package day02;

import java.util.Random;

public class 打乱数组中的数据 {
    static void main(String[] args) {
        Random r=new Random();
        int num[]={1,2,3,4,5};
        int fre=r.nextInt(31)+20;//20-50次
        for(int i=0;i<=fre;i++){
            int pos1=r.nextInt(num.length);
            int pos2=r.nextInt(num.length);
            if(pos2!=pos1){
                int temp=num[pos1];
                num[pos1]=num[pos2];
                num[pos2]=temp;
            }
        }
        System.out.print("打乱后：");
        for(int i=0;i<= num.length;i++){
            System.out.print(num[i]+" ");
        }
    }
}
