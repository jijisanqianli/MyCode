package day01;

public class 三元运算符 {
    static void main(String[] args) {
        //格式：关系表达式？表达式1：表达式2；
        int a=10,b=20;
        int max=a>b?a:b;//求两数较大值
        System.out.println(a>b?a:b);
    }
}
