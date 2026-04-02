package day04;

public class test {
    public static void clear() {
        try {
            // Windows CMD清屏命令
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        } catch (Exception e) {
            System.out.println("清屏失败: " + e.getMessage());
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("=== Windows控制台演示 ===");
        System.out.println("这个程序必须在CMD中运行才能清屏");

        for (int i = 5; i > 0; i--) {
            System.out.println("倒计时: " + i);
            Thread.sleep(1000);
        }

        clear();  // 这会在真正的CMD中清屏

        System.out.println("清屏成功！");
        System.out.println("新内容...");
    }
}
