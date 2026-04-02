package Third;

public class MyNode<E> {
    E value;
    MyNode<E> next;

    public MyNode(){
        this.next=null;
    }

    public MyNode(E value){
        this.value=value;
        this.next=null;
    }
}
