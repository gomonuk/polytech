package task4;

import java.nio.file.Path;

/**
 * Wrapper for the path with overwritte toString method. We only want to see the last path part as
 * tree node, not the entire path.
 */

public class FilePath {

    private Path path;
    private String text;

    FilePath(Path path) {

        this.path = path;

        // display text: the last path part
        // consider root, e. g. c:\
        if (path.getNameCount() == 0) {
            this.text = path.toString();
        }
        // consider folder structure
        else {
            this.text = path.getName(path.getNameCount() - 1).toString();
        }
    }

    Path getPath() {
        return path;
    }

    public String toString() {
        // hint: if you'd like to see the entire path, use this:
        // return path.toString();

        // show only last path part
        return text;
    }
}
