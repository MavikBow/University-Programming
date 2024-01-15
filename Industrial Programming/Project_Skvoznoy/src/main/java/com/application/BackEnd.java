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
}
