package day04;

import java.util.Random;
import java.util.Scanner;

public class 双色球系统 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        while(true){
            mainmenu();
            int chioce=sc.nextInt();
            if(chioce==1){
                func1();
            }else if(chioce==2){
                func2();
            }else if(chioce==3){
                break;
            }else{
                System.out.println("请输入正确的选择！！！");
            }
        }
    }

    static void mainmenu() {
        System.out.println("====模拟双色球系统====");
        System.out.println("1.模拟买彩票");
        System.out.println("2.猜猜中奖要几次");
        System.out.println("3.退出");
    }

    static void func1() {
        while(true){
            Scanner sc=new Scanner(System.in);
            int prize[]=new int[6];//六种奖
            System.out.print("请输入您要买的彩票张数:");
            int quantity=sc.nextInt();
            int standcode[]=getcode();
            for(int i=0;i<quantity;i++) {
                int mycode[] = getcode();
                int result[] = compare(standcode, mycode);
                duijiang(result, prize);
            }
            printprize(prize);
            System.out.println("再来一次？输1继续 输2退出");
            int choice=1;
            while(true){
                choice=sc.nextInt();
                if(choice==1||choice==2){
                    break;
                }else{
                    System.out.println("请输入正确选项！！！");
                }
            }
            if(choice==2){
                break;
            }
        }
    }

    static void func2() {
        while(true){
            Scanner sc=new Scanner(System.in);
            System.out.print("请问您想中几等奖：");
            int goal= sc.nextInt();
            int standcode[]=getcode();
            long count=0;
            while (true){
                int mycode[]=getcode();
                int result[]=compare(standcode,mycode);
                int prize[]=new int[6];
                duijiang(result,prize);
                count++;
                if(prize[goal-1]!=0){
                    break;
                }
                if(count==100000000){
                    count=0;
                    break;
                }
            }
            if(count==0){
                System.out.println("抱歉，在1亿次模拟中没有一次成功");
            }else{
                System.out.println("成功!您花费了"+count+"次抽到了您想要的奖");
            }
            System.out.println("再来一次？输1继续 输2退出");
            int choice=1;
            while(true){
                choice=sc.nextInt();
                if(choice==1||choice==2){
                    break;
                }else{
                    System.out.println("请输入正确选项！！！");
                }
            }
            if(choice==2){
                break;
            }
        }
    }

    static void printprize(int prize[]) {
        int count=0;
        for(int i=0;i<6;i++){
            count+=prize[i];
        }
        if(count==0){
            System.out.println("很遗憾，您并没有中奖");
        }
        else{
            if(prize[0]!=0){
                System.out.println("您中了"+prize[0]+"个一等奖");
            }
            if(prize[1]!=0){
                System.out.println("您中了"+prize[1]+"个二等奖");
            }
            if(prize[2]!=0){
                System.out.println("您中了"+prize[2]+"个三等奖");
            }
            if(prize[3]!=0){
                System.out.println("您中了"+prize[3]+"个四等奖");
            }
            if(prize[4]!=0){
                System.out.println("您中了"+prize[4]+"个五等奖");
            }
            if(prize[5]!=0) {
                System.out.println("您中了" + prize[5] + "个六等奖");
            }
            long sum=prize[0]*10000000+prize[1]*5000000+prize[2]*3000+prize[3]*200+prize[4]*10+prize[5]*5;
            System.out.println("总计中奖金额为"+sum+"元");
        }
    }

    static int[] compare(int stand[],int my[]) {
        int red=0,blue=0;
        int standCopy[]=new int[stand.length];
        for(int i=0;i<stand.length;i++){
            standCopy[i]=stand[i];
        }
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(standCopy[j]==0){
                    continue;
                }
                if(my[i]==standCopy[j]){
                    red++;
                    standCopy[j]=0;
                }
            }
        }
        if(my[6]==stand[6]){
            blue++;
        }
        int result[]={red,blue};
        return result;
    }

    static void duijiang(int result[],int prize[]) {
        int blue=result[1];
        int red=result[0];
        if(blue==1){
            if(red>=0&&red<=2){
                prize[5]++;
            }else if(red==3){
                prize[4]++;
            }else if(red==4){
                prize[3]++;
            }else if(red==5){
                prize[2]++;
            }else if(red==6){
                prize[0]++;
            }
        }else if(blue==0){
            if(red==4){
                prize[4]++;
            }else if(red==5){
                prize[3]++;
            }else if(red==6){
                prize[1]++;
            }
        }
    }

    static int[] getcode() {
        Random r=new Random();
        int num[]=new int[7];
        for(int i=0;i<7;i++){
            if(i<6){
                int red=r.nextInt(33)+1;
                num[i]=red;
            }else{
                int blue=r.nextInt(16)+1;
                num[i]=blue;
            }
        }
        return num;
    }
}
