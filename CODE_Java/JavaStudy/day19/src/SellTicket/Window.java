package SellTicket;

public class Window extends Thread{
    //表示所有类共用一个数据ticket
    static int ticket=0;
    static Object lock=new Object();
    @Override
    public void run(){

        while(true){
            synchronized (lock){
                if(ticket>=100){
                    break;
                }
                ticket++;
                System.out.println(getName()+"正在卖第"+ticket+"张票");
            }
        }
    }
}
