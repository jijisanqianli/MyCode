package ui.GameJFrame;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MyKeyboardListener implements KeyListener {

    private GameJFrame game;

    //构造方法
    public MyKeyboardListener(GameJFrame game){
        //引用，这里保存的是地址值
        this.game=game;
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override//按住不松时触发
    public void keyPressed(KeyEvent e) {
        int code=e.getKeyCode();
        if(code==66){   //为B时
            game.showAllPicture();
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        if(game.judgeWin()==true){
            return;
        }
        int code=e.getKeyCode();
        System.out.println(code);
        if(code==87||code==38){//上移
            game.moveUp();
            System.out.println("向上移动");
        }else if(code==65||code==37){
            game.moveLeft();
            System.out.println("向左移动");
        }else if(code==83||code==40){
            game.moveDown();
            System.out.println("向下移动");
        }else if(code==68||code==39){
            game.moveRight();
            System.out.println("向右移动");
        }else if(code==66){
            game.showPicture();
        }else if(code==86){//按v键
            game.cheat();
        }
    }
}
