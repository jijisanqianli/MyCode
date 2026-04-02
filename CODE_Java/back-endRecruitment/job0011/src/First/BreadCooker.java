package First;

public class BreadCooker implements Producer,Runnable{
    //记录BreadCooker的姓名
    String name;
    //所生产的Product的名字
    static String productName="面包";
    //所有BreadCooker总的面包生产量
    static int breadCount=0;

    @Override
    public void run() {
        while(true){//面包店将一直做面包直到顾客吃饱
            synchronized (Bakery.lock){
                while(Bakery.breadNum >= Bakery.maxBreadNum){
                    try {
                        Bakery.lock.wait();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
                if(BreadEater.breadConsumeCount>= BreadEater.consumerCount*BreadEater.maxPersonalCount){
                    Bakery.lock.notifyAll();
                    break;
                }
                breadCount++;
                Product bread = produce();
                Bakery.breadNum++;
                Bakery.breadLeft.add(bread);

                Bakery.lock.notifyAll();
            }
        }
    }

    @Override
    public synchronized Product produce() {
        System.out.println("面包师"+this.name+"制作了面包店的第"+breadCount+"个面包"+"，目前面包店内剩余"+(Bakery.breadNum+1)+"个面包");
        return new Product(productName,breadCount);
    }

    public BreadCooker(String name){
        this.name=name;
    }

    public void setName(String name){
        this.name=name;
    }

    @Override
    public String getProducerName() {
        return this.name;
    }

    @Override
    public int getProduceCount() {
        return breadCount;
    }
}
