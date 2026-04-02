package day02;
import java.time.Year;
import java.util.Scanner;

public class 老丈人喝酒 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入您的酒量");
        int you=sc.nextInt();
        int he=50;
        if (you>he){
            System.out.println("小伙子不错");
        }else{
            System.out.println("不太行啊");
        }
    }
}
