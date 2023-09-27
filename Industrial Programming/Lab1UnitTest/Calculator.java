import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.NumberFormat;

public class Calculator
{
    private int k = 0;
    private double x;

    public Calculator(int K, double X)
    {
        k = K;
        x = X;
    }

    private void clampX()
    {
        while (x > Math.PI * 2)
        {
            x -= Math.PI * 2;
        }

        while (x < 0)
        {
            x += Math.PI * 2;
        }
    }

    public double calculation()
    {
        double epsilon = (double)Math.pow(10, -(k + 1));

        clampX();

        double result = 0;
        double addendum = x;
        double denominator = 1;
        int sign = 1;

        while(addendum >= epsilon)
        {
            result += addendum * sign;
            addendum *= x * x;
            addendum /= denominator + 1;
            addendum /= denominator + 2;
            denominator += 2;
            sign *= -1;
        }

        return result;
    }

}
