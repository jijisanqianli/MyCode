package day07;

import java.util.ArrayList;
import java.util.Scanner;

public class ArrayListDemo2 {
    static void main(String[] args) {
        ArrayList<Student> list=new ArrayList<>();
        Student s1=new Student("张三",18);
        Student s2=new Student("王五",17);
        Student s3=new Student("李四",19);
        list.add(s1);list.add(s2);list.add(s3);
        Scanner sc=new Scanner(System.in);//输入查询的年龄
        int age=sc.nextInt();
        System.out.println(findPeople(age,list));
    }

    static boolean findPeople(int age,ArrayList<Student> list) {
        for(int i=0;i< list.size();i++){
            if(list.get(i).getAge()==age){
                return true;
            }
        }
        return false;
    }
}
