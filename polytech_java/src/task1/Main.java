package task1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.TreeMap;
import org.apache.commons.lang3.ArrayUtils;

// Дана строка. Разделить строку на фрагменты по три подряд идущих символа.
// В каждом фрагменте средний символ заменить на случайный символ, не совпадающий ни с одним из символов этого фрагмента.
// Показать фрагменты, упорядоченные по алфавиту.


public class Main {

    public static void main(String[] args) {

        int CHUNK_SIZE = 3;
        char[] CharArray = randomCharArrayGenerate(50);
        Map<Character, List<char[]>> chanksMap = new TreeMap<Character, List<char[]>>();

        for (int i = 0; i < CharArray.length; i += CHUNK_SIZE) {
            char[] chunk = Arrays.copyOfRange(CharArray, i, i + CHUNK_SIZE);
            chunk[1] = randomCharGenerate(chunk);

            if (chanksMap.containsKey(chunk[0])) {
                chanksMap.get(chunk[0]).add(chunk);
            } else {
//                chanksMap.put(chunk[0], new ArrayList<char[]>(chunk));
                chanksMap.put(chunk[0], new ArrayList<char[]>(Collections.singleton(chunk)));
            }
        }

        var orderedKeys = chanksMap.keySet();
        for (Object key : orderedKeys) {
            System.out.printf("\n---- %s ----\n", key);
            List<char[]> values = chanksMap.get(key);
            for (char[] value : values) {
                System.out.printf("%s ", Arrays.toString(value));
            }
        }
    }

    private static char randomCharGenerate(char[] minusSymbols) {
        char[] alphabetChar = "abcdefghijklmnopqrstuvwxyz".toCharArray();
        Character[] alphabet = setDifference(alphabetChar, minusSymbols);
        Random random = new Random();
        return alphabet[random.nextInt(alphabet.length)];
    }

    private static char[] randomCharArrayGenerate(int capacity) {
        char[] arr = new char[capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = randomCharGenerate("".toCharArray());
        }
        return arr;
    }

    private static Character[] setDifference(char[] arr1, char[] arr2) {
        Character[] objectArray1 = ArrayUtils.toObject(arr1);
        Character[] objectArray2 = ArrayUtils.toObject(arr2);
        HashSet<Character> list1 = new HashSet<>(Arrays.asList(objectArray1));
        HashSet<Character> list2 = new HashSet<>(Arrays.asList(objectArray2));
        list1.removeAll(list2);
        return list1.toArray(new Character[0]);
        //        return list1.toArray(new Character[list1.size()]);
    }

}