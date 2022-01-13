import rtl.ARRAY;
import rtl.CHARACTER;
import rtl.INTEGER;
import rtl.NATURAL;

public class Main {
    static public void main(String[] args) {
        ARRAY chars = new ARRAY();

        chars.ADD_FIRST(new CHARACTER());
        chars.ADD_FIRST(new CHARACTER());
        chars.ADD_FIRST(new CHARACTER());

        ((CHARACTER)chars.GET(1)).SET('a');
        ((CHARACTER)chars.GET(2)).SET('b');
        ((CHARACTER)chars.GET(3)).SET('c');

        chars.REMOVE_LAST();
        chars.REMOVE_FIRST();

        for (int i=(int)chars.LOWER(); i<=chars.UPPER(); i++) {
            System.out.println(i + ": " + ((CHARACTER)chars.GET(i)).GET());
        }
    }
}
