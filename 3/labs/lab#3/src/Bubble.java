/**
 * Created by jakwuh on 9/14/2015.
 */
public class Bubble {
    boolean nice;
    int length;
    Node n;
    Bubble solution;

    public Bubble()
    {
        nice = false;
        length = 0;
        solution = null;
        n = null;
    }

    public String toString()
    {
        return solution == null ? "" : n.toString();
    }
}
