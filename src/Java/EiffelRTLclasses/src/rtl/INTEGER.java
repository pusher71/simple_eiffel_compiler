package rtl;

public class INTEGER extends ANY {
    // ================ ATTRIBUTES ================
    private long _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public INTEGER() { this.SET(0); }

    // ----------------- contract -----------------
    public long GET()           { return this._value; }
    public void SET(long value) { this._value = (int)value; }
}
