import java.util.ArrayList;
import java.util.Map;
import java.util.stream.Collectors;

public class exercise1 {
    public static void main(String[] args) {
        ArrayList<String> people = new ArrayList<>();
        people.add("zhangsan,23");
        people.add("lisi,24");
        people.add("wangwu,25");

        Map<String, Integer> result1 = people.stream()
                .filter(x -> Integer.parseInt(x.split(",")[1]) >= 24)
                .collect(Collectors.toMap(
                        x -> x.split(",")[0],
                        x -> Integer.parseInt(x.split(",")[1])
                ));

        System.out.println(result1);

        Map<String, Integer> result2 = people.stream()
                .map(x->x.split(","))
                .filter(x -> Integer.parseInt(x[1])>=24)
                .collect(Collectors.toMap(
                        x -> x[0],
                        x -> Integer.parseInt(x[1])
                ));
    }
}
