package rtl;

public class NATURAL {
    // ================ ATTRIBUTES ================
    private long _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public NATURAL() { this.SET(0); }

    // ----------------- contract -----------------
    public long GET()           { return this._value; }
    public void SET(long value) { this._value = value % (1L << 32); }
}
