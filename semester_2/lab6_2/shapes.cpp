//
// Created by gomonuk on 30.03.19.
//

#include <random>
#include <iostream>
#include "shapes.h"


time_t seed = time(nullptr);
std::mt19937_64 rng(seed);
std::uniform_int_distribution<int> random_point(-50, 50);

Shape createRandomShape(int numVertexes) {
    Shape shape;
    shape.vertex_num = numVertexes;
    for (int i = 0; i < numVertexes; i++) {
        Point newPoint;
        newPoint.x = random_point(rng);
        newPoint.y = random_point(rng);
        shape.vertexes.push_back(newPoint);
    }
    return shape;
}


void printPointVector(std::vector<Point> points) {
//    for (std::vector<Point>::iterator pointIt = points.begin() ; pointIt!=points.end() ; ++pointIt) {
    for (auto point : points) {
        std::cout << "(" << point.x << "," << point.y << ") ";
    }
}


void printShapeVector(std::vector<Shape> shapes) {
    for (std::vector<Shape>::iterator shapeIt = shapes.begin() ; shapeIt!=shapes.end() ; ++shapeIt) {
        Shape shape = *shapeIt;
        switch (shape.vertex_num) {
            case 3:
                std::cout << "Triangle: { ";
                break;
            case 4:
                if (is_square(shape)) {
                    std::cout << "Square: { ";
                } else {
                    std::cout << "Rectangle: { ";
                }
                break;
            case 5:
                std::cout << "Pentagon: { ";
                break;
            default:
                break;
        }
        printPointVector(shape.vertexes);
        std::cout << "}" << std::endl;
    }
}


double line_by_points(Point point1, Point point2){
    double a = (point1.x - point2.x);
    double b = (point1.y - point2.y);
    return sqrt(pow(a, 2) + pow(b, 2));
}


bool is_square(Shape shape) {
    // https://5terka.com/node/2402
    if (shape.vertex_num != 4) {
        return false;
    }

    Point A = shape.vertexes.at(0);
    Point B = shape.vertexes.at(1);
    Point C = shape.vertexes.at(2);
    Point D = shape.vertexes.at(3);

    double sideAB = line_by_points(A, B);
    double sideBC = line_by_points(B, C);
    double sideCD = line_by_points(C, D);
    double sideAD = line_by_points(A, D);

    double diagonalAC = line_by_points(A, C);
    double diagonalBD = line_by_points(B, D);

    bool isRhomb = (sideAB == sideBC) && (sideCD == sideAD) && (sideAB == sideAD);
    bool isDiagonalEquals = (diagonalAC == diagonalBD);

    return isDiagonalEquals && isRhomb;
};

