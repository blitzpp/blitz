// static_cast

#include <typeinfo>

class Dog {
public:
    Dog() { }
    virtual void fetch() = 0;
};

class Dalmation : public Dog {
public:
    Dalmation() { }
    virtual void fetch();
};

void Dalmation::fetch()
{
}

void foo(Dalmation&)
{ }

int main()
{
    Dalmation cairo;
    Dog& dog = cairo;

    Dalmation& spotted = static_cast<Dalmation&>(dog);
    foo(spotted);

    return 0;
}

