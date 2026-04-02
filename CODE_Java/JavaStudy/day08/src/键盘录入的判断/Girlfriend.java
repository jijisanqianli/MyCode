package 键盘录入的判断;

public class Girlfriend {
    private String name;
    private int age;

    public Girlfriend() {
    }

    public Girlfriend(String name, int age) {
        this.name = name;
        this.age = age;
    }

    /**
     * 获取
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * 设置
     * @param name
     */
    public void setName(String name) {
        if(name.length()>10||name.length()<3){
            throw new NameFormatException(name+"：该名字的长度不合理");
        }
        this.name = name;
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
        if(age<18||age>40){
            throw new AgeOutOfBoundException(age+"：该年龄不在合法范围内");
        }
        this.age = age;
    }

    public String toString() {
        return "Girlfriend{name = " + name + ", age = " + age + "}";
    }
}
