#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <ctime>


template<typename T>
void print_vector(std::vector<T> vec) {
    unsigned long i;
    std::cout << "\n";
    for (i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ",";
    }
    std::cout << "\n";
}

void insertionsort_operator(std::vector<int> &a, int l, unsigned long r) {
    for (int i = l + 1; i < r; i++) {
        int j = i;
        while (j > l && a[j - 1] > a[j]) {
            std::swap(a[j - 1], a[j]);
            j--;
        }
    }
}

template<typename T>
void insertionsort_at(std::vector<T> &a, int l, unsigned long r) {
    for (int i = l + 1; i < r; i++) {
        int j = i;

        while (j > l && a.at(j - 1) > a.at(j)) {
            std::swap(a.at(j - 1), a.at(j));
            j--;
        }
    }
}

void insertionsort_iter(std::vector<int> &a) {
    std::vector<int>::iterator iter;
    for (iter = a.begin(); iter < --a.end() + 1; iter++) {
        auto jiter = iter;
        while (jiter < a.end() && *(jiter - 1) > *jiter) {
            std::swap(*(jiter - 1), *(jiter));
            jiter--;
        }
    }
}

void read_file() {
    FILE *fp;

    fp = fopen("../input.txt", "rb");

    int read_i = 1;
    char **res; // указатель на массив символов
    char *tmp;
    res = (char **) malloc(read_i * sizeof(char *)); // выделение неинициализированной памяти размером на один элемент
    while (!feof(fp)) {
        tmp = (char *) calloc(256, sizeof(char)); // выделение памяти под массив из 256 чаров
        fgets(tmp, 256, fp); // куда / сколько / откуда
        res[read_i - 1] = tmp;
        read_i++;
        res = (char **) realloc(res, read_i * sizeof(char *));
    }
    int lines = read_i - 2;
    std::vector<char *> v(res, res + lines); // load all lines in vector

    print_vector(v);
    std::cout << std::endl;
}

void read_from_stdio() {
// 5) Напишите программу, сохраняющую в векторе числа, полученные из стандартного ввода (окончанием ввода является число 0).
// Удалите все элементы, которые делятся на 2 (не используете стандартные алгоритмы STL), если последнее число 1.
// Если последнее число 2, добавьте после каждого числа которое делится на 3 три единицы.

    int elemet;
    std::vector<int> vec;
    std::vector<int> vec_111 = {1, 1, 1};
    std::vector<int>::iterator iter;

    std::cout << "Введите числа. Чтобы закончить введите 0" << std::endl;
    while (true) {
        scanf("%d", &elemet);
        if (elemet == 0) {
            std::cout << "Выходим!" << std::endl;
            break;
        }
        vec.push_back(elemet);
    }

    elemet = vec.back();
    if (elemet == 1) {
        for (iter = vec.begin(); iter < vec.end(); iter++) {
            if (*iter % 2 == 0) {
                vec.erase(iter);
            }
        }
        print_vector(vec);

    } else if (elemet == 2) {
        for (iter = vec.begin(); iter < vec.end(); iter++) {
            if (*iter % 3 == 0) {
                iter = vec.insert(iter + 1, vec_111.begin(), vec_111.end());
//                iter = vec.insert(iter+1, 3, 1);

            }
        }
        print_vector(vec);
    }
}

void fillRandom(double *array, int size) {
// 6) Напишите функцию void fillRandom(double* array, int size) заполняющую массив случайными значениямив интервале
// от -1.0 до 1.0. Заполните с помощью заданной функции вектора размером 5,10,25,50,100 и отсортируйте его содержимое
// (с помощью любого разработанного ранее алгоритма модифицированного для сортировки действительных чисел)
    int i;
    for (i = 0; i < size; ++i) {
        array[i] = ((1.0 + 1.0) * ((double) rand() / RAND_MAX)) - 1.0;
    }
}


int main() {
    std::vector<int> vv = {1, 5, 6, 7, 9, 8, 2, 3, 4, 0};
    std::chrono::time_point<std::chrono::system_clock> start, end;
    auto vector_size = vv.size();
    print_vector(vv);
    start = std::chrono::system_clock::now();

    // задание 1
    insertionsort_operator(vv, 0, vector_size);
    std::cout << "\n Сортировка через прямой доступ \n";

    // задание 2
    insertionsort_at(vv, 0, vector_size);
    std::cout << "\n Сортировка через at() \n";

    // задание 3
    insertionsort_iter(vv);
    std::cout << "\n Сортировка через итераторы\n";

    end = std::chrono::system_clock::now();
    long elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "\nВремя выполнения сортировки: " << elapsed_seconds << " microseconds\n";
    print_vector(vv);

    // задание 4
    std::cout << "\n Чтение из файла в вектор: \n";
    read_file();

    // задание 5
    std::cout << "\n Ввод и обработка вектора через stdio\n";
    read_from_stdio();

    // задание 6
    std::cout << "\n Заполнение и сортировка вектора случайными значениями\n";
    int size_array[] = {5, 10, 25, 50, 100};
    int i;
    for (i = 0; i < 5; ++i) {
        double *da;
        da = (double *) calloc(size_array[i], sizeof(double));
        fillRandom(da, size_array[i]);
        std::vector<double> v(da, da + size_array[i]);

        std::cout << "unsorted vector size: " << size_array[i] << std::endl;
        print_vector<double>(v);
        insertionsort_at(v, 0, v.size());

        std::cout << "sorted vector size: " << size_array[i] << std::endl;
        print_vector<double>(v);
        free(da);
    }
    return 0;
}