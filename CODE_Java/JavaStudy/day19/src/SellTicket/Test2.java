package SellTicket;

public class Test2 {
    static void main(String[] args) {
        Window w1=new Window();
        Window w2=new Window();
        Window w3=new Window();

        w1.setName("窗口1");
        w2.setName("窗口2");
        w3.setName("窗口3");

        w1.start();
        w2.start();
        w3.start();
    }
}
