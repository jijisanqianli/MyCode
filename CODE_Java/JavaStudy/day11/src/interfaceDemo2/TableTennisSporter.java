package interfaceDemo2;

public class TableTennisSporter extends Sporters implements English{

    @Override
    public void learn() {
        System.out.println("学打乒乓球");
    }

    @Override
    public void speakEnglish() {
        System.out.println("说英语");
    }
}
