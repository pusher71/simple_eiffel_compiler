package rtl;

public class NATURAL {
    // ============== STATIC MEMBERS ==============
    static private long _maxValue = (1L << 32);

    // ================ ATTRIBUTES ================
    private long _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public NATURAL() { this.SET(0); }

    // ----------------- contract -----------------
    public long GET()           { return this._value; }
    public void SET(long value) {
        this._value = (value % NATURAL._maxValue);
        if (this._value < 0) { this._value += NATURAL._maxValue; }
    }
}
