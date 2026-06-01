import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Map2 {
    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<>();
        Random r = new Random();
        for (int i = 0; i < 100; i++) {
            int index = r.nextInt(25);
            String location = String.valueOf((char) ('A' + index));
            System.out.println(location);
            list.add(location);
        }
        Map<String,Integer> map=new HashMap<String,Integer>();
        for(String key:list){
            if(map.containsKey(key)){
                map.put(key,map.get(key)+1);
            }else{
                map.put(key,1);
            }
        }
        System.out.println(map);
        int max=0;String maxKey=null;
        for(String key:map.keySet()){
            if(map.get(key)>max){
                max=map.get(key);
                maxKey=key;
            }
        }
        System.out.println(maxKey+":"+max);
    }
}
