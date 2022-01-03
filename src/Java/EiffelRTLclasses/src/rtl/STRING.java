package rtl;

public class STRING extends ANY {
    // ================ ATTRIBUTES ================
    private String _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public STRING() { this.SET(""); }

    // ----------------- contract -----------------
    public String   GET()               { return this._value; }
    public void     SET(String value)   { this._value = value; }
}
