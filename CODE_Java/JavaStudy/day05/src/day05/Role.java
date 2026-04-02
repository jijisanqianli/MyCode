package day05;

import java.util.Random;

public class Role {
    private String name;
    private int blood;
    private int attackPower;
    private int remainBlood;

    public void attack(Role role){
        //this表示方法的调用者
        Random r=new Random();
        int way=r.nextInt(3)+1;
        int damageValue=0;
        int randomValue=0;
        switch (way){
            case 1:
                randomValue=r.nextInt(6)+1;
                damageValue=this.getAttackPower()+randomValue;
                System.out.print(this.getName()+"用拳头揍了一下"+role.getName()+"，造成了"+damageValue+"点伤害,");
                break;
            case 2:
                randomValue=r.nextInt(6)+5;
                damageValue=this.getAttackPower()+randomValue;
                System.out.print(this.getName()+"用脚踢了一下"+role.getName()+"，造成了"+damageValue+"点伤害,");
                break;
            case 3:
                randomValue=r.nextInt(6)+3;
                damageValue=way*this.getAttackPower()+randomValue;
                System.out.print(this.getName()+"狠狠肘击了"+role.getName()+"，造成了"+damageValue+"点伤害,");
                break;
        }
        role.setRemainBlood(role.getRemainBlood()-damageValue);
        if(role.getRemainBlood()>0){
            System.out.println(role.getName()+"还剩下"+role.getRemainBlood()+"点血量");
        }else{
            System.out.println(role.getName()+"血量为0，当场去世！！！");
        }
    }

    public Role() {
    }

    public Role(String name, int blood, int attackPower) {
        this.name = name;
        this.blood = blood;
        this.attackPower = attackPower;
        this.remainBlood=blood;
    }

    /**
     * 获取
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * 设置
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * 获取
     * @return blood
     */
    public int getBlood() {
        return blood;
    }

    /**
     * 设置
     * @param blood
     */
    public void setBlood(int blood) {
        this.blood = blood;
    }

    /**
     * 获取
     * @return attackPower
     */
    public int getAttackPower() {
        return attackPower;
    }

    /**
     * 设置
     * @param attackPower
     */
    public void setAttackPower(int attackPower) {
        this.attackPower = attackPower;
    }

    public int getRemainBlood() {
        return remainBlood;
    }

    public void setRemainBlood(int remainBlood) {
        this.remainBlood = remainBlood;
    }

    public String toString() {
        return "Role{name = " + name + ", blood = " + blood + ", attackPower = " + attackPower + "}";
    }
}
