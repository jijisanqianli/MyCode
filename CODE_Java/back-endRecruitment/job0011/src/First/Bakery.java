package First;

import java.util.ArrayList;

public class Bakery {
    //目前剩余面包数
    static int breadNum=0;
    //最大容纳面包数
    static final int maxBreadNum=20;
    //目前面包库存
    static ArrayList<Product> breadLeft=new ArrayList<>();
    //公用的一把锁
    static final Object lock=new Object();
}
