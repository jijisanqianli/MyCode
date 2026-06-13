import java.util.ArrayList;
import java.util.Arrays;

public class exercise3 {
    public static void main(String[] args) {
        ArrayList<String> studentString = new ArrayList<>();
        studentString.add("张三,26");
        studentString.add("李四,24");
        studentString.add("王五,25");
        studentString.add("赵六,23");
        Student[] studentsArr=studentString.stream().map(Methods::toStudent).toArray(Student[]::new);
        String[] studentNameArr= Arrays.stream(studentsArr).map(Student::getName).toArray(String[]::new);
        String[] studentStringArr=Arrays.stream(studentsArr).map(Student::toString).toArray(String[]::new);
        System.out.println(studentString);
    }
}
