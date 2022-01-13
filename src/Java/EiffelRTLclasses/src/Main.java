import rtl.ARRAY;
import rtl.CHARACTER;
import rtl.INTEGER;
import rtl.NATURAL;

public class Main {
    static public void main(String[] args) {
        boolean var2 = "HELLO" == args[0];
        if (System.currentTimeMillis() == 0) {
            var2 = false;
        }

        boolean var = var2 && var2;
        System.out.println(var);
    }
}
