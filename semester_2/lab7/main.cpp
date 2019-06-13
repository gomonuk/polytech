/**
Created by gomonuk on 02.04.19.

 Разработать функтор, позволяющий собирать статистику о
 последовательности целых чисел (послед может содержать числа от -500 до 500).
 Функтор после обработки последовательности алгоритмом for_each
 должен предоставлять следующую статистику:

a. Максимальное число в последовательности
b. Минимальное число в последовательности
c. Среднее число в последовательности
d. Количество положительных чисел
e. Количество отрицательных чисел
f. Сумму нечетных элементов последовательности
g. Сумму четных элементов последовательности
h. Совпадают ли первый и последний элементы последовательности.

Проверить работу программы на случайно сгенерированных последовательностях.*/

#include <vector>
#include <random>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <functional>


std::vector<int> fillRandom(int size, int MIN, int MAX) {
    std::vector<int> vec;
    time_t seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> random_integer_value(MIN, MAX);

    for (int i = 0; i < size; i++) {
        vec.push_back(random_integer_value(rng));
    }
    return vec;
}

class Statistics : public std::unary_function<int, void> {
    int maximum;         // a. Максимальное число в последовательности
    int minimum;         // b. Минимальное число в последовательности
    int positive_count;  // d. Количество положительных чисел
    int negative_count;  // e. Количество отрицательных чисел

    int sum_odd;         // f. Сумму нечетных элементов последовательности
    int sum_even;        // g. Сумму четных элементов последовательности

    int count;           // c. Среднее число в последовательности
    int sum;

    int first_elem;      // h. Совпадают ли первый и последний элементы последовательности.
    int last_elem;

public:
    // Ниже представлен конструктор класса с пустым телом
    // и инициализацией переменных по новым правилам
    // https://ravesli.com/urok-117-spisok-initsializatsii-chlenov-klassa/

    Statistics()
            : maximum(std::numeric_limits<int>::min()), // Инициализация минимальным значением типа int
              minimum(std::numeric_limits<int>::max()),
              positive_count(0),
              negative_count(0),
              sum_even(0),
              sum_odd(0),
              count(0),
              sum(0) {  /* пустое тело конструктора */  }

    int getMaximum() const {
        return maximum;
    }

    int getMinimum() const {
        return minimum;
    }

    int getPositiveCount() const {
        return positive_count;
    }

    int getNegativeCount() const {
        return negative_count;
    }

    double getAverage() const {
        return static_cast<double>(sum) / count;
    }

    int getSumEven() const {
        return sum_even;
    }

    int getSumOdd() const {
        return sum_odd;
    }

    bool getFirstEqualsLast() const {
        return first_elem == last_elem;
    }

    void operator()(int next) {
        sum += next;
        ++count;
        last_elem = next;

        if (count == 1)
            first_elem = next;

        if (next > maximum) {
            maximum = next;
        }

        if (next < minimum) {
            minimum = next;
        }

        if (next > 0) {
            ++positive_count;
        }

        if (next < 0) {
            ++negative_count;
        }

        if (next % 2 == 0) {
            ++sum_even;
        } else {
            ++sum_odd;
        }
    }
};


int main() {
    std::vector<int> vec = fillRandom(10, -500, 500);

    for (int &it : vec) {
        std::cout << it << " ";
    }

    Statistics stat;
    stat = std::for_each(vec.begin(), vec.end(), stat);

    std::cout << std::endl
              << "Maximum: " << stat.getMaximum()                       << std::endl
              << "Minimum: " << stat.getMinimum()                       << std::endl
              << "Average: " << stat.getAverage()                       << std::endl
              << "Positive count: " << stat.getPositiveCount()          << std::endl
              << "Negative count: " << stat.getNegativeCount()          << std::endl
              << "Sum of even numbers: " << stat.getSumEven()           << std::endl
              << "Sum of odd  numbers: " << stat.getSumOdd()            << std::endl
              << "First == last: "       << stat.getFirstEqualsLast()   << std::endl;

    return 0;
}