package First;

public class Product {
    String name;
    int id;

    public Product() {
    }

    public Product(String name, int id) {
        this.name = name;
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
     * @return id
     */
    public int getId() {
        return id;
    }

    /**
     * 设置
     * @param id
     */
    public void setId(int id) {
        this.id = id;
    }

    public String toString() {
        return "Product{name = " + name + ", id = " + id + "}";
    }
}
