public class Methods {
    public static Student toStudent(String student) {
        Student student0=new Student();
        student0.setName(student.split(",")[0]);
        student0.setAge(Integer.parseInt(student.split(",")[1]));
        return student0;
    }
}
