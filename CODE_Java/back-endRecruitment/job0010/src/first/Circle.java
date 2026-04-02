package first;

public class Circle implements Perarea{
    double r;

    public Circle(double r){
        this.r=r;
    }

    @Override
    public double get_area() {
        return Math.PI*r*r;
    }

    @Override
    public double get_perimeter() {
        return Math.PI*2*r;
    }
}
