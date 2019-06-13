#include "shapes.h"

/**
 * Created by gomonuk on 26.03.19.
Написать программу, которая выполняет следующие действия
(все операции должны выполняться с помощью стандартных алгоритмов):

a. Заполняет вектор геометрическими фигурами.
   Геометрическая фигура может быть треугольником, квадратом, прямоугольником или пятиугольником.
   Структура описывающая геометрическую фигуру определена ниже,
b. Подсчитывает общее количество вершин всех фигур содержащихся в векторе
   (так треугольник добавляет к общему числу 3, квадрат 4 и т.д.)
c. Подсчитывает количество треугольников, квадратов и прямоугольников в векторе
d. Удаляет все пятиугольники
e. На основании этого вектора создает vector<Point>, который содержит координаты
   одной из вершин (любой) каждой фигуры, т.е. первый элемент
   этого вектора содержит координаты одной из вершину первой фигуры,
   второй элемент этого вектора содержит координаты одной из вершину второй фигуры и т.д.
f. Изменяет вектор так, чтобы он содержал в начале все треугольники, потом все квадраты, а потом прямоугольники.
g. Распечатывает вектор после каждого этапа работы

Геометрическая фигура задается следующей структурой:

typedef struct {
    int vertex_num; // количество вершин: для треугольника 3,
                                          для квадрата и прямоугольника 4,
                                          для пяти угольника 5
    vector<Point> vertexes; // вектор содержащий координаты вершин фигуры
                                          Для треугольника содержит 3 элемента
                                          Для квадрата и прямоугольника содержит 4 элемента
                                          Для пятиугольника 5 элементов
} Shape;

typedef struct {
    int x,y;
} Point;

*/

#include "shapes.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>


int main() {
    time_t seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> random_vertex_num(3, 5);
    int vertex;
    int vertex_count = 0;
    unsigned long shapes_size = 11;

    // Задание а
    std::vector<Shape> shapes;
    shapes.reserve(shapes_size);
    for (int i = 0; i < shapes_size; i++) {
        vertex = random_vertex_num(rng);
        vertex_count += vertex;
        shapes.push_back(createRandomShape(vertex));
    }

    std::cout << "==== Задание а ====\n" << std::endl;
    printShapeVector(shapes);

    // Задание b
    std::cout << "\n==== Задание b ====\n " << std::endl;
    std::cout << "Общее количество вершин всех фигур: " << vertex_count << std::endl;

    // Задание c  Подсчитывает количество треугольников, квадратов и прямоугольников в векторе
    int triangleNum = 0;
    int squareNum = 0;
    int rectangleNum = 0;

    for (const auto &shape : shapes) {
        switch (shape.vertex_num) {
            case 3:
                triangleNum += 1;
                break;
            case 4:
                if (is_square(shape)) {
                    squareNum += 1;
                } else {
                    rectangleNum += 1;
                }
                break;
            default:
                break;
        }
    }
    std::cout << "\n==== Задание c ====\n" << std::endl;
    std::cout << "triangleNum: " << triangleNum << " squareNum: " << squareNum << " rectangleNum: " << rectangleNum << std::endl;

    // Задание d
    // https://ru.cppreference.com/w/cpp/algorithm/remove
    shapes.erase(remove_if(shapes.begin(), shapes.end(), [](Shape& shape) { return shape.vertex_num == 5; }), shapes.end());
    std::cout << "\n==== Задание d ====\n" << std::endl;
    printShapeVector(shapes);

    // Задание e
    std::vector<Point> points;
    points.reserve(shapes.size());
    for (const auto &shape : shapes) {
        points.push_back(shape.vertexes.at(0));
    }

    // Задание f
    sort(shapes.begin(), shapes.end());
    std::cout << "\n==== Задание f ====\n" << std::endl;
    printShapeVector(shapes);

    return 0;

}
