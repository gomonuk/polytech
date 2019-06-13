//
// Created by gomonuk on 24.03.19.
//

#ifndef OOP_CPP2_MYCONTAINER_H
#define OOP_CPP2_MYCONTAINER_H

#include <iterator>


class MyIterator : public std::iterator<std::bidirectional_iterator_tag, int>
{
public:
    MyIterator(int startNumber);
//    MyIterator();

    int operator*();
    MyIterator & operator++();
    MyIterator & operator--();
    bool operator==(MyIterator other);
    bool operator!=(MyIterator other);
    bool operator<(MyIterator other);
    bool operator>(MyIterator other);

    const MyIterator operator++(int fakeUselessParamCppSucks);
//    const MyIterator operator--(int fakeUselessParamCppSucks);

private:
    int currentNumber;
};

class MyContainer {

public:
    typedef MyIterator iterator;
    MyContainer();
    iterator begin();
    iterator end();
};

#endif //OOP_CPP2_MYCONTAINER_H
