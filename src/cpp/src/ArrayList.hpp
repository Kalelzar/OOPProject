//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ARRAYLIST_HPP
#define OOPPROJECT_ARRAYLIST_HPP

#include "IList.hpp"
#include<iostream>

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

public:
    ArrayList() {
        create(getDefaultReservedSpace());
    }

    void appendAll(ArrayList<A> const &l) {
        for (int i = 0; i < l.length(); i++) {
            append(l.get(i));
        }
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

    void fill(){
        fill(A{});
    }

    void fill(A const& elem){
        for(int i = 0; i < capacity(); i++){
            append(elem);
        }
    }

    void append(A const &elem) {
        insert(elem, length());
    }

    void prepend(A const &elem) override {
        insert(elem, 0);
    }

    unsigned remove(const A &elem) {
        unsigned foundAt = 0;
        unsigned index = 0;
        for (unsigned i = 0; i < length(); i++) {
            if (get(i) == elem){
                foundAt = i;
                continue;
            }
            if (index != i) {
                elems[index] = elems[i];
            }
            index++;
        }
        elemCount--;
        return foundAt;
    }

    unique_ptr<Nullable<A>> removeAt(unsigned ind) override {
        if(length() == 0) return std::make_unique<Null<A>>();

        A ret = elems[ind >= length() ? length()-1 : ind];

        if(ind < length()-1){
            for(unsigned i = ind; i < length()-1; i++){
                elems[i] = elems[i+1];
            }
        }
        elemCount--;
        return std::make_unique<NotNull<A>>(ret);
    }

    unique_ptr<Nullable<A>> pop() override {
        return removeAt(length()-1);
    }

    unique_ptr<Nullable<A>> shift() override {
        return removeAt(0);
    }


    A get(unsigned index) const {
        if (index >= length()) return elems[length() - 1];
        return elems[index];
    }

    unsigned length() const final { return elemCount; }

    unsigned capacity() const { return reserved; }

    void clear() override {
        free();
        create(getDefaultReservedSpace());
    }

    static unsigned getDefaultReservedSpace() { return DEFAULT_RESERVED_SPACE; };
};


#endif //OOPPROJECT_ARRAYLIST_HPP
