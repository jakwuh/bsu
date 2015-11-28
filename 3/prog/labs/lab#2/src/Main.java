/**
 * Created by jakwuh on 9/14/2015.
 */
public class Main {

    public static void main(String[] args)
    {
        SymmetricMatrix a = new SymmetricMatrix(3);
        SymmetricMatrix b = new SymmetricMatrix(3);
        Matrix m = Matrix.multiply(a, b);
        System.out.println(a + "\n" + b + "\n" + m + "\n");
    }

}
