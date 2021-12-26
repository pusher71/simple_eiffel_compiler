package rtl;

import java.util.ArrayList;

public class ARRAY<T extends ANY> extends ANY {
    // ================ ATTRIBUTES ================
    private ArrayList<T> _elements = new ArrayList();
    private int          _lower;
    private int          _upper;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public ARRAY MAKE_FILLED(T value, int lower, int upper) {
        this._elements = new ArrayList();
        this._lower = lower;
        this._upper = upper;

        for (int i=lower; i<=upper; i++) { this._elements.add(value); }

        return this;
    }

    // ---------------- attributes ----------------
    public int LOWER() { return this._lower; }
    public int UPPER() { return this._upper; }

    public int CAPACITY() { return this._elements.size(); }

    // ----------------- contract -----------------
    public T    GET(int index)                  { return this._elements.get(index - this._lower); }
    public void SET(T elementValue, int index)  { this._elements.set(index - this._lower, elementValue); }
}
