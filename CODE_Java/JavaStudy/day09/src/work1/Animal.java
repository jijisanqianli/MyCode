package work1;

import java.util.Objects;

public class Animal {
    private int age;
    private String color;

    public String getType(){
        return "动物";
    }

    public void eat(String something){
        System.out.println("吃"+something);
    }

    public Animal() {
    }

    public Animal(int age, String color) {
        this.age = age;
        this.color = color;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Animal animal = (Animal) o;
        return age == animal.age && Objects.equals(color, animal.color);
    }

    @Override
    public int hashCode() {
        return Objects.hash(age, color);
    }

    /**
     * 获取
     * @return age
     */
    public int getAge() {
        return age;
    }

    /**
     * 设置
     * @param age
     */
    public void setAge(int age) {
        this.age = age;
    }

    /**
     * 获取
     * @return color
     */
    public String getColor() {
        return color;
    }

    /**
     * 设置
     * @param color
     */
    public void setColor(String color) {
        this.color = color;
    }

    public String toString() {
        return "Animal{age = " + age + ", color = " + color + "}";
    }
}
