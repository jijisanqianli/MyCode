package Demo1;

public class Worker {
    private long id;
    private String name;
    private double salary;

    public void work(){
        System.out.println("工作");
    }

    public void eat(){
        System.out.println("吃饭");
    }

    public Worker() {
    }

    public Worker(long id, String name, double salary) {
        this.id = id;
        this.name = name;
        this.salary = salary;
    }

    /**
     * 获取
     * @return id
     */
    public long getId() {
        return id;
    }

    /**
     * 设置
     * @param id
     */
    public void setId(long id) {
        this.id = id;
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
        this.name = name;
    }

    /**
     * 获取
     * @return salary
     */
    public double getSalary() {
        return salary;
    }

    /**
     * 设置
     * @param salary
     */
    public void setSalary(double salary) {
        this.salary = salary;
    }

    public String toString() {
        return "Worker{id = " + id + ", name = " + name + ", salary = " + salary + "}";
    }
}
