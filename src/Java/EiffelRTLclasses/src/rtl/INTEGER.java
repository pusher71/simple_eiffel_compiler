package rtl;

public class INTEGER extends ANY {
    // ================ ATTRIBUTES ================
    private int _value;

    // ================ OPERATIONS ================
    // ----------------- contract -----------------
    public int  GET()           { return this._value; }
    public void SET(int value)  { this._value = value; }
}
