import java.math.BigDecimal;
import java.math.RoundingMode;
import java.lang.Math.*;

/**
 * Created by jakwuh on 9/9/2015.
 */
public class DeepCopy {

    public static void main(String[] args)
    {
        BigDecimal x = BigDecimal.valueOf(50);
        BigDecimal eps = BigDecimal.valueOf(1e-10);

        int n = 2;
        BigDecimal s = BigDecimal.valueOf(1);
        BigDecimal d = x.pow(2).multiply(BigDecimal.valueOf(-1)).divide(BigDecimal.valueOf(2));

        while (d.abs().compareTo(eps) > 0) {
            n += 2;
            s = s.add(d);
            d = d.multiply(BigDecimal.valueOf(-1)).divide(BigDecimal.valueOf(n * (n - 1)), 100, RoundingMode.HALF_UP).multiply(x.pow(2));
        }

        System.out.println(s);
    }

}
