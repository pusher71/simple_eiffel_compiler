package rtl;

public class BOOLEAN extends ANY {
    // ================ ATTRIBUTES ================
    private boolean _value;

    // ================ OPERATIONS ================
    // ----------------- contract -----------------
    public boolean  GET()               { return this._value; }
    public void     SET(boolean value)  { this._value = value; }
}
