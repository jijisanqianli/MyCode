package day02;

import java.util.Random;

public class 数组的逆序交换 {
    static void main(String[] args) {
        Random r=new Random();
        int begin=r.nextInt(100);
        int num[]=new int[10];
        System.out.print("逆序前：");
        for(int i=0;i<=9;i++){
            num[i]=begin+i;
            System.out.print(num[i]+" ");
        }
        System.out.print("\n");
        for(int i=0,j=9;i<j;i++,j--) {
            int temp = num[i];
            num[i] = num[j];
            num[j] = temp;
        }
        System.out.print("逆序后：");
        for(int i=0;i<=9;i++){
            System.out.print(num[i]+" ");
        }
    }
}
