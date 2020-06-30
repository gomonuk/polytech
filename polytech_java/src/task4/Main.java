package task4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;

import javafx.scene.control.ContextMenu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.MultipleSelectionModel;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

// Разработать приложение, позволяющее просматривать файлы и каталоги файловой системы,
// а также создавать и удалять текстовые файлы.
// Для работы с текстовыми файлами необходимо реализовать функциональность записи(дозаписи) в файл.
// Требуется определить исключения для каждого слоя приложения и корректно их обработать.


public class Main extends Application {

    private TreeView<FilePath> treeView;
    private final String ROOT_FOLDER = "/home/gomonuk/Programm/34";
    private TextArea editArea;
    private String path;

    private void readText(String file, TextArea localEditArea) {
        String text;
        editArea.clear();

        try (BufferedReader buffReader = new BufferedReader(new FileReader(file))) {
            while ((text = buffReader.readLine()) != null) {
                localEditArea.appendText(text + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String fileNameInputDialog() {
        // https://o7planning.org/ru/11537/javafx-textinputdialog-tutorial
        TextInputDialog dialog = new TextInputDialog("folder/new.txt");
        dialog.setTitle("");
        dialog.setHeaderText("Enter file name name:");
        return dialog.showAndWait().orElse("");
    }

    @Override
    public void start(Stage window) throws IOException {

        // root component
        VBox root = new VBox();

        // treeview
        treeView = new TreeView<FilePath>();
        MyTree myTree = new MyTree(ROOT_FOLDER, treeView );

        VBox.setVgrow(treeView, Priority.ALWAYS);
        ContextMenu treeViewContextMenu = new ContextMenu();
        MenuItem create = new MenuItem("Create");
        MenuItem delete = new MenuItem("Delete");
        treeViewContextMenu.getItems().addAll(create, delete);
        treeView.setContextMenu(treeViewContextMenu);
        create.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                try {
                    File file = new File(ROOT_FOLDER + "/" + fileNameInputDialog());
                    File parent = file.getParentFile();
                    parent.mkdirs();
                    file.createNewFile();
                    myTree.createTree();
                    treeView.setRoot(MyTree.rootTreeItem);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        delete.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                try {
                    File file = new File(ROOT_FOLDER + "/" + fileNameInputDialog());
                    file.delete();
                    myTree.createTree();
                    treeView.setRoot(MyTree.rootTreeItem);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        // filter
        TextField filter = new TextField();
        filter.textProperty()
            .addListener((observable, oldValue, newValue) -> myTree.filterChanged(newValue));

        // contextMenu + editArea
        ContextMenu editAreaContextMenu = new ContextMenu();
        MenuItem save = new MenuItem("Save");
        save.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                try {
                    PrintWriter savedText = new PrintWriter(path);
                    BufferedWriter out = new BufferedWriter(savedText);
                    out.write(editArea.getText());
                    out.close();
                } catch (FileNotFoundException e) {
                    System.out.println("Error: " + e);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        editAreaContextMenu.getItems().add(save);
        editArea = new TextArea();
        editArea.setContextMenu(editAreaContextMenu);
        VBox.setVgrow(editArea, Priority.ALWAYS);

        // Добавляем все контролы
        root.getChildren().addAll(filter, treeView, editArea);

        // stage
        window.setScene(new Scene(root, 1024, 768));
        window.setTitle("Folder Tree View With Filter Example");
        window.show();

        myTree.createTree();

        // show tree structure in tree view
        treeView.setRoot(MyTree.rootTreeItem);

        MultipleSelectionModel<TreeItem<FilePath>> selectionModel = treeView.getSelectionModel();
        selectionModel.setSelectionMode(SelectionMode.SINGLE);
        selectionModel.selectedItemProperty().addListener(
            (ChangeListener<? super TreeItem<FilePath>>) (changed, oldValue, newValue) -> {
                if (newValue != null) {
                    var path_list = new ArrayList<String>();
                    path_list.add(String.valueOf(newValue.getValue()));
                    TreeItem<FilePath> parent = newValue.getParent();
                    while (parent != null) {
                        path_list.add(0, String.valueOf(parent.getValue()));
                        parent = parent.getParent();
                    }
                    path_list.remove(0);
                    path = ROOT_FOLDER + "/" + String.join("/", path_list);
                    if (path.endsWith(".txt")) {
                        editArea.setDisable(false);
                        readText(path, editArea);
                    } else {
                        editArea.setDisable(true);
                        editArea.clear();
                    }
                }
            });
    }

    public static void main(String[] args) {
        launch(args);
    }
}