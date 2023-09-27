import java.io.*;
import java.util.Scanner;

public class Main
{
    static int M = 0;
    static int N = 0;
    static int[][] Matrix1;

    static int[][]Matrix2;

    public static void inputMatrix1(String filename)throws Exception
    {
        Scanner in = new Scanner(new File (filename));

        M = in.nextInt();
        N = in.nextInt();

        Matrix1 = new int[M][N];

        for(int i = 0; i < M; i ++){
            for(int j = 0; j < N; j++)
            {
                Matrix1[i][j] = in.nextInt();
            }
        }
    }

    public static void inputMatrix2(String filename)throws Exception
    {
        Scanner in = new Scanner(new File (filename));

        M = in.nextInt();
        N = in.nextInt();

        Matrix2 = new int[M][N];

        for(int i = 0; i < M; i ++){
            for(int j = 0; j < N; j++)
            {
                Matrix2[i][j] = in.nextInt();
            }
        }
    }

    private static int columnOfMinOnRowI(int i)
    {
        int sample = Matrix1[i][0];
        int column = 0;

        for(int j = 1; j < N; j++)
        {
            if (Matrix1[i][j] <= sample)
            {
                sample = Matrix1[i][j];
                column = j;
            }
        }

        return column;
    }

    private static int maxElementInRowI(int i)
    {
        int sample = Matrix1[i][0];

        for(int j = 1; j < N; j++)
        {
            if (Matrix1[i][j] >= sample)
            {
                sample = Matrix1[i][j];
            }
        }

        return sample;
    }
    
    public static void Task1()
    {
        try
        {
            inputMatrix1("input1.txt");
        }
        catch (Exception e)
        {
            System.out.println("Task 1 failed, bruh what are you, stupit?");
        }

        boolean go_up, go_down, empty = true;

        for(int j = 0; j < N; j++)
        {
            go_up = true;
            go_down = true;

            for(int i = 1; i < M; i++)
            {
                if (Matrix1[i - 1][j] > Matrix1[i][j]) go_up = false;
                else if (Matrix1[i - 1][j] < Matrix1[i][j]) go_down = false;
            }

            if(go_up | go_down){
                empty = false;
                System.out.print(Integer.toString(j + 1) + " ");
            }
        }

        if(empty) System.out.print("no solution");
        System.out.print('\n');
    }

    public static void Task2()
    {
        try
        {
            inputMatrix1("input2.txt");
        }
        catch (Exception e)
        {
            System.out.println("Task 2 failed, you idiot.");
        }

        boolean valid = true;

        for (int i = 1; i < M; i++)
        {
            if (columnOfMinOnRowI(i - 1) > columnOfMinOnRowI(i))
            {
                valid = false;
            }
        }
        
        if (valid)
        {
            System.out.println("The matrix is valid");
        }
        else
        {
            System.out.println("The matrix is NOT valid");
        }
    }

    public static void Task3()
    {
        try
        {
            inputMatrix1("input3(1).txt");
        }
        catch (Exception e)
        {
            System.out.println("Task 3.1 failed, you idiot.");
        }

        try
        {
            inputMatrix2("input3(2).txt");
        }
        catch (Exception e)
        {
            System.out.println("Task 3.2 failed, you idiot.");
        }

        System.out.println("The new Matrix is:");

        for(int i = 0; i < M; i++)
        {
            int scale = maxElementInRowI(i);
            for(int j = 0; j < N; j++)
            {
                Matrix2[i][j] *= scale;
                System.out.print(Integer.toString(Matrix2[i][j]) + " ");
            }

            System.out.print('\n');
        }
    }

    public static void main(String[] args)
    {
        System.out.println("Task 1 ========");
        Task1();
        System.out.println("Task 2 ========");
        Task2();
        System.out.println("Task 3 ========");
        Task3();
        System.out.println("===============");
    }
}