package ui;

import javax.swing.*;

public class Test {
    static void main(String[] args) {
        //JFrame是一个描述界面的javabean类
        //1.创建游戏主界面
        JFrame gameJframe=new JFrame();
        gameJframe.setSize(603,680);//设置界面尺寸
        gameJframe.setVisible(true);//使得界面显示出来
        //2.创建登录界面
        JFrame loginJframe=new JFrame();
        loginJframe.setSize(488,430);//设置界面尺寸
        loginJframe.setVisible(true);
        //3.创建一个注册界面
        JFrame registerJframe=new JFrame();
        registerJframe.setSize(488,500);//设置界面尺寸
        registerJframe.setVisible(true);
    }
}
