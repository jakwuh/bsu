import java.lang.Math.*;
import java.util.*;

/**
 * Created by jakwuh on 9/7/2015.
 */
public class Math {

    final static int J_LOW = 2;
    final static int I_LOW = 2;

    private static double[] fillX(int n, double x)
    {
        double[] row = new double[n + 1];
        row[J_LOW] =java.lang.Math.pow(x, J_LOW * 2 + 1);
        for (int j = n; j > n - J_LOW; --j) {
            row[J_LOW] /= j;
        }
        for (int j = J_LOW; j < n; ++j) {
            row[j + 1] = row[j] * x * x / (n - j);
        }
        return row;
    }

    private static double calc(int n, double x)
    {
        double p = 1;
        double[] row = Math.fillX(n, x);
        for (int i = J_LOW; i <= I_LOW; ++i) {
            p *= row[i];
        }
        double s = p;
        for (int i = I_LOW + 1; i <= n; ++i) {
            p *= row[i];
            s += p;
        }
        return s;
    }

    private static double verify(int n, double x)
    {
        int[][] a = {{1,2},{1,2}};
        double r = java.lang.Math.pow(x, 5) / (n * (n - 1));
        double p = r;
        double s = p;
        for (int i = 3; i <= n; ++i) {
            r *= x * x / (n - i +  1);
            p *= r;
            s += p;
        }
        return s;
    }

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter n:");
        int n = in.nextInt();
        System.out.println("Enter x:");
        double x = in.nextDouble();
        System.out.println("The sum is " + calc(n, x));
        System.out.println("The verifying sum is " + verify(n, x));
    }

}
