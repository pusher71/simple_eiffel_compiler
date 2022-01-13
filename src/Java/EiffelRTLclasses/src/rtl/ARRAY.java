package rtl;

import java.util.ArrayList;

public class ARRAY extends ANY {
    // ================ ATTRIBUTES ================
    private ArrayList<Object> _elements = new ArrayList();
    private int          _lower = 1;
    private int          _upper = 0;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    public void MAKE_EMPTY() {}

    public void MAKE_FILLED(Object value, long lower, long upper) {
        if ((int)lower != lower) { throw new RuntimeException("Invalid lower index for ARRAY (must be signed 32-bit integer)."); }
        if ((int)upper != upper) { throw new RuntimeException("Invalid upper index for ARRAY (must be signed 32-bit integer)."); }

        this._elements = new ArrayList();
        this._lower = (int)lower;
        this._upper = (int)upper;

        for (int i=this._lower; i<=this._upper; i++) { this._elements.add(value); }
    }

    // ---------------- attributes ----------------
    public long LOWER() { return this._lower; }
    public long UPPER() { return this._upper; }
    public long CAPACITY() { return this._elements.size(); }

    // ----------------- contract -----------------
    public Object GET(long index) {
        if ((int)index != index) { throw new RuntimeException("Invalid index when getting ARRAY element (must be signed 32-bit integer)."); }

        if (index < this._lower || index > this._upper) {
            throw new RuntimeException("Index of array is out of bounds.");
        }

        int realIndex = (int)index - this._lower;
        return this._elements.get(realIndex);
    }
    public void SET(Object elementValue, long index)  {
        if ((int)index != index) { throw new RuntimeException("Invalid index when setting ARRAY element (must be signed 32-bit integer)."); }

        if (index < this._lower || index > this._upper) {
            throw new RuntimeException("Index of array is out of bounds.");
        }

        int realIndex = (int)index - this._lower;
        this._elements.set(realIndex, elementValue);
    }

    public void ADD_FIRST(Object elementValue) {
        this._elements.add(0, elementValue);
        this._upper++;
    }

    public void ADD_LAST(Object elementValue) {
        this._elements.add(elementValue);
        this._upper++;
    }

    public void ADD(Object elementValue, long index) {
        if ((int)index != index) { throw new RuntimeException("Invalid index when setting ARRAY element (must be signed 32-bit integer)."); }

        if (index < this._lower || index > this._upper) {
            throw new RuntimeException("Index of array is out of bounds.");
        }

        int realIndex = (int)index - this._lower;
        this._elements.add(realIndex, elementValue);
        this._upper++;
    }

    public void REMOVE_FIRST() {
        if (this._lower > this._upper) { throw new RuntimeException("Array has no elements to remove"); }

        this._elements.remove(0);
        this._upper--;
    }

    public void REMOVE_LAST() {
        if (this._lower > this._upper) { throw new RuntimeException("Array has no elements to remove"); }

        this._elements.remove(this._elements.size() - 1);
        this._upper--;
    }

    public void REMOVE(long index) {
        if ((int)index != index) { throw new RuntimeException("Invalid index when setting ARRAY element (must be signed 32-bit integer)."); }

        if (index < this._lower || index > this._upper) {
            throw new RuntimeException("Index of array is out of bounds.");
        }

        int realIndex = (int)index - this._lower;
        this._elements.remove(realIndex);
        this._upper--;
    }
}
