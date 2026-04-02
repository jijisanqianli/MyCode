package Demo1;

import java.util.ArrayList;

public  class Test {
    static void main(String[] args) {
        PossyCat possyCat=new PossyCat("张三",3);
        LihuaCat lihuaCat=new LihuaCat("李四",4);
        TeddyDog teddyDog=new TeddyDog("王五",5);
        HuskyDog huskyDog=new HuskyDog("赵六",6);
        ArrayList<Cat> catList=new ArrayList<>();
        catList.add(possyCat);
        catList.add(lihuaCat);
        ArrayList<Dog> dogList = new ArrayList<>();
        dogList.add(teddyDog);
        dogList.add(huskyDog);
        ArrayList<Animal> animalList=new ArrayList<>();
        animalList.add(possyCat);
        animalList.add(lihuaCat);
        animalList.add(teddyDog);
        animalList.add(huskyDog);
        keepCat(catList);
        System.out.println("============================");
        keepDog(dogList);
        System.out.println("============================");
        keepAnimal(animalList);
    }

    public static void keepCat(ArrayList<? extends Cat> list){
        for (Cat cat : list) {
            cat.eat();
        }
    }

    public static void keepDog(ArrayList<? extends Dog> list){
        for (Dog dog : list) {
            dog.eat();
        }
    }

    public static void keepAnimal(ArrayList<? extends Animal> list){
        for (Animal animal: list) {
            animal.eat();
        }
    }

}
