package Demo;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

public class LIstDemo1 {
    static void main(String[] args) {
        List<String> list=new ArrayList<>();
        list.add("aaa");
        list.add("bbb");
        list.add("ccc");
        /*for (String s : list) {
            System.out.println(s);
        }
        System.out.println("============");
        list.forEach(s -> System.out.println(s));*/
        ListIterator<String> it=list.listIterator();

    }

}
