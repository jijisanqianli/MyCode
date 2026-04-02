package day01;

public class 三个和尚身高比较 {
    static void main(String[] args) {
        int num1=150,num2=210,num3=165;
        int middle=num1>num2?num1:num2;
        int max=middle>num3?middle:num3;
        System.out.println(max);
    }
}
