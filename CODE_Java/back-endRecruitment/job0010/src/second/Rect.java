package second;

public class Rect {
    double height;
    double width;

    public Rect(){
        this.height=10;
        this.width=10;
    }

    public Rect(double height,double width){
        this.height=height;
        this.width=width;
    }

    public double area() {
        return height*width;
    }

    public double perimeter() {
        return 2*(height+width);
    }
}
