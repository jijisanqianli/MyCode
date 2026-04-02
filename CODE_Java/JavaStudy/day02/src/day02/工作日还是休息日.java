package day02;
import java.util.Scanner;

public class 工作日还是休息日 {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int week= sc.nextInt();
        switch(week){
            /*case 1,2,3,4,5:
                System.out.println("工作日");
                break;
            case 6,7:
                System.out.println("休息日");
                break;
            default:
                System.out.println("你逗我玩呢");*/
            case 1,2,3,4,5 ->System.out.println("工作日");
            case 6,7-> System.out.println("休息日");
            default -> System.out.println("你逗我玩呢");
        }
    }
}
