/**
 * Created by jakwuh on 9/14/2015.
 */
import java.util.Arrays;

public class Matrix
{
    protected long[][] v;
    protected int n, m;

    public Matrix()
    {
        this(0);
    }

    public Matrix(int n)
    {
        this(n, n);
    }

    public Matrix(int n, int m)
    {
        v = new long[n][m];
        this.n = n;
        this.m = m;
        randomFill();
    }

    public String toString()
    {
        return Arrays.deepToString(v);
    }

    protected void randomFill()
    {
        for (int i = 0; i < v.length; ++i) {
            for (int j = 0; j < v[i].length; ++j) {
                v[i][j] = Math.round(Math.random() * 10);
            }
        }
    }

    public long get(int i, int j)
    {
        return v[i][j];
    }

    public static Matrix multiply(Matrix a, Matrix b)
    {
        Matrix out = new Matrix(a.n, b.m);
        for (int i = 0; i < out.v.length; ++i) {
            for (int j = 0; j < out.v[i].length; ++j) {
                out.v[i][j] = 0;
                for (int k = 0; k < a.m; ++k) {
                    out.v[i][j] += a.get(i, k) * b.get(k, j);
                }
            }
        }
        return out;
    }

}