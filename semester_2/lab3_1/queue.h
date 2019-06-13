//
// Created by user on 12.03.19.
//

#ifndef OOP_CPP2_INTERFACE_H
#define OOP_CPP2_INTERFACE_H

#include <list>
#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::list;

typedef enum {
    LOW, NORMAL, HIGH
} ElementPriority;

/** QueueElement structure */
typedef struct {
    string name;
} QueueElement;

/** QueueWithPriority container for QueueElement */
class QueueWithPriority {

private:
    list<QueueElement> lowPriority;
    list<QueueElement> normalPriority;
    list<QueueElement> highPriority;

public:
    /// Constructor
    QueueWithPriority(void);

    /// Desctructor
    ~QueueWithPriority(void);

    /// put char name[] and #ElementPriority priority
    void putElement(const char name[], ElementPriority priority);

    /** Получить элемент из очереди
    метод должен возвращать элемент с наибольшим приоритетом, который был
    добавлен в очередь раньше других*/
    QueueElement getElement(void);

    /// accelerate - set all #QueueElement priority to HIGH and move afrer HIGH elements and before  NORMAL elements
    void accelerate(void);

    /// for human print #QueueWithPriority
    void print_queue(void);

};

#endif //OOP_CPP2_INTERFACE_H
