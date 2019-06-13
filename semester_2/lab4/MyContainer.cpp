//
// Created by gomonuk on 24.03.19.
//

#include "MyContainer.h"

/// Реализация контейнера
MyContainer::MyContainer() = default;

MyContainer::iterator MyContainer::begin() {
    return 1;
}

MyContainer::iterator MyContainer::end() {
    return 11;
}


/// Реализация Итератрора
MyIterator::MyIterator(int startNumber){
    this->currentNumber = startNumber;
}

int MyIterator::operator*() {
    int result = 1;
    for(int i = 1; i <= currentNumber; i++) {
        result *= i;
    }
    return result;
}

MyIterator& MyIterator::operator++() {
    currentNumber += 1;
    return *this;
}

MyIterator& MyIterator::operator--() {
    currentNumber -= 1;
    return *this;
}

bool MyIterator::operator==(MyIterator other) {
    return this->currentNumber == other.currentNumber;
}

bool MyIterator::operator!=(MyIterator other) {
    return this->currentNumber != other.currentNumber;
}

bool MyIterator::operator<(MyIterator other) {
    return this->currentNumber < other.currentNumber;
}

bool MyIterator::operator>(MyIterator other) {
    return this->currentNumber > other.currentNumber;
}

const MyIterator MyIterator::operator++(int) {
    MyIterator copy = MyIterator(currentNumber);
    ++(*this);
    return copy;
}