package day02;

public class 逢七过 {
    static void main(String[] args) {
        for (int i = 1; i <=100 ; i++) {
            if(i%7==0){
                continue;
            }
            System.out.println(i);
        }
    }
}
