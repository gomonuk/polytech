package task5;

// Создать “универсальный” класс, позволяющий получить значение из любого properties-файла.
// Физическое чтение файла должно происходить только один раз.
// Результаты чтения храните в коллекции типа Map.

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Map;
import java.util.Properties;

class PropertyAsMap {

    private Properties property = new Properties();

    Properties getPropertyAsMap(String path_to_file) throws IOException {
        FileInputStream fis = new FileInputStream(path_to_file);
        property.load(fis);
        return property;
//        return (Map<String, String>)property;
    }
}

public class Main {
    public static void main(String[] args) {
        Properties chanksMap = null;
        String path_to_file = "src/task5/resources/spark.properties";
        try {
            chanksMap = new PropertyAsMap().getPropertyAsMap(path_to_file);
        } catch (FileNotFoundException e) {
            System.out.println("Файл не найден");
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (chanksMap instanceof Map){
            System.out.println("Properties наследуется от Hashtable, который имплементится от Map");
        }

        System.out.println(chanksMap);
    }}
