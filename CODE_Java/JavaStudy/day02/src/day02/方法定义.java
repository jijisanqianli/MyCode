package day02;


import java.util.Scanner;

public class 方法定义 {
    /*
    * 最简单的方法定义：public static void 方法名() {}
    * */
    /*
    * 方法的重载：同一个类中，方法名相同，参数不同的方法。与返回值无关。
    * 参数不同：个数，类型···
    * */
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int x[]={1,2,3,4,5};
        arrtra(x);
        System.out.print("\n");
        System.out.println(max(x));
        arrtra(copyOfRange(x,2,4));
    }

    static void arrtra(int a[]) {
        //遍历打印数组
        for(int i=0;i<a.length;i++){
            System.out.print(a[i]+" ");
        }
    }

    static int max(int a[]) {
        /*找数组最大值*/
        int max0=0;
        for(int i=0;i<a.length;i++){
            if(a[i]>max0){
                max0=a[i];
            }
        }
        return max0;
    }

    static int[] copyOfRange(int a[],int from,int end) {
        /*复制数组：从from复制到end*/
        int x[]=new int[end-from+1];
        for(int i=0;i<x.length;i++){
            x[i]=a[from+i];
        }
        return x;
    }
}
