

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



#include <cstdio>

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

    void push_back(T value) {
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
        ind--;
    };

    T&  back(void){
        return v[ind];
    };

    void erase (iterator p){
        v[p] = NULL;
    };

    iterator insert(iterator position, const T& value){
//        for (int j = n-1; j >= index; j--)
//        {
//            arr[j+1] = arr[j];
//        }
//        v[position] = value;
    };

//    T& at(int i);
    void swap(const Vector & that){

        v = that.v;

        printf("Your color\n");

    };
//    Vector & operator=( Vector & that);

};

int main(void) {
    printf("Your color\n");
    Vector<int> v;
    v.push_back(1);

    Vector<int> v2;
    v2.push_back(2);
    v.swap(v2);

}