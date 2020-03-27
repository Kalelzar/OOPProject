//
// Created by Kalelzar on 26/03/2020.
//

#ifndef OOPPROJECT_ILIST_HPP
#define OOPPROJECT_ILIST_HPP

#include "Nullable.hpp"
#include<memory>

template<class A>
class IList {
private:

public:
    virtual void append(A const &elem)  = 0;
    virtual void prepend(A const &elem) = 0;

    virtual void insert(A const &elem, unsigned at) = 0;

    void appendAll(IList<A> const &l) {
        for (int i = 0; i < l.length(); i++) {
            append(l.get(i));
        }
    }

    virtual ~IList() = default;

    unique_ptr<Nullable<A>> operator[](unsigned index) const {
        if(index < length()) return std::make_unique<NotNull<A>>(get(index));
        return std::make_unique<Null<A>>();
    }

    void prependAll(IList<A> const &l){
        for (int i = 0; i < l.length(); i++) {
            prepend(l.get(i));
        }
    }

    virtual unsigned remove(const A& elem) = 0;

    virtual unique_ptr<Nullable<A>> removeAt(unsigned ind) = 0;
    virtual unique_ptr<Nullable<A>> pop() = 0;
    virtual unique_ptr<Nullable<A>> shift() = 0;

    virtual A get(unsigned index) const = 0;
    virtual void clear() = 0;

    bool isEmpty() const {
        return length()==0;
    }




    virtual unsigned length() const = 0;
};

#endif //OOPPROJECT_ILIST_HPP
