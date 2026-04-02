package day06;

public class 拼接字符串 {
    static void main(String[] args) {
        int[] arr={9,12,1,56,88};
        /*String result="[";
        for (int i = 0; i < arr.length-1; i++) {
            result+=arr[i];
            result+=",";
        }
        result+=arr[arr.length-1]+"]";
        System.out.println(result);*/
        String result=splice(arr);
        System.out.println(result);
    }

    static String splice(int[] arr) {
        StringBuilder sb=new StringBuilder();
        sb.append('[');
        for (int i = 0; i < arr.length; i++) {
            if(i!= arr.length-1){
                sb.append(arr[i]).append(',');
            }else{
                sb.append(arr[i]).append(']');
            }
        }
        return sb.toString();
    }
}
