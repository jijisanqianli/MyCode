package Second.SynchronizedMethod;

public class Creep implements Runnable{
    static int player=100;
    @Override
    public void run() {
        method();
    }

    private synchronized static void method() {
        Thread now=Thread.currentThread();
        for (int i = 0; i < 3; i++) {
            if (player == 0) {
                break;
            }
            System.out.println("Creep-" + now.getName() + " attack...");
            player -= 20;
            System.out.println("Creep-" + now.getName() + ": 当前player的hp值= " + player);
            if (player == 0) {
                System.out.println("Creep-" + now.getName() + ": player is dead.");
                System.out.println("Creep-" + now.getName() + " end.");
                break;
            }
        }
    }
}
