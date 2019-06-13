#include <stdio.h>
#include <iostream>
#include <list>
#include <zconf.h>
#include <cstring>

//Написать шаблоны контейнерных классов.
// В качестве основы можно использовать наброски классов из приложений 10, 14 и класс Array из лекции 13.
//
//Каждый класс должен  содержать следующие методы:
//- набор конструкторов (в том числе и конструктор копирования);
//- деструктор.
//- iterator begin(void);
//- iterator end(void);
//- void clear(void);
//- bool empty(void);
//- size_type size(void); //количество элементов
//
//Во всех контейнерах для итераторов реализованы операции:
//=, ==, !=, *, ++(префиксная и постфиксная)
//Кроме того каждый класс должен содержать свой специфический набор методов.
//
//class Vector На основе динамического массива.
//Дополнительный набор методов:
//void push_back(T &value);
//void pop_back(void);
//T&   back(void);
//void erase (iterator p);
//iterator insert(iterator position, const T& value);
//T& at(int i);
//void swap(Vector & that);
//Vector & operator=( Vector & that);



template<class T> class Vector {
private:
    T * v;                // указатель на массив элементов вектора
    int ind, size;

public:
    Vector(int n=256){
        v=new T[size=n];
        ind=0;
    }
    ~Vector(void){
        delete[] v;
        v=NULL;
    }

    typedef T* iterator;

    void push_back(T &value) {
        v[ind++]=value;
    }

    iterator begin(void){
        return v;
    }

    iterator end(void){
        return v+ind;
    }

    void clear(void){
        delete[] v;
        v=NULL;
        ind = 0;
        size = 0;
    };

    bool isEmpty(void){
        return ind == 0;
    };

    int getSize(void){
        return size;
    };

    void pop_back(void){
        size--;
        ind--;
    };

    T&  back(void){
        return v[ind];
    };

    void erase (iterator p){
        v[p] = NULL;
    };

    iterator insert(iterator position, const T& value){
        T * tmp;
        memcpy ( tmp, v, sizeof(int) );
    };

//    T& at(int i);
//    void swap(Vector & that);
//    Vector & operator=( Vector & that);

};