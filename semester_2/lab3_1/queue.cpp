//
// Created by gomonuk on 11.03.19.
//

/*
В очередь могут быть добавлены элементы,
каждому элементу при добавлении присваивается один из трех уровней приоритета (low, normal, high)
Элементы из очереди извлекаются в соответствии с их приоритетами
(сначала извлекаются элементы с приоритетом high, потом normal, потом low),
 элементы с одинаковыми приоритетами извлекаются из очереди в порядки их поступления.

В очереди также может происходить операция акселерации – все элементы с приоритетом low
 находящиеся в момент акселерации в очереди увеличивают свой приоритет до high
и «обгоняют» элементы с приоритетом normal.

Реализовать этот класс, используя list или deque. Объяснить свой выбор.
Протестируете программу, добавьте отладочный вывод, показывающий, что  класс работает правильно.
*/

#include  "queue.h"
#include <iostream>

using std::string;
using std::ifstream;
using std::endl;
using std::cout;


/// Constructor
QueueWithPriority::QueueWithPriority() {
    cout << "Queue was created" << endl;

}


/// Destructor
QueueWithPriority::~QueueWithPriority() {
    lowPriority.clear();
    normalPriority.clear();
    highPriority.clear();
    cout << "Queue was destroyed" << endl;
}


void QueueWithPriority::putElement(const char *name, ElementPriority priority) {
    QueueElement element;
    element.name = string(name);

    switch (priority) {
        case LOW:
            QueueWithPriority::lowPriority.push_back(element);
            break;

        case NORMAL:
            QueueWithPriority::normalPriority.push_back(element);
            break;

        case HIGH:
            QueueWithPriority::highPriority.push_back(element);
            break;
    }
}


QueueElement QueueWithPriority::getElement() {
    QueueElement returned;

    if (not highPriority.empty()) {
        returned = highPriority.front();
        highPriority.pop_front();
    }
    else if (not normalPriority.empty()) {
        returned = normalPriority.front();
        normalPriority.pop_front();
    }
    else if (not lowPriority.empty()) {
        returned = lowPriority.front();
        lowPriority.pop_front();
    }

    return returned;
}


void QueueWithPriority::accelerate() {
    if (not lowPriority.empty()) {
        highPriority.splice(highPriority.end(), lowPriority);
        lowPriority.clear();
    }
}

