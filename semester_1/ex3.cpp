#include <iostream>
#include <stdio.h>
#include <cstring>

//Задание N 3
//Выполнить задачу из задания 1 с вводом данных из командной строки (не с клавиатуры!).
//Методические указания к решению задачи - конец 4-ой лекции.

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

int main(int argc, char *argv[]){
    if( argc < 2 ) {
        printf("%s", "Please input string to reverce.\n");

    } else {
        char* Str = argv[1];

        Reverse_by_Index(Str);
        printf("Reverse_by_Index %s \n", Str);

        Reverse_by_Pointer(Str);
        printf("Reverse_by_Pointer %s \n", Str);
    }

    return 0;
}