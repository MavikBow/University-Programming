package com.application;

import com.CyberMan;
import com.archivators.ArchivatorInterface;
import com.archivators.ArchivatorJar;
import com.archivators.ArchivatorZip;

import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.io.File;

public class BackEnd
{
    private static ArchivatorInterface aI;

    public static void processCLI(String filename, String[] flags)
    {
        int argc = 0;
        String[]argv = new String[4];
        argv[argc++] = filename;
        for(String str:flags) argv[argc++] = str;

        String str = process(argc, argv);
    }

    public static String processGUI(Integer argc, String[] argv)
    {
        return process(argc, argv);
    }

    public static String process(Integer argc, String[] argv)
    {
        String filename = argv[0];
        for(int i = 1; i < argc; i++)
        {
            try {
                switch (argv[i]) {
                    case "-z":
                        aI = new ArchivatorZip();
                        aI.archive(filename);
                        filename += ".zip";
                        break;
                    case "-uz":
                        aI = new ArchivatorZip();
                        aI.unarchive(filename);
                        filename = filename.substring(0, filename.length() - 4);
                        break;
                    case "-j":
                        aI = new ArchivatorJar();
                        aI.archive(filename);
                        filename += ".jar";
                        break;
                    case "-uj":
                        aI = new ArchivatorJar();
                        aI.unarchive(filename);
                        filename = filename.substring(0, filename.length() - 4);
                        break;
                    case "-e":
                        CyberMan.encrypt(filename);
                        filename += ".enc";
                        break;
                    case "-d":
                        CyberMan.decrypt(filename);
                        filename = filename.substring(0, filename.length() - 4);
                        break;
                    default:
                }
            } catch (Exception e)
            {
                throw new RuntimeException(e);
            }
        }

        return filename;
    }

    public static Boolean isFile(String fileName)
    {
        File f = new File(fileName);
        return f.exists() && !f.isDirectory();
    }

    private static String helpManual = "Usage: [filename] [command1] [command2](optional)\n" +
            "Commands 1st set:\n" +
            "\t-z\t\tzips the file\n" +
            "\t-j\t\tjars the file\n" +
            "\t-uz\t\tunzips the file\n" +
            "\t-uj\t\tunjars the file\n" +
            "Commands 2nd set:\n" +
            "\t-e\t\tencrypts the file\n" +
            "\t-d\t\tdecrypts the file\n" +
            "You can only use a command of one set once, in whatever order you like.\n" +
            "For example:\n" +
            "\texample.txt -z -e\twould be correct\n" +
            "However:\n" +
            "\texample.txt -z -j\twould be incorrect\n";

    public static void printHelp()
    {
        System.out.println(helpManual);
    }

    public static Boolean validFlags(String[]flags)
    {
        int i = 0;
        int set1 = 0;
        int set2 = 0;
        int setbroken = 0;
        for(String str : flags)
        {
            i++;
        }
        if(i >= 3) return false;

        for(String str: flags)
        {
            switch(str)
            {
                case "-z":
                case "-uz":
                case "-j":
                case "-uj":
                    set1++;
                    break;
                case "-d":
                case "-e":
                    set2++;
                    break;
                case "":
                    break;
                default:
                    setbroken++;
                    break;
            }
        }

        if(setbroken != 0) return false;
        if(set1 > 1 || set2 > 1)return false;
        return true;
    }
}
