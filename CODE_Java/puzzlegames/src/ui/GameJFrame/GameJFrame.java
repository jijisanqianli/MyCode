package ui.GameJFrame;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class GameJFrame extends JFrame {
    //游戏主界面

    int count=0;//记录步数

    int[][] right={{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};//正确的结果
    //图片路径
    String type="animal";
    int number=3;
    String mainPath="image\\";
    String branchPath=type+"\\"+type+number+"\\";
    //功能的子菜单
    JMenuItem replayItem=new JMenuItem("重新游戏");
    JMenuItem reLoginItem=new JMenuItem("重新登录");
    JMenuItem closeItem=new JMenuItem("关闭游戏");
    //关于我们的子菜单
    JMenuItem accountItem=new JMenuItem("作者信息");
    //更换图片的子菜单
    JMenuItem beauty=new JMenuItem("美女");
    JMenuItem animal=new JMenuItem("动物");
    JMenuItem sport=new JMenuItem("运动");

    int[][] list=new int[4][4];

    //记录空格所在数组中位置
    int x16,y16;

    public GameJFrame(){
        initJFrame();
        initJMenuBar();
        //初始化图片
        initImage();
        //添加键盘的监听
        this.addKeyListener(new MyKeyboardListener(this));

        this.setVisible(true);
    }

    public void moveDown(){
        if(x16!=0){
            list[x16][y16]=list[x16-1][y16];
            list[x16-1][y16]=16;
            x16=x16-1;
            count++;
            showPicture();
        }
    }

    public void moveUp(){
        if(x16!=3){
            list[x16][y16]=list[x16+1][y16];
            list[x16+1][y16]=16;
            x16=x16+1;
            count++;
            showPicture();
        }
    }

    public void moveLeft(){
        if(y16!=3){
            list[x16][y16]=list[x16][y16+1];
            list[x16][y16+1]=16;
            y16=y16+1;
            count++;
            showPicture();
        }
    }

    public void moveRight(){
        if(y16!=0){
            list[x16][y16]=list[x16][y16-1];
            list[x16][y16-1]=16;
            y16=y16-1;
            count++;
            showPicture();
        }
    }

    private void initImage() {
        //初始化图片
        //取消图片默认位置
        this.getContentPane().setLayout(null);
        //获得图片编号
        int[] tempArr={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        //将图片顺序打乱
        disrupt(tempArr);
        //放入二维数组之中
        int num=0;//填入数字的工具
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                list[i][j]=tempArr[num];
                num++;
            }
        }
        showPicture();
    }

    public void showAllPicture(){
        this.getContentPane().removeAll();//删除目前图片
        JLabel all=new JLabel(new ImageIcon(mainPath+branchPath+"all.jpg"));
        all.setBounds(83,134,420,420);
        this.getContentPane().add(all);
        JLabel backGround=new JLabel(new ImageIcon("D:\\code\\CODE_Java\\puzzlegames\\image\\background.png"));
        backGround.setBounds(40,40,508,560);

        this.getContentPane().add(backGround);
        this.getContentPane().repaint();
    }

    public void showPicture() {//展示拼图
        this.getContentPane().removeAll();
        judgeWin();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if(list[i][j]==16){
                    x16=i;y16=j;
                }
                //创建一个图片ImageIcon的对象
                ImageIcon icon=new ImageIcon(mainPath+branchPath+list[i][j]+".jpg");
                //创建一个JLabel的对象(管理容器)
                JLabel jLabel=new JLabel(icon);
                //指定位置
                jLabel.setBounds(105*j+83,105*i+134,105,105);
                //设置边框
                jLabel.setBorder(new BevelBorder(BevelBorder.LOWERED));
                //把管理容器添加到界面中
                this.add(jLabel);
            }
        }
        //添加背景
        JLabel backGround=new JLabel(new ImageIcon("D:\\code\\CODE_Java\\puzzlegames\\image\\background.png"));
        backGround.setBounds(40,40,508,560);
        this.getContentPane().add(backGround);
        //添加计数器
        JLabel counter=new JLabel("步数:"+count);
        counter.setBounds(50,30,100,20);
        this.getContentPane().add(counter);
        //重绘画面
        this.getContentPane().repaint();
        /*ImageIcon icon=new ImageIcon("D:\\code\\CODE_Java\\puzzlegames\\image\\animal\\animal3\\1.jpg");
        //创建一个JLabel的对象(管理容器)
        JLabel jLabel=new JLabel(icon);
        //指定位置
        jLabel.setBounds(0,0,105,105);
        this.getContentPane().setLayout(null);
        //把管理容器添加到界面中
        this.add(jLabel);*/
    }

    private static void disrupt(int[] tempArr) {
        Random r=new Random();
        for (int i = tempArr.length-1; i > 0 ; i--) {
            int j=r.nextInt(i+1);
            int middle= tempArr[j];
            tempArr[j]= tempArr[i];
            tempArr[i]=middle;
        }
    }

    public void cheat(){
        int count=1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                list[i][j] = count;
                count++;
            }
        }
        showPicture();
    }

    private void initJMenuBar() {
        // 初始化菜单
        // 创建整个的菜单对象
        JMenuBar jMenuBar=new JMenuBar();
        JMenu functionJmenu=new JMenu("功能");
        JMenu aboutJMenu=new JMenu("关于作者");
        //功能的子菜单
        JMenu changeIconItem=new JMenu("更换图片");
        //添加item
        functionJmenu.add(changeIconItem);
        functionJmenu.add(replayItem);
        functionJmenu.add(reLoginItem);
        functionJmenu.add(closeItem);
        aboutJMenu.add(accountItem);
        //添加Jmenu
        jMenuBar.add(functionJmenu);
        jMenuBar.add(aboutJMenu);
        //为更换图片添加子菜单
        changeIconItem.add(beauty);
        changeIconItem.add(animal);
        changeIconItem.add(sport);
        //为更换图片绑定事件
        beauty.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                type="girl";
                Random r=new Random();
                number=r.nextInt(11)+1;
                branchPath=type+"\\"+type+number+"\\";
                initImage();
            }
        });
        animal.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                type="animal";
                Random r=new Random();
                number=r.nextInt(8)+1;
                branchPath=type+"\\"+type+number+"\\";
                initImage();
            }
        });
        sport.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                type="sport";
                Random r=new Random();
                number=r.nextInt(10)+1;
                branchPath=type+"\\"+type+number+"\\";
                initImage();
            }
        });
        //给选项jmenumitem绑定事件
        replayItem.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("重新游戏");
                restart();
            }
        });
        reLoginItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("重新登录");
            }
        });
        closeItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("关闭游戏");
                System.exit(0);
            }
        });
        accountItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("作者信息");
                //创建弹框
                JDialog jDialog=new JDialog();
                //设置标题
                jDialog.setTitle("作者信息");
                //给弹框设置大小
                jDialog.setSize(344,344);
                //让弹框置顶
                jDialog.setAlwaysOnTop(true);
                //让弹框居中
                jDialog.setLocationRelativeTo(null);
                //弹框不关闭无法进行其他操作
                jDialog.setModal(true);
                JLabel myInformation=new JLabel(new ImageIcon("image\\MyInformaiton.png"));
                myInformation.setBounds(0,0,258,258);
                jDialog.getContentPane().add(myInformation);
                //显示弹框
                jDialog.setVisible(true);
            }
        });
        //给整个界面设置菜单
        this.setJMenuBar(jMenuBar);
    }

    public boolean judgeWin(){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if(list[i][j]!=right[i][j]){
                    return false;
                }
            }
        }
        JLabel win=new JLabel(new ImageIcon("D:\\code\\CODE_Java\\puzzlegames\\image\\win.png"));
        win.setBounds(203,283,197,73);
        this.getContentPane().add(win);
        this.getContentPane().repaint();
        return true;
    }

    public void restart(){
        count=0;//计数器归零
        initImage();//
    }

    private void initJFrame() {
        this.setSize(603,680);//设置界面尺寸
        this.setTitle("拼图单机版 v1.0");
        this.setAlwaysOnTop(true);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
}
