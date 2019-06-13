//
// Created by gomonuk on 20.03.19.
//

#include <list>
#include <iostream>
#include <random> // The header for the generators.
//#include <ctime> // To seed the generator.


int random_range(int min, int max){
//    https://gist.github.com/PhDP/5289449
    time_t seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> unii(min, max);
    return unii(rng);

}

int main(){
    int MIN = 0;
    int MAX = 20;
    int LIST_LEN = 6;
    int random_value;
    std::list<int> randomValuesList;

    time_t seed = time(nullptr);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> unii(MIN, MAX);

    for (int i = 0; i < LIST_LEN; i++) {
        // To get a random number, send the engine (rng) as argument to the distribution object:
        random_value = unii(rng);
        randomValuesList.push_back(random_value);
        std::cout << random_value << ' ';
    }

    std::cout <<  "\n";

    auto iter = randomValuesList.begin();
    auto reverse_iter = randomValuesList.rbegin();

    for (int i = 0; i < LIST_LEN / 2; i++) {
        std::cout << *(iter++) << " " << *(reverse_iter++) << " ";
    }

    if (LIST_LEN % 2 != 0)
        std::cout << *iter;


    return 0;
}