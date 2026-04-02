package day02;
import java.util.Random;

public class 遍历数组求和 {
    static void main(String[] args) {
        Random r=new Random();
        int num[]=new int[10];
        int sum=0,average,count=0;
//      int number=r.nextInt(100);从0开始到n-1结束
        //生成任意数到到任意数的随机数7-15
        /*1.让这个范围头尾都减去一个值，让这个范围从零开始（再加上就行）·······*/
        for(int i=0;i<=9;i++){
            int number= r.nextInt(100);
            num[i]=number+1;
            System.out.print(num[i]+" ");
            sum+=num[i];
        }
        average=sum/10;
        for(int i=0;i<=9;i++){
            if(num[i]<average){
                count++;
            }
        }
        System.out.print("\n");
        System.out.println("平均数："+average);
        System.out.println("个数："+count);
    }
}
