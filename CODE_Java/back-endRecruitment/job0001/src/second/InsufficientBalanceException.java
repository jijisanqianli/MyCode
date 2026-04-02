package second;

public class InsufficientBalanceException extends Exception {
    public InsufficientBalanceException(){

    }

    public InsufficientBalanceException(String accountNumber, double amount, double balance) {
        super(String.format("账户 %s 余额不足！当前余额：%.2f，尝试提取：%.2f，差额：%.2f",
                accountNumber, balance, amount, amount - balance));
    }
}

/*public void test(double amount){   //这里是测试函数(取钱)
    if (amount > balance) {
        // 异常对象内部包含账户号码和提取金额
        throw new InsufficientBalanceException(accountNumber, amount, balance);
    }
}
捕获部分
try {
        account.withdraw(800);
} catch (InsufficientBalanceException e) {
        // 异常对象e本身就包含了账户号码、金额等所有信息
        System.out.println(e.getMessage());*/
