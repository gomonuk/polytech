/**
Created by gomonuk on 04.04.19.

 Разработать программу, которая, используя только стандартные алгоритмы и функторы,
 умножает каждый элемент списка чисел с плавающей  точкой на число PI
*/

#include <list>
#include <random>
#include <iostream>
#include <algorithm>

std::list<float> fillRandom(int size, int MIN, int MAX) {
    std::list<float> vec;
    time_t seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<float> random_index_string(MIN, MAX);

    for (int i = 0; i < size; i++) {
        vec.push_back(random_index_string(rng));
    }
    return vec;
}

int main(){
    std::list<float> simple_float = fillRandom(5, -500, 500);
    std::list<float> float_pi;


    for (float &it : simple_float) {
        std::cout << it << " ";
    }
    std::cout << "\n";

//    for (float &it : simple_float)
//        it =std::multiplies<float>()(it, static_cast<const float &>(M_PI));

    std::for_each(simple_float.begin(),simple_float.end(),
            [&] (float i) { float_pi.push_back(i * M_PI);});

    for (float &it : float_pi) {
        std::cout << it << " ";
    }
    return 0;
}

