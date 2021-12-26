package rtl;

public class CHARACTER extends ANY {
    // ================ ATTRIBUTES ================
    private char _value;

    // ================ OPERATIONS ================
    // ----------------- contract -----------------
    public char GET()           { return this._value; }
    public void SET(char value) { this._value = value; }
}
