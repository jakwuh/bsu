public class IntervalArray<T extends IntervalInterface> implements Cloneable {

    T[] elements;

    public IntervalArray(){}

    @SuppressWarnings("unchecked")
    public IntervalArray(T[] a) {
        if (a.length % 2 != 0) {
            throw new IllegalArgumentException();
        }
        elements = (T[]) new Object[a.length];
        for (int i = 0; i < a.length; i+=2) {
            elements[i / 2].set(a[i], a[i + 1]);
        }
    }

    @SuppressWarnings("unchecked")
    public T longestInterval() throws IllegalAccessException, IllegalArgumentException {
        if (elements.length == 0) {
            throw new IllegalAccessException();
        }
        T current = this.at(0).clone();
        for (T el : elements) current.merge(el);
        return current;
    }

    public int compareLongestInterval(IntervalArray<?> a) throws IllegalAccessException {
        return this.longestInterval().compareTo(a.longestInterval());
    }

    public void setFirstLongestIntervals(IntervalArray<?> a, Pair<IntervalInterface> pair) throws IllegalAccessException {
        if (this.compareLongestInterval(a) > 0) {
            pair.setFirst(this.at(0));
            pair.setFirst(this.longestInterval());
        } else {
            pair.setFirst(a.at(0));
            pair.setSecond(a.longestInterval());
        }
    }

    public T at(int i) throws IllegalArgumentException {
        if (i >= elements.length) {
            throw new IllegalArgumentException();
        }
        return elements[i];
    }

}