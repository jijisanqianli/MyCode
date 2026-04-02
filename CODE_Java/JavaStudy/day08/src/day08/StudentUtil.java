package day08;

import java.util.ArrayList;

public class StudentUtil {
    private StudentUtil(){}

    public static int getBiggestAge (ArrayList<Student> list) {
        int max=0;
        for(int i=0;i<list.size();i++){
            if(max<list.get(i).getAge()){
                max=list.get(i).getAge();
            }
        }
        return max;
    }
}
