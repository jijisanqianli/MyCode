package First;

public class BreadEater implements Consumer,Runnable{
    String name;
    //顾客单人最大消费数量
    static final int maxPersonalCount=30;
    //记录顾客个人消费数
    int personalCount=0;
    //记录顾客消费的总数
    static int breadConsumeCount=0;
    //记录顾客总人数
    static int consumerCount=0;

    @Override
    public void run() {
        while (true) {
            synchronized (Bakery.lock) { // 全局锁保证资源安全
                try {
                    // 1. 无面包时等待生产
                    while (Bakery.breadNum <= 0) {
                        // 若总消费数已到60（2人×30），退出
                        if (breadConsumeCount >= consumerCount*maxPersonalCount) {
                            Bakery.lock.notifyAll(); // 唤醒面包师
                            return;//
                        }
                        Bakery.lock.wait(); // 等待面包师生产
                    }
                    // 2. 个人吃满30个，退出
                    if (personalCount >= 30) {
                        Bakery.lock.notifyAll(); // 唤醒其他线程
                        return;
                    }
                    // 3. 消费面包（取最后一个）
                    consume(Bakery.breadLeft.remove(Bakery.breadNum - 1));
                    Bakery.breadNum--;
                    breadConsumeCount++;
                    personalCount++;
                    // 4. 唤醒等待的面包师
                    Bakery.lock.notifyAll();

                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        }
    }

    public BreadEater(String name) {
        this.name = name;
        //记录的顾客人数+1
        consumerCount++;
    }

    @Override
    public void consume(Product bread) {
        System.out.println("顾客" + this.name + "吃下了自己的第" + (personalCount+1)+ "个面包（面包ID：" + bread.getId() +
                "）"+"，目前面包店内剩余"+(Bakery.breadNum-1)+"个面包");
    }

    @Override
    public String getConsumerName() {
        return this.name;
    }

    @Override
    public int getConsumerCount() {
        return breadConsumeCount;
    }
}
