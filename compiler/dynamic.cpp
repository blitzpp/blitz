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
    Dalmation cairo;
    Dog& doggie = cairo;
         
    if (dynamic_cast<Dalmation*>(&doggie))
    {
        return 0;
    }

    return 1;
}

