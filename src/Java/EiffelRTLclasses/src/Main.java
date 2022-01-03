import rtl.NATURAL;

public class Main {
    static public void main(String[] args) {
        long val = 0xFFFFFFFFL;
        System.out.println(val);
        System.out.println(1L << 32);

        NATURAL natural = new NATURAL();
        natural.SET(val);
        System.out.println(natural.GET());
    }
}
