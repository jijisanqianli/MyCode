import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class Map1 {
    public static void main(String[] args) {
        //1.创建Map集合的对象
        Map<String, String> map = new HashMap<>();

        //2.添加元素
        map.put("尹志平", "小龙女");
        map.put("郭靖", "穆念慈");
        map.put("欧阳克", "黄蓉");

        Set<String> keys = map.keySet();
//        for (String key : keys) {
//            String value = map.get(key);
//            System.out.println(key + ": " + value);
//        }
//        Iterator<String> it = keys.iterator();
//        while (it.hasNext()) {
//            String key = it.next();
//            String value = map.get(key);
//            System.out.println(key + ":" + value);
//        }
        keys.forEach(key -> {
            System.out.println(key+":"+map.get(key));
        });
        //System.out.println(map);
    }
}
