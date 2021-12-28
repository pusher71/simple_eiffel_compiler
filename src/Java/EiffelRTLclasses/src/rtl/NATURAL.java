package rtl;

public class NATURAL extends ANY {
    // ================ ATTRIBUTES ================
    private long _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public NATURAL() { this.SET(0); }
    public NATURAL(long value) { this.SET(value); }

    // ----------------- contract -----------------
    public long GET()           { return this._value; }
    public void SET(long value) {
        this._value = (value >= 0 ? value : Integer.MAX_VALUE + value);
    }
}
