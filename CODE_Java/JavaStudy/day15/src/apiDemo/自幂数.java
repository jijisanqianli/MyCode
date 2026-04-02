package apiDemo;

import java.util.ArrayList;

public class 自幂数 {
    static void main(String[] args) {
        //统计水仙花数
        int num=0;
        int digitCount=3;
        int numSelf=0;
        int count=0;//统计个数
        ArrayList<Integer> list=new ArrayList<>();
        for (int i = 1; i < 10; i++) {//百位
            double one=Math.pow(i,digitCount);
            num+=one;
            numSelf+=i;
            for (int j = 0; j < 10; j++) {//十位
                double two=Math.pow(j,digitCount);
                num+=two;
                if(num>999){
                    num-=two;
                    continue;
                }
                numSelf=numSelf*10+j;
                for (int k = 0; k < 10; k++) {//个位
                    double three=Math.pow(k,digitCount);
                    num+=three;
                    if(num>999){
                        num-=three;
                        continue;
                    }
                    numSelf=numSelf*10+k;
                    if(num==numSelf){
                        count++;
                        list.add(numSelf);
                        System.out.println(numSelf);
                    }
                    num-=three;
                    numSelf=(numSelf-k)/10;
                }
                num-=two;
                numSelf=(numSelf-j)/10;
            }
            num-=one;
            numSelf=(numSelf-i)/10;
        }
        System.out.println("共有"+count+"个水仙花数");
        /*for (int i = 0; i < list.size(); i++) {
            System.out.println(list.get(i));
        }*/
    }
}
