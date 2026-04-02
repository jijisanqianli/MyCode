package interfaceDemo1;

public class Dog extends Animal implements Swim{
    public Dog() {
    }

    public Dog(String name, int age) {
        super(name, age);
    }

    @Override
    public void swim(){
        System.out.println("狗刨");
    }

    @Override
    public void eat(){
        System.out.println("吃骨头");
    }
}
