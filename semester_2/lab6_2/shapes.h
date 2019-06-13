//
// Created by gomonuk on 30.03.19.
//

#ifndef OOP_CPP2_SHAPES_H
#define OOP_CPP2_SHAPES_H

#include <vector>
//struct DataStruct {
//    int key1;
//    int key2;
//    string str;
//
//    bool operator<(const DataStruct& strc) {
//        if ((key1 == strc.key1) && (key2 == strc.key2))
//            return str.length() < strc.str.length();
//        else if (key1 == strc.key1)
//            return key2 < strc.key2;
//        else
//            return key1 < strc.key1;
//    }
//};

struct Point {
    int x,y;
};

struct Shape {
    int vertex_num; // количество вершин: для треугольника 3,
    std::vector<Point> vertexes; // вектор содержащий координаты вершин фигуры

    bool operator<(const Shape& shape) {
        return vertex_num < shape.vertex_num;
    }
};

Shape createRandomShape(int numVertices);

bool is_square(Shape shape);

void printShapeVector(std::vector<Shape> shapes);

void printPointVector(std::vector<Point> points);

double line_by_points(Point point1, Point point2);

class shapes {

};


#endif //OOP_CPP2_SHAPES_H
