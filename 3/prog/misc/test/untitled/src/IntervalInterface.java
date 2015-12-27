import javax.activation.UnsupportedDataTypeException;

public interface IntervalInterface<T extends Comparable> extends Cloneable, Comparable<T>{
    public int compareTo(IntervalInterface<?> b);
    public double value();
    public <E> void merge(E b) throws UnsupportedOperationException;
    public void set(T a, T b);
    public Object clone();
}