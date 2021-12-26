package rtl;

import java.util.ArrayList;
import java.util.Scanner;

public class CONSOLEIO {
    // ================ ATTRIBUTES ================
    private Scanner in;

    public boolean  LAST_BOOLEAN;
    public int      LAST_INTEGER;
    public char     LAST_CHARACTER;
    public String   LAST_STRING;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public CONSOLEIO() {
        this.in = new Scanner(System.in);
    }

    // ----------------- contract -----------------
    public void READ_BOOLEAN()          { this.LAST_BOOLEAN = in.nextBoolean(); }
    public void READ_INTEGER()          { this.LAST_INTEGER = in.nextInt(); }
    public void READ_CHARACTER()        { this.LAST_CHARACTER = (char)in.nextInt(); }
    public void READ_LINE()             { this.LAST_STRING = in.nextLine(); }

    public void PUT_BOOLEAN(boolean v)  { System.out.print(v ? "True" : "False"); }
    public void PUT_INTEGER(int v)      { System.out.print(v); }
    public void PUT_CHARACTER(char v)   { System.out.print((char)v); }
    public void PUT_STRING(String v )   { System.out.print(v); }
    public void NEW_LINE()              { System.out.println(); }
}
