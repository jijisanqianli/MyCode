public class StudentTest {
    public static void main(String[] args) {
        // 使用有参构造创建学生对象
        Student stu1 = new Student("张三", 18, 90.5, 85.0, 92.0);
        stu1.displayInfo();

        System.out.println();

        // 使用无参构造 + Setter
        Student stu2 = new Student();
        stu2.setName("李四");
        stu2.setAge(19);
        stu2.setChineseScore(78.5);
        stu2.setMathScore(88.0);
        stu2.setEnglishScore(95.5);
        stu2.displayInfo();
    }
}
