package rtl;

public class NATURAL {
    // ================ ATTRIBUTES ================
    private long _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public NATURAL() { this.SET(0); }

    // ----------------- contract -----------------
    public long GET()           { return this._value; }
    public void SET(long value) {
        if (value < 0L || value > (1L << 32) - 1) {
            throw new RuntimeException("NATURAL can store only unsigned 32-bit integers.");
        }

        this._value = value;
    }
}
