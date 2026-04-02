package first;

public class Triangle {
    private double s1;
    private double s2;
    private double s3;

    public double area(){
        if(s1<=0||s2<=0||s3<=0){
            throw new NotTriangle("三角形边长不能为非正数");
        }
        if(s1+s2<=s3||s1+s3<=s2||s2+s3<=s1){
            throw new NotTriangle("任意两边之和需大于第三边，无法构成三角形");
        }
        double s=(s1+s2+s3)/2;
        return Math.sqrt(s*(s-s1)*(s-s2)*(s-s3));
    }

    public static void main(String[] args) {
        Triangle a1=new Triangle(3.0,4.0,5.0);
        Triangle a2=new Triangle(1.0,1.0,2.0);
        test(a1);
        test(a2);
    }

    public static void test(Triangle a){
        try {
            double result=a.area();
            System.out.println(result);
        } catch (NotTriangle e) {
            e.printStackTrace();
        }
    }

    public Triangle() {
    }

    public Triangle(double s1, double s2, double s3) {
        this.s1 = s1;
        this.s2 = s2;
        this.s3 = s3;
    }

    public double getS1() {
        return s1;
    }

    public void setS1(double s1) {
        this.s1 = s1;
    }

    public double getS2() {
        return s2;
    }

    public void setS2(double s2) {
        this.s2 = s2;
    }

    public double getS3() {
        return s3;
    }

    public void setS3(double s3) {
        this.s3 = s3;
    }

    public String toString() {
        return "Triangle{s1 = " + s1 + ", s2 = " + s2 + ", s3 = " + s3 + "}";
    }
}
