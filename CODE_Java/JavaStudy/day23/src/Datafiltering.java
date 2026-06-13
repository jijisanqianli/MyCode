import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Datafiltering {
    public static void main(String[] args) {
        ArrayList<Integer> list = new ArrayList<>();

        for (int i = 1; i <= 10; i++) {
            list.add(i);
        }
        List<Integer> evenList = list.stream()
                .filter(x -> x % 2 == 0)
                .collect(Collectors.toList());

        System.out.println(evenList);
    }
}
