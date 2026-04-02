package second;

public class test {
    static void main(String[] args) {
        PlainRect plainRect=new PlainRect(10,10,10,20);
        System.out.println("该长方形的面积:"+plainRect.area()+" 周长:"+plainRect.perimeter());
        System.out.println("点(25.5,13)是否在矩形内:"+plainRect.isInside(25.5,13));
    }
}
