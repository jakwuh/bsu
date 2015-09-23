/**
 * Created by jakwuh on 9/14/2015.
 */
public class Node {
    Node left, right;
    long v;

    public Node(long n)
    {
        v = n;
    }

    public void attach(Node n)
    {
        if (n.v < v) {
            if (left == null) left = n;
            else left.attach(n);
        } else {
            if (right == null) right = n;
            else right.attach(n);
        }
    }

    public String toString() {
        return "" + v;
    }

    public Bubble solve()
    {
        Bubble b = new Bubble(), lb = null, rb = null;
        b.length = 1;
        long maxl = 0;
        if (left != null) {
            lb = left.solve();
            maxl = lb.length;
        }
        if (right != null) {
            rb = right.solve();
            if (rb.length > maxl) maxl = rb.length;
        }
        b.length += maxl;

        if ((lb == null && rb == null) ||
                (lb != null && rb == null && lb.nice) ||
                (lb != null && rb != null && lb.nice && rb.nice && lb.length > rb.length)) {
            b.nice = true;
            b.solution = b;
            b.n = this;
        } else {
            b.nice = false;
            if (lb != null && lb.solution != null) {
                b.solution = lb.solution;
                b.n = lb.n;
            }
            if (rb != null && (b.solution != null && rb.length > b.solution.length) || b.solution == null) {
                b.solution = rb.solution;
                b.n = rb.n;
            }
        }

        System.out.println("value=" + this + "|length=" + b.length + "|solution=" + b.solution);
        return b;
    }
}
