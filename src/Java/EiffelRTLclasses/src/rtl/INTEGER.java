package rtl;

public class INTEGER extends ANY {
    // ================ ATTRIBUTES ================
    private long _value;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public INTEGER() { this.SET(0); }

    // ----------------- contract -----------------
    public long GET()           { return this._value; }
    public void SET(long value) {
        if (value < -(1L << 31) || value > (1L << 31) - 1) {
            throw new RuntimeException("INTEGER can store only signed 32-bit integers.");
        }

        this._value = value;
    }
}
