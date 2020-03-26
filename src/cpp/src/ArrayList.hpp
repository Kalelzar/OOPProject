//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ARRAYLIST_HPP
#define OOPPROJECT_ARRAYLIST_HPP

#include "IList.hpp"

template<class A>
class ArrayList : public IList<A> {
private:
    static const unsigned DEFAULT_RESERVED_SPACE = 4;
    void free() {
        delete[] elems;
    }

    void create(unsigned reserve) {
        elems = new A[reserve];
        reserved = reserve;
        elemCount = 0;
    }

    void copy(ArrayList<A> const &other) {
        delete[] elems;
        elems = new A[other.capacity()];
        reserved = other.capacity();
        elemCount = 0;
        appendAll(other);
    }


protected:

    A *elems;
    unsigned reserved;
    unsigned elemCount;

    void expand() {
        unsigned newCapacity = capacity() * 2;
        reserved = newCapacity;

        A *newRooms = new A[newCapacity];

        for (int i = 0; i < length(); i++) {
            newRooms[i] = get(i);
        }

        delete[] elems;
        elems = newRooms;
    }
public:
    ArrayList() {
        create(getDefaultReservedSpace());
    }

    explicit ArrayList(unsigned reserved) {
        create(reserved);
    }

    ArrayList(ArrayList<A> const &other) {
        if (&other != this)
            copy(other);
    }

    ArrayList<A> &operator=(ArrayList<A> const &other) {
        if (&other != this)
            copy(other);
        return *this;
    }

    ~ArrayList() {
        free();
    }

    void insert(A const &elem, unsigned at) override {
        if(at < 0) return;

        if (elemCount + 1 > capacity()) {
            expand();
        }

        if(at >= length()){
            elems[elemCount] = elem;
            elemCount++;
            return;
        }

        for(int i = length(); i > at; i--){
            elems[i] = elems[i-1];
        }

        elems[at] = elem;
        elemCount++;
    }

    virtual void append(A const &elem) {
        insert(elem, length());
    }

    void prepend(A const &elem) override {
        insert(elem, 0);
    }

    void remove(const A &elem) {
        bool found = false;
        unsigned index = 0;
        for (unsigned i = 0; i < length(); i++) {
            if (get(i) == elem)
                continue;
            if (index != i) {
                elems[index] = elems[i];
            }
            index++;
        }
        elemCount--;
    }

    void removeAt(unsigned ind) override {
        if(ind < 0) return;

        if(ind < length()-1){
            for(unsigned i = ind; i < length()-1; i++){
                elems[i] = elems[i+1];
            }
        }

        elemCount--;
    }

    void pop() override {
        removeAt(length()-1);
    }

    void shift() override {
        removeAt(0);
    }


    A get(unsigned index) const {
        if(index < 0 ) return elems[0];
        if (index >= length()) return elems[length() - 1];
        return elems[index];
    }

    unsigned length() const final { return elemCount; }

    unsigned capacity() const { return reserved; }

    static unsigned getDefaultReservedSpace() { return DEFAULT_RESERVED_SPACE; };
};


#endif //OOPPROJECT_ARRAYLIST_HPP
