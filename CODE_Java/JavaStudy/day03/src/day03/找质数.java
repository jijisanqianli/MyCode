package day03;

import java.util.Scanner;

public class 找质数 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int begin=sc.nextInt();
        int end=sc.nextInt();
        int x[]=findAllPrime(end);//包含到end的全部质数
        cutPrintPrime(x,begin);
    }

    static int[] findAllPrime(int end) {
        //一个线性筛
        int prime[]=new int[end];//存质数
        boolean num[]=new boolean[end+1];//存所有数字（遍历完）
        int primeCount=0;//存放质数的工具
        for(int i=2;i<=end;i++){//遍历所有数
            if(num[i]==false){//还没被筛掉的就进入质数列
                prime[primeCount]=i;
                primeCount++;
            }
            for(int p=0;p<=primeCount-1;p++){//筛掉数
                if(i*prime[p]<=end){//筛掉正在遍历的数与质数列的积
                    num[i*prime[p]]=true;
                }
                if(i%prime[p]==0){
                    break;
                }
            }
        }
        /*int primeCount=0;
        for(int i=2;i<=end;i++){
            int judge=1;
            for(int j=0;prime[j]!=0;j++){
                if(i%prime[j]==0){
                    judge=0;
                    break;
                }
            }
            if(judge==1){
                prime[primeCount]=i;
                primeCount++;
            }
        }*/
        return prime;
    }

    static void giveArr(int x[]) {
        for(int i=0;x[i]!=0;i++){
            System.out.print(x[i]+" ");
        }
    }

    static void cutPrintPrime(int x[],int begin) {
        int min=0;
        for(int i=0;x[i]!=0;i++){
            if(x[i]>=begin){
                min=i;
                break;
            }
        }
        for(int i=min;x[i]!=0;i++){
            System.out.print(x[i]+" ");
        }
    }
}
