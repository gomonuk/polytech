//
// Created by gomonuk on 20.03.19.
//

#include  "queue.h"
#include <iostream>

using std::endl;
using std::cout;

int main() {
    QueueWithPriority queue;
    queue.putElement("LOW_1", LOW);
    queue.putElement("LOW_2", LOW);
    queue.putElement("NORMAL_1", NORMAL);
    queue.putElement("NORMAL_2", NORMAL);
    queue.putElement("HIGH_1", HIGH);

    // Теперь очередь выглядит так:
    // HIGH_1, NORMAL_1, NORMAL_2, LOW_1, LOW_2

    cout << queue.getElement().name << endl;  // HIGH_1
    cout << queue.getElement().name << endl;  // NORMAL_1
    queue.accelerate();
    cout << queue.getElement().name << endl;  // LOW1

    return 0;
}
