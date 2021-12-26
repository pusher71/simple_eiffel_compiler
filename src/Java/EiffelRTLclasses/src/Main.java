import rtl.INTEGER;

public class Main {
    static Object var;

    static public void main(String[] args) {
        var = new INTEGER(0);
        System.out.println(((INTEGER)var).GET());
    }
}
