//
// Created by gomonuk on 05.03.19.
//

/*
Задание:
Разработать программу, которая должна сделать следующее:
1.Прочитать содержимое текстового файла. Файл может содержать:
    a.Слова – состоят из латинских строчных и заглавных букв, а также цифр, длинна слова должна быть не более 20 символов
    b.Знаки препинания – «.», «,» «!» «?» «:» «;»
    c.Пробельные символы – пробел, табуляция, символ новой строки.

2.Отформатировать текст следующим образом:
    a.Не должно быть пробельных символов отличных от пробела
    b.Не должно идти подряд более одного пробела
    c.Между словом и знаком препинания не должно быть пробела
    d.После знака препинания всегда должен идти пробел
    e.Слова длиной более 10 символов заменяются на слово «Vau!!!»

3.Преобразовать полученный текст в набор строк, каждая из которых содержит целое количество строк
  (слово должно целиком находиться в строке) и ее длинна не превышает 40 символов.

Подсказки:
Для хранения всего входного текста можно использовать одну строку
Можно создать строки содержащие символы принадлежащие какое либо категории, например знаки препинания
Для хранения результирующих строк можно использовать vector<string>
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>

using std::string;
using std::vector;
using std::ifstream;
using std::endl;
using std::cout;
using std::regex;
using std::regex_replace;

const int MAX_INPUT_SIZE = 255;

vector<string> readStringsFromFile(ifstream &fileDescriptor) {
    string stringArray[MAX_INPUT_SIZE];

    int lineIndex = 0;
    while (!fileDescriptor.eof()) {
        getline(fileDescriptor, stringArray[lineIndex]);
        lineIndex++;
    }

    vector<string> result(stringArray, stringArray + lineIndex);
    return result;
}

/**
 * 1. Прочитать содержимое текстового файла.
 */
void readFile(string &file_name) {
    ifstream fileDescriptor(file_name);
    vector<string> lines = readStringsFromFile(fileDescriptor);
    auto lines_size = lines.size();
    for (int i = 0; i < lines_size; ++i) {
        cout << lines[i] << endl;
    }
}

string textProcessing(string &file_name) {
//    2.Отформатировать текст следующим образом:
//    a.Не должно быть пробельных символов отличных от пробела
//    b.Не должно идти подряд более одного пробела
//    c.Между словом и знаком препинания не должно быть пробела
//    d.После знака препинания всегда должен идти пробел
//    e.Слова длиной более 10 символов заменяются на слово «Vau!!!»

    ifstream fileDescriptor(file_name);
    string result_text;
    vector<string> lines = readStringsFromFile(fileDescriptor);
    auto lines_size = lines.size();

    for (int i = 0; i < lines_size; ++i) {
        result_text.append(lines[i]);
    }

    // \s? - ноль или один пробельный символ
    // ([.,!?:;…]) знаки препинания выделенные в группу
    // $1 - копирует символ сматченный группой №1
    result_text = regex_replace(result_text, regex("\\s?([.,!?:;…])"), "$1 ");

    // Заменяем один или много пробельных символов на одиночный пробел
    result_text = regex_replace(result_text, regex("\\s+"), " ");

    // Заменяем последовательность из 10 и более буквенных символов
    result_text = regex_replace(result_text, regex("\\w{10,}"), "Vau!!!");

    return result_text;
}

vector<string> prettyFormat(string &str) {
//    3.Преобразовать полученный текст в набор строк, каждая из которых содержит целое количество строк
//    (слово должно целиком находиться в строке) и ее длинна не превышает 40 символов.
    vector<string> result;
    regex exp(".{0,40}\\s");
    std::smatch res;

//    string::const_iterator searchStart( str.cbegin() );
//    while ( regex_search( searchStart, str.cend(), res, exp ) )
//    {
//        cout << ( searchStart == str.cbegin() ? "" : " " ) << res[0] << endl;
//        searchStart = res.suffix().first;
//    }

    while (regex_search(str, res, exp)) {
        result.push_back(res[0]);
        str = res.suffix();
        if (str.size() == 0) break;
    }
    return result;
}

template<typename T>
void print_vector(std::vector<T> vec) {
    unsigned long i;
    std::cout << "\n";
    for (i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << endl;
    }
    std::cout << "\n";
}


int main() {
    string file_name = "../input.txt";

    cout << "Исходный текст:" << endl;
    readFile(file_name);

    cout << "\nТекст после обработки, в одну строку:" << endl;
    string text = textProcessing(file_name);
    cout << text << endl;

    cout << "\nОбработанный текст распечатанный по 40 символов" << endl;
    vector<string> pretty_lines = prettyFormat(text);
    print_vector(pretty_lines);

    return 0;
}