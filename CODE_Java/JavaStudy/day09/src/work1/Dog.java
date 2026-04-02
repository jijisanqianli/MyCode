package work1;

public class Dog extends Animal{

    public Dog() {
    }

    public Dog(int age,String color) {
        setAge(age);
        setColor(color);
    }

    @Override
    public String getType(){
        return "狗";
    }

    @Override
    public void eat(String something){
        System.out.println("两只前腿死死的抱住"+something+"猛吃");
    }

}
