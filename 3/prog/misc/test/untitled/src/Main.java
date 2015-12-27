abstract class Interval<T extends Comparable> implements IntervalInterface<T> {

    protected T l, r;

    public Interval(T a, T b) {
        set(a, b);
    }

    public int compareTo(IntervalInterface<?> b) {
        if (this.value() > b.value()) {
            return 1;
        } else if (this.value() < b.value()) {
            return -1;
        } else {
            return 0;
        }
    }

    @Override
    public Object clone() {
        try {
            return super.clone();
        } catch (CloneNotSupportedException e) {
            System.out.println("Cloning not allowed.");
            return this;
        }
    }

    public <E> void merge(E b) throws UnsupportedOperationException {
        if (!(b instanceof Interval)) {
            throw new UnsupportedOperationException();
        }
        Interval<T> bi = (Interval<T>)b;
        this.l = (l.compareTo(bi.l) < 0 ? l : bi.l);
        this.r = (r.compareTo(bi.r) > 0 ? r : bi.r);
    }

    public void set(T a, T b) {
        if (a.compareTo(b) > 0) {
            l = b;
            r = a;
        } else {
            l = a;
            r = b;
        }
    }

    public String toString() {
        return "[" + this.value() + "]";
    }
}

class DoubleInterval extends Interval<Double> {
    public double value() {
        return r - l;
    }
}

class IntegerInterval extends Interval<Integer> {
    public double value() {
        return (double)(r - l);
    }
}

public class Main {
    public static void main(String[] args) {
        try {
            DoubleInterval[] da = new DoubleInterval[]{new DoubleInterval(1., 2.)};
            IntegerInterval[] ia = new IntegerInterval[]{new IntegerInterval(1, 2)};
            IntervalArray<DoubleInterval> DA = new IntervalArray<DoubleInterval>(da);
            IntervalArray<IntegerInterval> IA = new IntervalArray<IntegerInterval>(ia);
            System.out.println(IA.longestInterval());
            System.out.println(DA.longestInterval());
        } catch (IllegalAccessException e) {
            System.out.println("Illegal access");
        } catch (IllegalArgumentException e) {
            System.out.println("Illegal argument");
        }
    }
}