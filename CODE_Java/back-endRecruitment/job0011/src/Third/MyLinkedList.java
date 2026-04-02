package Third;

import java.util.ArrayList;

public class MyLinkedList<E> {
    private MyNode<E> head;
    private int size;

    public MyLinkedList(){
        head=new MyNode<>();
        this.size=0;
    }

    public boolean addList(MyNode<E> newNode){
        if(newNode==null){
            return false;
        }
        MyNode<E> tool=this.getHead();
        while(tool.next!=null){
            tool=tool.next;
        }
        tool.next=newNode;
        size++;
        return true;
    }

    public void removeList0(){
        MyNode<E> tool=this.getHead();
        for(int i=0;i<size-1;i++){
            tool=tool.next;
        }
        tool.next=null;
        size--;
    }

    public void removeListByValue(E value){
        MyNode<E> tool=this.getHead();
        int index=-1;
        ArrayList<Integer> arrayList=new ArrayList<>();
        while(tool.next!=null){
            index++;
            tool=tool.next;
            if(tool.value != null&&tool.value.equals(value)){
                arrayList.add(index);
            }
        }
        int count=0;
        for (Integer i : arrayList) {
            removeListByIndex(i-count);
            count++;
        }
    }

    public boolean removeListByIndex(int index){
        if(index>=size||index<0){
            return false;
        }
        MyNode<E> tool=this.getHead();
        //下标从0开始
        for(int i=0;i<index;i++){
            tool=tool.next;
        }
        //此时为被删除节点的前一个节点
        tool.next=tool.next.next;
        size--;
        return true;
    }

    public int find(E value){
        if(value==null){
            return -1;
        }
        int index=-1;
        MyNode<E> tool=this.getHead();
        while(tool.next!=null){
            tool=tool.next;
            index++;
            if(tool.value.equals(value)){
                return index;
            }
        }
        return -1;
    }

    public MyNode<E> getHead(){
        return this.head;
    }

    public int getSize(){
        return this.size;
    }
}
