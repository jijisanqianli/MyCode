package apiDemo;

import java.io.IOException;
import java.util.Scanner;

public class ShutdownTiming {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        while (true){
            clear();
            menu();
            int choice=sc.nextInt();
            sc.nextLine();
            if(choice==1){
                clear();
                System.out.println("您希望多少秒后关机");
                int time=sc.nextInt();
                sc.nextLine();
                clear();
                try {
                    Runtime.getRuntime().exec("shutdown -s -t "+time);
                    System.out.println("定时关机已启动！！！设定时间为"+time+"秒");
                    System.out.println("按任意键继续....");
                    sc.nextLine();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }else if(choice==2){
                clear();
                try {
                    Runtime.getRuntime().exec("shutdown -a");
                    System.out.println("定时关机已取消！！！");
                    System.out.println("按任意键继续....");
                    sc.nextLine();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }else if(choice==3){
                System.exit(0);
            }else{
                System.out.println("请输入正确选项！！！");
                System.out.println("按任意键继续....");
                sc.nextLine();
            }
        }

    }

    public static void menu(){
        System.out.println("1.设定定时关机时间");
        System.out.println("2.取消定时关机");
        System.out.println("3.退出");
        System.out.print("请输入选项：");
    }

    public static void clear() {
        try {
            // Windows CMD清屏命令
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        } catch (Exception e) {
            System.out.println("清屏失败: " + e.getMessage());
        }
    }
}
