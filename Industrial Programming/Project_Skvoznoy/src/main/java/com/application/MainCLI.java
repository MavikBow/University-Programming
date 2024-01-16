package com.application;

import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

public class MainCLI
{
    public static String filename = "";
    public static Boolean help = false;
    public static Boolean exit = false;
    public static String[] words;

    public static void takeInput()
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the filename:");
        filename = scanner.nextLine();

        if(Objects.equals(filename, "--help"))
        {
            help = true;
            return;
        }

        if(BackEnd.isFile(filename))
        {
            System.out.println("Input flags:");

            String inputString = scanner.nextLine();
            words = inputString.split("\\s+");
        }
        else
        {
            exit = true;
            System.out.println("Such file doesn't exist or wasn't found");
        }
    }

    public static void main(String[] args)
    {
        System.out.println("--------------------------------");
        takeInput();
        if(help)
        {
            BackEnd.printHelp();
        }
        else
        {
            if(!exit)
            {
                if (BackEnd.validFlags(words))
                {
                    BackEnd.processCLI(filename, words);
                }
                else
                {
                    System.out.println("Incorrect flags. Type --help for help");
                }
            }
        }
        System.out.println("--------------------------------");
    }
}
