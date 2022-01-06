import rtl.ARRAY;
import rtl.INTEGER;
import rtl.NATURAL;

public class Main {
    static public void main(String[] args) {
        ARRAY array = new ARRAY();
        array.MAKE_FILLED(new INTEGER(), 0, 3);

        boolean var = true;
        if (var) {
            System.out.println("INNER HELLO");
        }

        System.out.println("HELLO");

        /*
        array = null;
        array.GET(0);
        INTEGER val = new INTEGER();
        val.SET(2);
        array.SET(val, 0);

        System.out.println(((INTEGER)array.GET(0)).GET());
         */
    }
}
