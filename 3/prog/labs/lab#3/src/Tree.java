/**
 * Created by jakwuh on 9/14/2015.
 */
public class Tree {

    Node root;

    public Tree() {
    }

    public void insert(long x) {
        if (root == null) root = new Node(x);
        else root.attach(new Node(x));
    }

    public void insert(long[] x) {
        for (long i : x) insert(i);
    }

    public Bubble solve() {
        return root == null ? null : root.solve();
    }

    public static void main(String[] args) {
        Tree t = new Tree();
        t.insert(new long[]{20});
        System.out.println(t.solve());
    }

}
