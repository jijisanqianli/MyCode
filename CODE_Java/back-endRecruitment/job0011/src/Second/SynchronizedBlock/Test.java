package Second.SynchronizedBlock;

public class Test {
    static void main(String[] args) {
        Creep creep=new Creep();
        Thread A=new Thread(creep);
        Thread B=new Thread(creep);
        A.setName("A");
        B.setName("B");
        A.start();
        B.start();
    }
}
