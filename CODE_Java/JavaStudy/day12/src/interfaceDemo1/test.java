package interfaceDemo1;

public class test {
    private int a=10;
    class Inner{
        private int a=20;
        public void show(){
            int a=30;
            System.out.println(test.this.a);
            System.out.println(this.a);
            System.out.println(a);
        }
    } 
}
