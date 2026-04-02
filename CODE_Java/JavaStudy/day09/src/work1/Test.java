package work1;

public class Test {
    static void main(String[] args) {
        Animal dog=new Dog(2,"黑颜色");
        Animal cat=new Cat(3,"灰颜色");
        Breeder b1=new Breeder("老王",30);
        Breeder b2=new Breeder("老李",25);
        b1.keepPet(dog,"骨头");
        b2.keepPet(cat,"鱼");
    }
}
