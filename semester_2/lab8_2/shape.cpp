#include <utility>

//
// Created by gomonuk on 06.04.19.
//

#include "shape.h"
#include <random>

time_t seed = time(nullptr);
std::mt19937_64 rng(seed);
std::uniform_int_distribution<int> random_int(-10, 10);

shape::shape() {
    x = random_int(rng);
    y = random_int(rng);
}

int shape::getX() { return x; }

int shape::getY() { return y; }

bool shape::IsMoreLeft(shape some_shape)  {
    return this->x < some_shape.x;
}

bool shape::IsUpper(shape some_shape) const {
    return this->y > some_shape.y;
}

void shape::Draw() {
    std::cout << "Тип фигуры:   "  << this->name
              << ", Координаты { " << this->x << "," << this->y << " }" << std::endl;
}

void shape::setName(std::string new_name) {
    this->name = std::move(new_name);
}


Circle::Circle():shape() {
    shape::setName(shape_type);
};


Triangle::Triangle():shape() {}
void Triangle::Draw()  {
    std::cout << "Тип фигуры: " << this->name
              << ", Координаты { "<< this->x << "," << this->y << " }" << std::endl;
};