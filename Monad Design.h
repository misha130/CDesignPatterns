#include <QString>
#include <QDebug>

#ifndef MONAD_H
#define MONAD_H

class monad
{

public:

    struct Address{
        QString* house_name = nullptr;
    };
    struct Person{
        Address* address = nullptr;
    };

    monad();
    void print_house_name(Person* p);
};


#endif // MONAD_H
