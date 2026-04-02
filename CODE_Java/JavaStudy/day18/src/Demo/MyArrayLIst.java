package Demo;

public class MyArrayLIst<E> {
    Object[] obj=new Object[10];
    int size=0;
    //E表示不确定的类型，已经定义过
    public boolean add(E e){
        obj[size]=e;
        size++;
        return true;
    }

    public E get(int index){
        return (E)obj[index];
    }
}
