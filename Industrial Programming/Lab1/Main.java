import java.io.*;
import java.text.NumberFormat;

public class Main
{
    static int k = 0;
    static double result = 0;
    static float x;

    public static void readVariables()
    {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);

        System.out.print("Enter the number: ");

        try
        {
            String line = br.readLine();
            x = Float.parseFloat(line);
        }
        catch (NumberFormatException e)
        {
            System.out.println("not an float");
        }
        catch (IOException e)
        {
            System.out.println("trouble reading from keyboard");
        }
        
        System.out.print("Enter precision: ");

        try
        {
            String line = br.readLine();
            k = Integer.parseInt(line);
        }
        catch (NumberFormatException e)
        {
            System.out.println("not an int");
        }
        catch (IOException e)
        {
            System.out.println("trouble reading from keyboard");
        }
    }

    public static void clampX()
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

    public static double calculation()
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

    public static void output()
    {
        NumberFormat formatter = NumberFormat.getNumberInstance();

        formatter.setMaximumFractionDigits(k);
        System.out.print("My method:   ");
        System.out.println(formatter.format(calculation()));

        System.out.print("Math method: ");
        System.out.println(formatter.format(Math.sin(x)));
    }

    public static void main(String[] args)
    {
        readVariables();
        output();
    }
}