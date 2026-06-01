public class Student {
    // 属性
    private String name;        // 姓名
    private int age;            // 年龄
    private double chineseScore; // 语文成绩
    private double mathScore;    // 数学成绩
    private double englishScore; // 英语成绩

    // 无参构造
    public Student() {
    }

    // 有参构造
    public Student(String name, int age, double chineseScore, double mathScore, double englishScore) {
        this.name = name;
        this.age = age;
        this.chineseScore = chineseScore;
        this.mathScore = mathScore;
        this.englishScore = englishScore;
    }

    // Getter 和 Setter
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public double getChineseScore() {
        return chineseScore;
    }

    public void setChineseScore(double chineseScore) {
        this.chineseScore = chineseScore;
    }

    public double getMathScore() {
        return mathScore;
    }

    public void setMathScore(double mathScore) {
        this.mathScore = mathScore;
    }

    public double getEnglishScore() {
        return englishScore;
    }

    public void setEnglishScore(double englishScore) {
        this.englishScore = englishScore;
    }

    // 计算总分
    public double getTotalScore() {
        return chineseScore + mathScore + englishScore;
    }

    // 计算平均分
    public double getAverageScore() {
        return getTotalScore() / 3.0;
    }

    // 显示学生信息
    public void displayInfo() {
        System.out.println("========== 学生信息 ==========");
        System.out.println("姓名：" + name);
        System.out.println("年龄：" + age);
        System.out.println("语文成绩：" + chineseScore);
        System.out.println("数学成绩：" + mathScore);
        System.out.println("英语成绩：" + englishScore);
        System.out.println("总分：" + getTotalScore());
        System.out.println("平均分：" + String.format("%.1f", getAverageScore()));
        System.out.println("==============================");
    }

    @Override
    public String toString() {
        return "Student{name='" + name + "', age=" + age +
                ", 语文=" + chineseScore + ", 数学=" + mathScore +
                ", 英语=" + englishScore + ", 总分=" + getTotalScore() + "}";
    }
}
