import java.io.*;
import java.text.*;

public class Main
{
    private static char ch;
    private static int number;
    private static String[] text = new String[13];

    private static void readInputs()
    {
        InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);

        System.out.print("Input the char you want to remove/add: ");

        try
        {
            String line = br.readLine();
            ch = line.charAt(0);
        }
        catch (NumberFormatException e)
        {
            System.out.println("not a proper char");
        }
        catch (IOException e)
        {
            System.out.println("trouble reading from keyboard");
        }
    
        System.out.print("Input the number after which you want to add the char: ");

        try
        {
            String line = br.readLine();
            number = Integer.parseInt(line);
        }
        catch (NumberFormatException e)
        {
            System.out.println("not a proper int");
        }
        catch (IOException e)
        {
            System.out.println("trouble reading from keyboard");
        }

        try
        {
        InputStream is = new FileInputStream("input.txt");
        isr = new InputStreamReader(is);
		br = new BufferedReader(isr);

        for(int i = 0; i < 13; i++)
        {
            text[i] = br.readLine();
        }
        
        br.close();
        }
        catch (IOException e)
        {
            System.out.println("trouble reading the file");
        }       
    }

    private static void Task1()
    {
        try
        {
            OutputStream os = new FileOutputStream("output(0).txt");
            OutputStreamWriter osr = new OutputStreamWriter(os);
		    BufferedWriter bw = new BufferedWriter(osr);

            for(int i = 0; i < 12; i++)
            {
                bw.write(text[i].replaceAll(Character.toString(ch), "") + '\n');
            }

            bw.close();
            osr.close();
            os.close();
        }
        catch (IOException e)
        {
            System.out.println("trouble opening the output(0).txt file");
        }
    }

    private static void Task2()
    {
        try
        {
            OutputStream os = new FileOutputStream("output(1).txt");
            OutputStreamWriter osr = new OutputStreamWriter(os);
		    BufferedWriter bw = new BufferedWriter(osr);

            int tempNumb = number;

            for(int i = 0; i < 12; i++)
            {
                if(number > text[i].length())
                {
                    tempNumb = text[i].length();
                }
                bw.write(text[i].substring(0, tempNumb) + ch + text[i].substring(tempNumb) + '\n');
            }

            bw.close();
            osr.close();
            os.close();
        }
        catch (IOException e)
        {
            System.out.println("trouble opening the output(0).txt file");
        }
    }

    public static void main(String[] args)
    {
        readInputs();

        System.out.println("Case 0:");
        Task1();
        System.out.println("Case 1:");
        Task2();
    }
}