package day07;

import java.util.ArrayList;

public class ArrayListDemo1 {
    static void main(String[] args) {
        ArrayList<String> list=new ArrayList<>();
        list.add("aaa");
        list.add("ddd");
        list.add("aaa");
        System.out.println(list);
        System.out.println(list.add("1"));
        System.out.println(list);
        list.remove("aaa");
        System.out.println(list);
    }
}
