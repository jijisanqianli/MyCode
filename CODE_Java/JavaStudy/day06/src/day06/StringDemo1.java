package day06;

public class StringDemo1 {
    static void main(String[] args) {
        //字符串的比较
        String s1=new String("abc");
        String s2="abc";
        String s3="Abc";
        System.out.println(s1==s2);//比较地址值
        System.out.println(s1.equals(s2));//.equal比较的是字符串内容
        System.out.println((s1.equalsIgnoreCase(s2)));//忽略英文字母大小写
    }
}
