package day05;

import java.util.Scanner;

public class test {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.print("请输入汽车数量：");
        int num=sc.nextInt();
        sc.nextLine();
        Car arr[]=new Car[num];
        for (int i = 0; i < arr.length; i++) {
            Car car=new Car();
            System.out.println("第"+(i+1)+"辆车");
            System.out.print("请输入汽车品牌：");
            String brand=sc.nextLine();
            car.setBrand(brand);
            System.out.print("请输入汽车价格：");
            double price=sc.nextDouble();
            sc.nextLine();
            car.setPrice(price);
            System.out.print("请输入汽车颜色：");
            String color=sc.nextLine();
            System.out.println();
            car.setColor(color);
            arr[i]=car;
        }
        System.out.println("已全部录入完毕，按回车将依次展示录入的车辆信息...");
        sc.nextLine();
        for (int i = 0; i < arr.length; i++) {
            System.out.print("第"+(i+1)+"辆车信息：");
            System.out.print("品牌："+arr[i].getBrand()+" ");
            System.out.print("价格："+arr[i].getPrice()+" ");
            System.out.print("颜色："+arr[i].getColor()+" ");
            System.out.println();
            System.out.print("按回车继续...");
            sc.nextLine();
        }
        System.out.println("已展示完所有车辆信息...");
    }
}
