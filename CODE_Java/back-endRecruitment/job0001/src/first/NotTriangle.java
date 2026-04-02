package first;

public class NotTriangle extends RuntimeException{
    public NotTriangle() {
    }

    public NotTriangle(String message) {
        super(message);
    }
}
