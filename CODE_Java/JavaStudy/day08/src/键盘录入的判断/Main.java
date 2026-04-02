package 键盘录入的判断;

import java.util.Scanner;

public class Main {
    static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        Girlfriend gl=new Girlfriend();
        while (true) {
            try {
                System.out.println("请输入名字：");
                String name=sc.nextLine();
                gl.setName(name);
                System.out.println("请输入年龄：");
                int age=Integer.parseInt(sc.nextLine());
                gl.setAge(age);
                break;
            } catch (NumberFormatException e) {
                System.out.println("请输入正确的数据格式");
            } catch (NameFormatException e){
                e.printStackTrace();
            }catch (AgeOutOfBoundException e){
                e.printStackTrace();
            }
        }
        System.out.println(gl.toString());
    }
}
