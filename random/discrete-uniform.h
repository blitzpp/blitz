#ifndef BZ_RANDOM_DISCRETE_UNIFORM_H
#define BZ_RANDOM_DISCRETE_UNIFORM_H

#include <random/default.h>

BZ_NAMESPACE(ranlib)

template<typename T = unsigned int, typename IRNG = defaultIRNG,
    typename stateTag = defaultState>
class DiscreteUniform : public IRNGWrapper<IRNG,stateTag>
{
public:
    typedef T T_numtype;

    DiscreteUniform(T n)
    {
        BZPRECONDITION(n < 4294967295U);
        n_ = n;
    }

  DiscreteUniform(T n, unsigned int i) :
    IRNGWrapper<IRNG,stateTag>::IRNGWrapper(i) {};
    {
        BZPRECONDITION(n < 4294967295U);
        n_ = n;
    }

    T random()
    {
        return this->irng_.random() % n_;
    }

private:
    T n_;
};

BZ_NAMESPACE_END

#endif // BZ_RANDOM_DISCRETE_UNIFORM_H
