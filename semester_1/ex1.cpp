#include <iostream>
#include <stdio.h>
#include <cstring>
//#include <conio.h>

//Написать функцию в двух вариантах: с использованием индексов и указателей.
//Вначале должна быть написана функция с использованием  индексов.
//Второй вариант должен являться чисто формальным преобразованием "выражений с индексами" в "выражения с указателями"
//(которое всегда осуществляется самим компилятором!!!!, когда он встречает выражения с индексами).
//Пример разработки подобной функции приведен в приложении 04.
//
//char* strrew(char* string)
//Реверсирует строку и возвращает на нее указатель.

int strlen(char* p) {
    int i = -1;
//    printf(p, *p);
    while (*p++)
        i++;
    return i;
}

char* Reverse_by_Index(char* string){
    int start = 0;
    int end = strlen(string);
    char tmp;

    while( end > start ){
        //printf("start %d, end, %d", start, end);
        tmp = string[start];
        string[start] = string[end];
        string[end] = tmp;
        start++;
        end--;
    }
    return string;
}


char* Reverse_by_Pointer(char* string){
    int start = 0;
    int end = strlen(string);
    char tmp;

    while( end > start ){
        //printf("start %d, end, %d", start, end);
        tmp = *(string + start);
        string[start] = *(string + end);
        string[end] = tmp;
        start++;
        end--;
    }
    return string;
}

int main(){
    char Str[20] = "012345678";
    Reverse_by_Index(Str);
    printf("Reverse_by_Index %s \n", Str);

    Reverse_by_Pointer(Str);
    printf("Reverse_by_Pointer %s", Str);

    return 0;
}