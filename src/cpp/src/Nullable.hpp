#ifndef OOPPROJECT_NULLABLE_HPP
#define OOPPROJECT_NULLABLE_HPP

#include "NoValueException.hpp"

template<class A>
class Nullable{
private:
protected:
public:
    virtual ~Nullable() = default;
    virtual bool isEmpty() const = 0;

    bool isDefined() const{
        return !isEmpty();
    }

    virtual A get() const = 0;
    A getOrElse(A const& def) const {
        if(isEmpty()) return def;
        return get();
    }
};

template<class A>
class NotNull : public Nullable<A>{
private:
    A value;
public:
    NotNull(A const& _value){
        value = _value;
    }

    bool isEmpty() const override {
        return false;
    }

    A get() const override {
        return value;
    }
};

template<class A>
class Null: public Nullable<A>{
public:
    bool isEmpty() const override {
        return true;
    }

    A get() const override {
        throw NoValueException();
    }
};


#endif // OOPPROJECT_NULLABLE_HPP