package SellTicket;

public class MyRunnable implements Runnable {
    int ticket=0;
    @Override
    public void run() {
        while(true){
                if (extracted()) break;
        }
    }

    private synchronized boolean extracted() {
        if(ticket>=100){
            return true;
        }
        ticket++;
        System.out.println(Thread.currentThread().getName()+"正在卖第"+ticket+"张票");
        return false;
    }
}
