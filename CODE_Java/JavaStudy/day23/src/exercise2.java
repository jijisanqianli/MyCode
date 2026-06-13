import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class exercise2 {
    public static void main(String[] args) {
        // 第一个集合：存储6名男演员的名字和年龄
        ArrayList<String> maleActors = new ArrayList<>();
        maleActors.add("吴京,50");
        maleActors.add("刘德华,63");
        maleActors.add("沈腾,45");
        maleActors.add("张雪峰,41");
        maleActors.add("黄晓明,52");
        maleActors.add("张译,46");

        // 第二个集合：存储6名女演员的名字和年龄
        ArrayList<String> femaleActors = new ArrayList<>();
        femaleActors.add("巩俐,59");
        femaleActors.add("章子怡,47");
        femaleActors.add("周迅,50");
        femaleActors.add("赵丽颖,37");
        femaleActors.add("杨幂,38");
        femaleActors.add("杨颖,37");

        Stream<String> male=maleActors.stream()
                .filter(x->x.split(",")[0].length()==3)
                .limit(2);

        Stream<String> female=femaleActors.stream()
                .filter(x->x.split(",")[0].charAt(0)=='杨');

        List<Actor> actor=Stream.concat(male,female)
                .map(x->new Actor(x.split(",")[0],Integer.parseInt(x.split(",")[1])))
                .collect(Collectors.toList());

        /*// 打印男演员信息
        System.out.println("====== 男演员 ======");
        for (String actor : maleActors) {
            String[] info = actor.split(",");
            System.out.println("姓名：" + info[0] + "，年龄：" + info[1]);
        }

        // 打印女演员信息
        System.out.println("\n====== 女演员 ======");
        for (String actor : femaleActors) {
            String[] info = actor.split(",");
            System.out.println("姓名：" + info[0] + "，年龄：" + info[1]);
        }*/
    }
}
