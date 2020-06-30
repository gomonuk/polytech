package task4;

import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Comparator;
import java.util.function.Function;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;

class MyTree {

    static TreeItem<FilePath> rootTreeItem;
    private static String ROOT_FOLDER;
    private static TreeView<FilePath> treeView;

    MyTree(String root_folder, TreeView<FilePath> tree_view) {
        ROOT_FOLDER = root_folder;
        treeView = tree_view;
    }

    /**
     * Create original tree structure
     */
    void createTree() throws IOException {

        // create root
        rootTreeItem = createTreeRoot();

        // create tree structure recursively
        createTree(rootTreeItem);

        // sort tree structure by name
        rootTreeItem.getChildren()
            .sort(Comparator.comparing(new Function<TreeItem<FilePath>, String>() {
                @Override
                public String apply(TreeItem<FilePath> t) {
                    return t.getValue().toString().toLowerCase();
                }
            }));

    }

    /**
     * Iterate through the directory structure and create a file tree
     */
    private static void createTree(TreeItem<FilePath> rootItem) throws IOException {

        try (DirectoryStream<Path> directoryStream = Files
            .newDirectoryStream(rootItem.getValue().getPath())) {

            for (Path path : directoryStream) {
                TreeItem<FilePath> newItem = new TreeItem<FilePath>(new FilePath(path));
                newItem.setExpanded(true);

                rootItem.getChildren().add(newItem);

                if (Files.isDirectory(path)) {
                    createTree(newItem);
                }
            }
        } catch (AccessDeniedException ignored) {
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Create new filtered tree structure
     */
    private void filter(TreeItem<FilePath> root, String filter, TreeItem<FilePath> filteredRoot) {

        for (TreeItem<FilePath> child : root.getChildren()) {

            TreeItem<FilePath> filteredChild = new TreeItem<>(child.getValue());
            filteredChild.setExpanded(true);

            filter(child, filter, filteredChild);

            if (!filteredChild.getChildren().isEmpty() || isMatch(filteredChild.getValue(),
                filter)) {
                filteredRoot.getChildren().add(filteredChild);
            }

        }
    }

    /**
     * Comparator for tree filter
     */
    private boolean isMatch(FilePath value, String filter) {
        return value.toString().toLowerCase()
            .contains(filter.toLowerCase()); // TODO: optimize or change (check file extension, etc)
    }

    /**
     * Show original tree or filtered tree depending on filter
     */
    void filterChanged(String filter) {
        if (filter.isEmpty()) {
            treeView.setRoot(rootTreeItem);
        } else {
            TreeItem<FilePath> filteredRoot = createTreeRoot();
            filter(rootTreeItem, filter, filteredRoot);
            treeView.setRoot(filteredRoot);
        }
    }

    /**
     * Create root node. Used for the original tree and the filtered tree. Another option would be to
     * clone the root.
     */
    private TreeItem<FilePath> createTreeRoot() {
        TreeItem<FilePath> root = new TreeItem<>(new FilePath(Paths.get(ROOT_FOLDER)));
        root.setExpanded(true);
        return root;
    }
}