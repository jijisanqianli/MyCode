package 键盘录入的判断;

public class AgeOutOfBoundException extends RuntimeException{
    public AgeOutOfBoundException() {
    }

    public AgeOutOfBoundException(String message) {
        super(message);
    }
}
