package day01;

public class 短路逻辑运算符 {
    static void main(String[] args) {
        //短路与&&
        //短路或||
        int a=10;
        int b=10;
        boolean result=++a<5&&++b<5;
        System.out.println(result);
        System.out.println(a);
        System.out.println(b);
    }
}
