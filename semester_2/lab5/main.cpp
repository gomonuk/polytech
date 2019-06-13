//
// Created by gomonuk on 26.03.19.
//

/**
a.  Заполняет vector<DataStruct> структурами DataStruct, при этом key1 и key2,
    генерируются случайным образом в диапазоне от -5 до 5, str заполняется из
    таблицы (таблица содержит 10 произвольных строк, индекс строки
    генерируется случайным образом)
b.  Выводит полученный вектор на печать

c. Сортирует вектор следующим образом:
     i. По возрастанию key1
    ii. Если key1 одинаковые, то по возрастанию key2
   iii. Если key1 и key2 одинаковые, то по возрастанию длинны строки str
d. Выводит полученный вектор на печать

DataStruct определена следующим образом:
typedef struct {
    int key1;
    int key2;
    string str;
} DataStruct;
*/

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <time.h>
#include <algorithm>


using std::vector;
using std::string;
using std::cout;
using std::endl;

struct DataStruct {
    int key1;
    int key2;
    string str;

    bool operator<(const DataStruct& strc) {
        if ((key1 == strc.key1) && (key2 == strc.key2))
            return str.length() < strc.str.length();
        else if (key1 == strc.key1)
            return key2 < strc.key2;
        else
            return key1 < strc.key1;
    }
};


string getString(int index) {
    vector<string>  stringArray = {
            "S1",
            "St2",
            "Str3",
            "Stri4",
            "Strin5",
            "String6",
            "SString7",
            "SSString8",
            "SSSString9",
            "SSSSString0",
    };
    return stringArray[index];
}


void printVectorDataStruct(vector<DataStruct> vectorDataStruct){
    vector<DataStruct>::iterator iterator = vectorDataStruct.begin();
    cout << "string-key1-key2" << endl;
    while (iterator != vectorDataStruct.end()) {
        DataStruct strc = *iterator;
        cout << strc.str << " " << strc.key1 << " " << strc.key2 << endl;
        iterator++;
    }
    cout << endl;

}


int main(){
    int LIST_LEN = 50;
    vector<DataStruct> vectorDataStruct;

    time_t seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> random_index_string(0, 9);
    std::uniform_int_distribution<int> random_index_key(-5, 5);

    for (int i = 0; i < LIST_LEN; i++) {
        DataStruct structur;
        structur.key1 = random_index_key(rng);
        structur.key2 = random_index_key(rng);
        structur.str = getString(random_index_string(rng));
        vectorDataStruct.push_back(structur);
    }

    cout << "До сортировки" << endl;
    printVectorDataStruct(vectorDataStruct);

    sort(vectorDataStruct.begin(), vectorDataStruct.end());

    cout << "После сортировки" << endl;
    printVectorDataStruct(vectorDataStruct);
}

