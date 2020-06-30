package task2;


// Описать 4 класса (базовый и 3 потомка), описывающих некоторых хищных животных (один из потомков),
// всеядных (второй потомок) и травоядных (третий потомок).
// Определить в базовом классе абстрактный метод для расчета количества и типа пищи,
// необходимого для пропитания животного в зоопарке. Затем:
// a.Упорядочить всю последовательность животных по убыванию количества пищи.
//   При совпадении значений – упорядочивать данные по алфавиту по имени.
//   Вывести идентификатор животного, имя, тип и количество потребляемой пищи для всех элементов списка.
// b.Вывести первые 5 имен животных из полученного в пункте а) списка.
// c.Вывести последние 3 идентификатора животных из полученного в пункте а) списка.
// d.Организовать запись и чтение коллекции в/из файл.
// e.Организовать обработку некорректного формата входного файла.


import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;

abstract class Animal implements Serializable {
    private static int last_id;
    int id;
    private boolean isHerbivore;
    private boolean isPredator;
    double weight;
    private String name;
    private static final long serialVersionUID = 1L;

    Animal(String name, boolean isHerbivore,  boolean isPredator, double weight){
        this.isPredator = isPredator;
        this.isHerbivore = isHerbivore;
        this.weight = weight;
        this.name = name;

    }

    protected abstract double foodCalculate();

    void printAllInfo() {
        System.out.printf("Animal ID: %d Name: %s Type: %s Food Consumed: %.1f\n" , this.id, this.name, this.getType(), this.foodCalculate());
    }

    private String getType(){
        if (this.isHerbivore & this.isPredator) {
            return "Omnivore";
        } else {
            if (this.isPredator) {
                return "Predator";
            } else {
                return "Herbivore";
            }
        }
    }

    static int getLastId() {
        last_id = last_id + 1;
        return last_id;
    }

    double roundTwo(double a){
        return Math.round(a * 100.0) / 100.0;
    }

    static Comparator<Animal> AnimalComparator = new Comparator<Animal>() {

        @Override
        public int compare(Animal animal, Animal t1) {
            int compareResult = 0;

            if (animal.foodCalculate() > t1.foodCalculate()){
                compareResult = -1;
            }

            if (animal.foodCalculate() < t1.foodCalculate()){
                compareResult = 1;
            }

            if (compareResult != 0){
                return compareResult;
            }

            return animal.name.compareTo(t1.name);
        }
    };
}

class Predator extends Animal {
    Predator(String name, boolean isHerbivore, boolean isPredator, double weight) {
        super(name, isHerbivore, isPredator, weight);
        this.id = getLastId();
    }

    @Override
    protected double foodCalculate() {
        return roundTwo(this.weight * 2);
    }
}

class Herbivore extends Animal{
    Herbivore(String name, boolean isHerbivore, boolean isPredator, double weight) {
        super(name, isHerbivore, isPredator, weight);
        this.id = getLastId();
    }

    @Override
    protected double foodCalculate() {
        return roundTwo(this.weight * 0.7);
    }
}

class Omnivore extends Animal{
    Omnivore (String name, boolean isHerbivore, boolean isPredator, double weight) {
        super(name, isHerbivore, isPredator, weight);
        this.id = getLastId();
    }

    @Override
    protected double foodCalculate() {
        return roundTwo(this.weight * 0.5);
    }
}



public class Main {
    private static final String FILE_TO_SERIALIZETION = "animals.ser";
    private static void writeObject(ArrayList<Animal> listAnimal) throws IOException {
        //Create FileOutputStream to write file
        FileOutputStream fos = new FileOutputStream(FILE_TO_SERIALIZETION);
        //Create ObjectOutputStream to write object
        ObjectOutputStream objOutputStream = new ObjectOutputStream(fos);
        //Write object to file
        for (Object obj : listAnimal) {
            objOutputStream.writeObject(obj);
            objOutputStream.reset();
        }
        objOutputStream.close();
    }

    private static ArrayList<Animal> readObject() throws ClassNotFoundException, IOException {
        ArrayList<Animal> listAnimal = new ArrayList();
        //Create new FileInputStream object to read file
        FileInputStream fis = new FileInputStream(FILE_TO_SERIALIZETION);
        //Create new ObjectInputStream object to read object from file
        ObjectInputStream obj = new ObjectInputStream(fis);
        try {
            while (fis.available() != -1) {
                //Read object from file
                Animal acc = (Animal) obj.readObject();
                listAnimal.add(acc);
            }
        } catch (EOFException ex) {
//            ex.printStackTrace();
        }
        return listAnimal;
    }


    public static void main(String[] args){
        // https://stackoverflow.com/questions/8307982/serializing-a-list-of-objects-into-a-file-in-java

        ArrayList<Animal> animalList = new ArrayList<>();
        animalList.add(new Predator("cat", false, true, 3.4));
        animalList.add(new Predator("tiger", false, true, 130.4));
        animalList.add(new Herbivore("hamster", true, false, 0.4));
        animalList.add(new Herbivore("rabbit", true, false, 1.4));
        animalList.add(new Omnivore("pig", true, true, 30.4));
        animalList.add(new Omnivore("woman", true, true, 90.4));
        animalList.add(new Omnivore("human", true, true, 90.4));

        System.out.println("List of animals before sorting");
        for (Animal animal : animalList) {
            animal.printAllInfo();
        }

        System.out.println("Sorted list of animals before serialization ...");
        animalList.sort(Animal.AnimalComparator);
        for (Animal animal : animalList) {
            animal.printAllInfo();
        }

        try {
            writeObject(animalList);
        } catch (IOException e) {
            System.out.println("An error occurred while writing objects to a file.");
//            e.printStackTrace();
        }

        ArrayList<Animal> listAnimal = new ArrayList<>();
        try {
            listAnimal = readObject();
        } catch (ClassNotFoundException | IOException e) {
            System.out.println("An error occurred while reading objects from a file.");
//            e.printStackTrace();
        }

        System.out.println("... and then");
        for (Animal animal : listAnimal) {
            animal.printAllInfo();
        }
    }
}