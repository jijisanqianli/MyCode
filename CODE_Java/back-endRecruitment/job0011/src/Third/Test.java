package Third;

public class Test {
    static void main(String[] args) {
        MyLinkedList<Integer> list = new MyLinkedList<>();
        list.addList(new MyNode<>(10));
        list.addList(new MyNode<>(20));
        list.addList(new MyNode<>(20));
        list.addList(new MyNode<>(30));

        System.out.println("find(20) = " + list.find(20)); // 1
        list.removeListByValue(20);
        System.out.println("size = " + list.getSize()); // 2
        list.removeList0();
        System.out.println("size = " + list.getSize()); // 1
    }
}
