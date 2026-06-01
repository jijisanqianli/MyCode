import java.util.Comparator;
import java.util.TreeSet;

public class Test {
    public static void main(String[] args) {
        // 创建 5 个学生对象
        Student s1 = new Student("Wang Xiaoming", 18, 92.5, 88.0, 95.0);
        Student s2 = new Student("Li Xiaohong", 19, 85.0, 93.5, 90.0);
        Student s3 = new Student("Zhang Xiaowei", 17, 78.5, 82.0, 88.5);
        Student s4 = new Student("Zhao Lili", 18, 96.0, 91.0, 97.5);
        Student s5 = new Student("Liu Dazhuang", 19, 65.0, 72.5, 60.0);

        TreeSet<Student> set = new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                if(o1.getTotalScore()!=o2.getTotalScore()) return (int)((o2.getTotalScore()-o1.getTotalScore())*10);
                if(o1.getChineseScore()!=o2.getChineseScore()) return (int)((o2.getChineseScore()-o1.getChineseScore())*10);
                if(o1.getMathScore()!=o2.getMathScore()) return (int)((o2.getMathScore()-o1.getMathScore())*10);
                if(o1.getEnglishScore()!=o2.getEnglishScore()) return (int)((o2.getEnglishScore()-o1.getEnglishScore())*10);
                if(o1.getAge()!=o2.getAge()) return o2.getAge()-o1.getAge();
                if(!o1.getName().equals(o2.getName())) return o2.getName().compareTo(o1.getName());
                return 0;
            }
        });
        set.add(s1);
        set.add(s2);
        set.add(s3);
        set.add(s4);
        set.add(s5);
        System.out.println(set);
    }
}
