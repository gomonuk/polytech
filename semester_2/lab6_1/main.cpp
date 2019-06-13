/**
Created by gomonuk on 26.03.19.

Написать программу, которая выполняет следующие действия:

a. Читает содержимое текстового файла
b. Выделяет слова, словом считаются последовательность символов
   разделенных пробелами и/или знаками табуляции и/или символами новой строки
c. Вывести список слов присутствующий в тексте без повторений (имеется в виду,
   что одно и то же слово может присутствовать в списке только один раз)

Подсказка: кроме алгоритмов рассмотренных в этой работе можно применять все средства
описанные в предыдущих работах, включая алгоритмы сортировки.

 http://www.cyberforum.ru/cpp-beginners/thread625812.html
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>

template<typename T>
void print_vector(std::vector<T> vec) {
    unsigned long i;
    std::cout << "\n";
    for (i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }
    std::cout << "\n";
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> split2(std::string line) {
    std::vector<std::string> wordsVector;
    std::string buffer;
    std::vector<char> delimiters = {' ', '\n', '\t', '\r', '\v', '\f'};

    for (int i = 0; i < line.size(); i++) {
        if (i == line.size() - 1) {
            buffer += line[i];
            wordsVector.push_back(buffer);
            break;
        }

        // bool found = (std::find(my_list.begin(), my_list.end(), my_var) != my_list.end());
        if (std::find(delimiters.begin(), delimiters.end(), line[i]) == delimiters.end()) {
            buffer += line[i];
        } else {
            wordsVector.push_back(buffer);
            buffer = "";
        }
    }

    return wordsVector;
}

std::string readStringsFromFile(std::string &file_name) {
    std::ifstream fileDescriptor(file_name);
    std::string result_text;
    std::string buff;

    while (!fileDescriptor.eof()) {
        std::getline(fileDescriptor, buff);
        result_text.append(buff);
        buff = "";
    }

    return result_text;
}

int main() {
    std::string file_name2 = "../input.txt";
    std::string text = readStringsFromFile(file_name2);
    std::vector<std::string> wordsVector = split2(text);

    std::unordered_set<std::string> us(wordsVector.begin(), wordsVector.end());
    for(const auto& elem: us)
        std::cout << elem << ' ';
    std::cout << std::endl;

    return 0;
}
