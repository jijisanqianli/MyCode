package work1;

public class Breeder extends Person{
    public Breeder() {
    }

    public Breeder(String name, int age) {
        setName(name);
        setAge(age);
    }
    public void keepPet(Animal animal,String something){
        System.out.println("年龄为"+getAge()+"的"+getName()+"养了一只"+animal.getColor()+"的"+animal.getAge()+"岁的"+animal.getType());
        System.out.print(animal.getAge()+"岁的"+animal.getColor()+"的"+animal.getType());
        animal.eat(something);
    }
}
