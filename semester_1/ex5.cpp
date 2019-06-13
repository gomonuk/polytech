#include <iostream>
#include <stdio.h>
#include <cstring>

//При написании функций можно использовать только следующее:
//- целочисленные константы;
//- целочисленные аргументы функций и автоматические (локальные)переменные;
//- операции   ~ !     *     +  -   (тип)  sizeof    <<  >>    &     ^     |
// Группы операций расположены в порядке   убывания приоритета.
//
//Запрещается:
//- использовать такие операторы как if, do, while, for, switch и т.п. ;
//- использовать макросы или какие либо функции;
//- использовать другие операции такие как &&, ||, ?: ;
//- использовать типы данных кроме целочисленных;
//- использовать массивы, структуры и объединения.
//
//Методические указания для выполнения заданий приведены в Приложении 13.

//unsigned ChangeGroupBits(unsigned x, unsigned y, int n1, int n2);
//ChangeGroupBits– возвращает х, в котором заданная группа разрядов получается исключающим или соответствующих групп х и у.
//Разряды нумеруются с 0.
//ChangeGroupBits(0xFFFF,0xFFA5,1,7) = 0xFF5B

unsigned ChangeGroupBits(unsigned x, unsigned y, unsigned n1, unsigned n2)
{
    unsigned n = n2 - n1 + 1;
    unsigned mask = ~(-1u << n) << n1;
    return x ^ (y & mask);
}

int main(){

    std::cout << "0x"<< std::hex << ChangeGroupBits(0xFFFF, 0xFFA5, 1, 7) << '\n';

    return 0;
}