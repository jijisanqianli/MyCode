package first;

public class Rectangle implements Perarea{
    double length;
    double width;

    public Rectangle(double length,double width){
        this.length=length;
        this.width=width;
    }

    @Override
    public double get_area() {
        return length*width;
    }

    @Override
    public double get_perimeter() {
        return 2*(length+width);
    }
}
