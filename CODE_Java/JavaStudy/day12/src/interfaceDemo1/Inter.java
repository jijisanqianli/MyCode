package interfaceDemo1;

public interface Inter {
    public default void show(){
        System.out.println("这是一个默认方法");
    }
    void showCopy();
}
