package day05;

public class gameMain {
    static void main(String[] args) {
        Role r1=new Role("昌吉",100,5);
        Role r2=new Role("猪来",100,6);
        System.out.println("=====游戏开始=====");
        while(true){
            r1.attack(r2);
            if(r2.getRemainBlood()<=0){
                System.out.println(r1.getName()+"获得了胜利！！");
                break;
            }
            r2.attack(r1);
            if(r1.getRemainBlood()<=0){
                System.out.println(r2.getName()+"获得了胜利！！");
                break;
            }
        }
    }
}
