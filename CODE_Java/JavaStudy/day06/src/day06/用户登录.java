package day06;

import java.util.Scanner;

public class 用户登录 {
    static void main(String[] args) {
        String rightName="Jerry";
        String rightPassword="456321";
        Scanner sc=new Scanner(System.in);
        boolean judge=false;
        for(int i=0;i<3;i++){
            System.out.println("请输入用户名：");
            String userName=sc.nextLine();
            System.out.println("请输入密码：");
            String password=sc.nextLine();
            if(userName.equals(rightName)){
                if(password.equals(rightPassword)){
                    judge=true;
                    break;
                }else{
                    System.out.println("密码错误请重试！！！");
                }
            }else{
                System.out.println("请输入正确的用户名！！！");
            }
        }
        if(judge==false){
            System.out.println("你的错误次数过多，请稍后再试...");
        }else{
            System.out.println("登录成功！！！");
        }
    }
}
