/**
 * Created by jakwuh on 9/14/2015.
 */
public class SymmetricMatrix extends Matrix{

    public SymmetricMatrix(int n) {
        super();
        v = new long[n][];
        this.n = this.m = n;
        for (int i = 0; i < v.length; ++i) {
            v[i] = new long[i + 1];
        }
        randomFill();
    }

    public long get(int i, int j)
    {
        return v[Math.max(i, j)][Math.min(i,j)];
    }
}
