package rtl;

public class INTEGER extends ANY {
    // ================ ATTRIBUTES ================
    private int _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public INTEGER(int value) { this.SET(value); }

    // ----------------- contract -----------------
    public int  GET()           { return this._value; }
    public void SET(int value)  { this._value = value; }
}
