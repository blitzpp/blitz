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

int main()
{
    Dalmation z;
    Dog* y = &z;

    if (typeid(*y) == typeid(Dalmation))
    {
        return 0;
    }

    return 1;
}

