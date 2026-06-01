import java.util.ArrayList;
import java.util.Comparator;
import java.util.TreeMap;

public class Map3 {
    static void main(String[] args) {
        String source="ahfdjnakcjgslccn";
        TreeMap<String,Integer> wordCount=new TreeMap<>();
        for(char word:source.toCharArray()){
            String key=String.valueOf(word);
            if(wordCount.containsKey(key)){
                wordCount.put(key,wordCount.get(key)+1);
            }else{
                wordCount.put(key,1);
            }
        }
        System.out.println(wordCount);
    }
}
