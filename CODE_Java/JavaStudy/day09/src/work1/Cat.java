package work1;

public class Cat extends Animal{
    String theClass="猫";

    @Override
    public String getType(){
        return "猫";
    }

    public Cat() {
    }

    public Cat(int age,String color) {
        setAge(age);
        setColor(color);
    }

    @Override
    public void eat(String something){
        System.out.println("眯着眼睛侧着头吃"+something);
    }

    public void catchMouse(){
        System.out.println("猫在逮老鼠");
    }
}
