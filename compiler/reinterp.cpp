// Reinterpret cast

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

class Unrelated {
public:
    Unrelated() { }

};

void foo(Unrelated&)
{ }

int main()
{
    Dalmation cairo;
    Dog& dog = cairo;
    Unrelated& eek = reinterpret_cast<Unrelated&>(dog);
    foo(eek);
    return 0;
}

