package day06;

import java.util.StringJoiner;

public class StringJoinerDemo {
    static void main(String[] args) {
        StringJoiner sj=new StringJoiner(",","[","]");
        sj.add("1").add("123");
        System.out.println(sj);
        System.out.println(sj.length());
    }
}
