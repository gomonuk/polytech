#include <iostream>
#include <stdio.h>


//Написать функцию для произвольного двухмерного классического (не свободного) массива с использованием индексов.
//Прототип функции должен выглядеть приблизительно следующим образом:

//int Func( int * Array, int Dim1, int Dim2, ...);

//Подчеркнутые параметры(int Dim1, int Dim2) – обязательны. Массив при определении инициализируется массивом значений.
//Методические указания решения задачи приведены в лекции 4 (разработка функции print_arr).
//Второй вариант функции должен являться чисто формальным преобразованием выражений с индексами в выражения с указателями
//Необходимо ответить на вопросы, поставленные в лекции 4.
//Почему все нижеприведенные обращения к функции – эквивалентны?
//
//Func((int*)m, Dim1, Dim2, …);
//Func (*m, Dim1, Dim2, …);
//Func (m[0], Dim1, Dim2, …);
//Func (&m[0][0], Dim1, Dim2, …);
//Func (&**m, Dim1, Dim2, …);
//
//Вариант № 7. Найти наибольший элемент в заданном столбце
//

int max_element_by_index(int* matrix, int dim1, int dim2, int column_index) {
    int result = INT16_MIN;
    int element = 0;

    for(int i = 0; i < dim1; i++) {
        element = matrix[column_index];
        if (result < element){
            result = element;
        };
        column_index = column_index + dim2;
    }
    return result;
}


int max_element_by_pointer(int* matrix, int dim1, int dim2, int column_index) {
    int result = INT16_MIN;
    int element = 0;

    for(int i = 0; i < dim1; i++) {
        element = *(matrix + column_index);
        if (result < element){
            result = element;
        };
        column_index = column_index + dim2;
    }
    return result;
}


int main(){
    const int Dim1 = 3;
    const int Dim2 = 4;
    const int Column_Index = 2;

    int Matrix[Dim1][Dim2] = {{0, 1, 2, -3},
                              {4, 5, 6, -7},
                              {8, 9, 0, -1}};

    int by_index = max_element_by_index(*Matrix, Dim1, Dim2, Column_Index);
    printf("Результат работы функции max_element_by_index равен: %d \n", by_index);

    int by_pointer = max_element_by_pointer(*Matrix, Dim1, Dim2, Column_Index);
    printf("Результат работы функции max_element_by_pointer равен: %d \n", by_pointer);

    return 0;
}