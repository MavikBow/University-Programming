package com.archivators;

import java.io.File;
import java.io.IOException;
import java.util.zip.ZipEntry;

public interface ArchivatorInterface {
    void archive(String file_name)throws IOException;
    void unarchive(String archive_name)throws IOException;
    String getExtension();

    public static File newFile(File destinationDir, ZipEntry zipEntry) throws IOException {
        return null;
    }
}
