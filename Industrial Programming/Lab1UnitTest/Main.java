import java.io.*;
import java.text.NumberFormat;

public class Main
{
    static int k = 0;
    static double x;

    public static void readVariables()
    {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);

        System.out.print("Enter the number: ");

        try
        {
            String line = br.readLine();
            x = Double.parseDouble(line);
        }
        catch (NumberFormatException e)
        {
            System.out.println("not an double");
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

    public static void output(Calculator C)
    {
        NumberFormat formatter = NumberFormat.getNumberInstance();

        formatter.setMaximumFractionDigits(k);
        System.out.print("My method:   ");
        System.out.println(formatter.format(C.calculation()));

        System.out.print("Math method: ");
        System.out.println(formatter.format(Math.sin(x)));
    }

    public static void main(String[] args)
    {
        readVariables();

        Calculator Calc;
        Calc = new Calculator(k, x);

        output(Calc);
    }
}