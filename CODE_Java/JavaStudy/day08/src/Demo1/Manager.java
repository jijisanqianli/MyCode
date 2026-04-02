package Demo1;

public class Manager extends Worker{
    private double manageSalary;

    public Manager() {
    }

    public Manager(long id, String name, double salary, double manageSalary) {
        super(id, name, salary);
        this.manageSalary = manageSalary;
    }

    @Override
    public void work(){
        super.work();
        System.out.println("管理其他人");
    }

    @Override
    public void eat(){
        super.eat();
        System.out.println("吃米饭");
    }

    /**
     * 获取
     * @return manageSalary
     */
    public double getManageSalary() {
        return manageSalary;
    }

    /**
     * 设置
     * @param manageSalary
     */
    public void setManageSalary(double manageSalary) {
        this.manageSalary = manageSalary;
    }

    public String toString() {
        return "Manager{manageSalary = " + manageSalary + "}";
    }
}
