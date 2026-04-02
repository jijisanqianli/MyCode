package first;

public class test {
    static void main(String[] args) {
        Rectangle rectangle=new Rectangle(10,5);
        Circle circle=new Circle(5);
        System.out.println("该长方形的面积:"+rectangle.get_area()+" 周长:"+rectangle.get_perimeter());
        System.out.println("该圆形的面积:"+circle.get_area()+" 周长:"+circle.get_perimeter());
    }
}
