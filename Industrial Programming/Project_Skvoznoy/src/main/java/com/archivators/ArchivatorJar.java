package com.archivators;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;
import java.util.jar.JarOutputStream;

public class ArchivatorJar implements ArchivatorInterface {

    @Override
    public void archive(String fileName)throws IOException {
        FileOutputStream fos = new FileOutputStream(fileName + ".jar");
        JarOutputStream jarOut = new JarOutputStream(fos);

        File fileToJar = new File(fileName);
        FileInputStream fis = new FileInputStream(fileToJar);
        JarEntry jarEntry = new JarEntry(fileToJar.getName());
        jarOut.putNextEntry(jarEntry);

        byte[] bytes = new byte[1024];
        int length;
        while((length = fis.read(bytes)) >= 0) {
            jarOut.write(bytes, 0, length);
        }

        jarOut.close();
        fis.close();
        fos.close();
    }

    @Override
    public void unarchive(String jarFile) throws IOException
    {
        byte[] buffer = new byte[1024];
        JarInputStream jis = null;
        FileOutputStream fos = null;
        try {
            jis = new JarInputStream(new FileInputStream(jarFile));
            JarEntry jarEntry = jis.getNextJarEntry();
            while (jarEntry != null) {
                File newFile = new File(jarFile.substring(0, jarFile.length() - 4));
                fos = new FileOutputStream(newFile);
                int len;
                while ((len = jis.read(buffer)) > 0) {
                    fos.write(buffer, 0, len);
                }
                fos.close();
                jarEntry = jis.getNextJarEntry();
            }
            jis.closeEntry();
            jis.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (fos != null) {
                    fos.close();
                }
                if (jis != null) {
                    jis.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public String getExtension(){
        return "jar";
    }

    public static File newFile(File destinationDir, JarEntry jarEntry) throws IOException {
        File destFile = new File(destinationDir, jarEntry.getName());
        String destDirPath = destinationDir.getCanonicalPath();
        String destFilePath = destFile.getCanonicalPath();
        if (!destFilePath.startsWith(destDirPath + File.separator)) {
            throw new IOException("Entry is outside of the target dir: " + jarEntry.getName());
        }
        return destFile;
    }
}