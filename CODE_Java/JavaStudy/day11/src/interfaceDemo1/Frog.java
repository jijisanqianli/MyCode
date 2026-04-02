package interfaceDemo1;

public abstract class Frog extends Animal implements Swim{
    public Frog() {
    }

    public Frog(String name, int age) {
        super(name, age);
    }

    @Override
    public void swim(){
        System.out.println("蛙泳");
    }

    @Override
    public void eat(){
        System.out.println("吃虫子");
    }
}

