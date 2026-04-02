package day02;
import java.util.Scanner;

public class 选择语句题 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String noodle= sc.next();
        switch (noodle){
            case"拉面":
                System.out.println("吃1");
                break;
            case"热干面":
                System.out.println("吃2");
                break;
            case"炸酱面":
                System.out.println("吃3");
                break;
            case"油泼面":
                System.out.println("吃4");
                break;
            default:
                System.out.println("吃铲铲");
                break;
        }
    }
}
