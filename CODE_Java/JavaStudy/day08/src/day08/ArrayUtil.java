package day08;

import java.util.StringJoiner;

public class ArrayUtil {
    private ArrayUtil(){}

    public static String printArr(int[] arr){
        StringJoiner sj=new StringJoiner(",","[","]");
        for(int i=0;i<arr.length;i++){
            sj.add(String.valueOf(arr[i]));
        }
        return sj.toString();
    }

    public static double getAverage(double[] arr){
        double sum=0;
        for(int i=0;i<arr.length;i++){
            sum+=arr[i];
        }
        return sum/(1.0*arr.length);
    }

}
