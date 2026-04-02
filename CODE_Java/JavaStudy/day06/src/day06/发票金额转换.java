package day06;

import java.util.Scanner;

public class 发票金额转换 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        char[] blank= {'零','壹','贰','叁','肆','伍','陆','柒','捌','玖'};
        System.out.println("请输入数字金额:");
        String smallPrice=sc.nextLine();
        String result1="";
        for(int i=0;i<smallPrice.length();i++){
            result1=result1+blank[smallPrice.charAt(i)-'0'];
        }
        //System.out.println(result1);
        while(result1.length()!=7){
            result1="零"+result1;
        }
        //System.out.println(result1);
        char[] result=new char[14];
        result[1]=result[9]='佰';result[3]=result[11]='拾';result[5]='万';result[7]='仟';result[13]='元';
        int count=0;
        for(int i=0;i<=13;i++){
            if(i%2!=0){
                System.out.print(result[i]);
            }else{
                result[i]=result1.charAt(count);
                System.out.print(result[i]);
                count++;
            }
        }
    }
}
