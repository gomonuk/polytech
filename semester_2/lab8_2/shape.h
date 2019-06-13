//
// Created by gomonuk on 06.04.19.
//

#ifndef OOP_CPP2_SHAPE_H
#define OOP_CPP2_SHAPE_H

#include <string>
#include <iostream>

/*
i.Класс Shape.
1.Содержит информацию о положении центра фигуры (координаты x и y).
2.Содердит метод IsMoreLeft, позволяющий определить расположена ли данная фигура
левее (определяется по положению центра) чем фигура переданная в качестве аргумента
3.Содердит метод IsUpper, позволяющий определить расположена ли данная фигура
выше (определяется по положению центра) чем фигура переданная в качестве аргумента
4.Определяет чисто виртаульную функцию рисования Draw
(каждая фигура в реализации этой функци должна выводить на стандартный вывод
 свое название и положение центра)

ii.Класс Circle производный от класса Shape
1.Реализует Draw
        iii.Класс Triangle производный от класса Shape
1.Реализует Draw
        iv.Класс Square производный от класса Shape
1.Реализует Draw*/

class shape {
protected:
    std::string name = "shape";
    int x;
    int y;

public:
// Ниже представлен конструктор класса с пустым телом
// и инициализацией переменных по новым правилам
// https://ravesli.com/urok-117-spisok-initsializatsii-chlenov-klassa/
    shape();
    int getX();
    int getY();
    void setName(std::string new_name);
    bool IsMoreLeft(shape some_shape);
    bool IsUpper(shape some_shape) const;
    virtual void Draw();
};

// Переопределяем переменную принадлежащую родителю в конструкторе. Используем только методы род.класса
class Circle: public shape{
    std::string shape_type = "Circle";
public:
    Circle();
};


// Реализуем метод Draw и консруктор прям тут.
class Square: public shape{
    std::string name = "Square";
public:
    Square(): shape() {}
    virtual void Draw() {
        std::cout << "Тип фигуры:   " << this->name
                  << ", Координаты { "<< this->x << "," << this->y << " }" << std::endl;
    };
};


// Реализуем метод Draw отдельно от определения
class Triangle: public shape{
    std::string name = "Triangle";
public:
    Triangle();
    void Draw() override;
};


#endif //OOP_CPP2_SHAPE_H
