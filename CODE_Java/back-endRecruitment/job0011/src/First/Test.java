package First;

public class Test {
    static void main(String[] args) {
        BreadCooker c1=new BreadCooker("老王");
        BreadCooker c2=new BreadCooker("老李");
        BreadEater e1=new BreadEater("小明");
        BreadEater e2=new BreadEater("小王");
        Thread cooker1=new Thread(c1);
        Thread cooker2=new Thread(c2);
        Thread eater1=new Thread(e1);
        Thread eater2=new Thread(e2);
        cooker1.start();
        cooker2.start();
        eater1.start();
        eater2.start();
    }
}
