//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ARRAYLIST_HPP
#define OOPPROJECT_ARRAYLIST_HPP

#include "IList.hpp"
#include<iostream>
#include<functional>

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

    template <typename B>
    unsigned static partition(unique_ptr<ArrayList<B>> const& array,
                       unsigned from,
                       unsigned to,
                       std::function<bool(const B&, const B&)> comparator){
        B pivot = array->get(to);
        unsigned i = from;
        for(unsigned j = from; j <= to; j++){
            if(comparator(array->get(j), pivot)){
                swap(array->elems[j], array->elems[i]);
                i++;
            }
        }
        swap(array->elems[i], array->elems[to]);
        return i;
    }

    template <typename B>
    void static quickSort(unique_ptr<ArrayList<B>> const& array,
                   unsigned from,
                   unsigned to,
                   std::function<bool(const B&, const B&)> comparator){
        if(from <= to){
            //std::cout<<"Sorting from "<<from<<" to "<<to<<std::endl;
            //std::cout<<"Partitioning!"<<std::endl;
            unsigned part = partition<B>(array, from, to, comparator);
            //std::cout<<"Partition: "<<part<<std::endl;
            //std::cout<<"Quicksort A"<<std::endl;
            if(part != 0) quickSort<B>(array, from, part-1, comparator);
            //std::cout<<"Quicksort B"<<std::endl;
            quickSort<B>(array, part+1, to, comparator);
        }
     }

protected:

    A *elems = nullptr;
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
        if (at < 0) return;

        if (elemCount + 1 > capacity()) {
            expand();
        }

        if (at >= length()) {
            elems[elemCount] = elem;
            elemCount++;
            return;
        }

        for (int i = length(); i > at; i--) {
            elems[i] = elems[i - 1];
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

    void fill() {
        fill(A{});
    }

    void fill(A const &elem) {
        for (int i = 0; i < capacity(); i++) {
            append(elem);
        }
    }

    void append(A const &elem) {
        insert(elem, length());
    }

    void prepend(A const &elem) override {
        insert(elem, 0);
    }

    bool contains(A const &elem) const override {
        for(int i = 0; i < length(); i++){
            if(get(i) == elem) return true;
        }
        return false;
    }

    unsigned remove(const A &elem) {
        unsigned foundAt = 0;
        unsigned index = 0;
        for (unsigned i = 0; i < length(); i++) {
            if (get(i) == elem) {
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
        if (length() == 0) return std::make_unique<Null<A>>();

        A ret = elems[ind >= length() ? length() - 1 : ind];

        if (ind < length() - 1) {
            for (unsigned i = ind; i < length() - 1; i++) {
                elems[i] = elems[i + 1];
            }
        }
        elemCount--;
        return std::make_unique<NotNull<A>>(ret);
    }

    unique_ptr<Nullable<A>> pop() override {
        return removeAt(length() - 1);
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

    unique_ptr<ArrayList<A>> filter(std::function<bool(const A&)> predicate) const {
        unique_ptr<ArrayList<A>> filtered = make_unique<ArrayList<A>>();
        for(int i = 0; i < length(); i++){
            if(predicate(get(i))){
                filtered->append(get(i));
            }
        }
        return filtered;
    }

    void foreach(std::function<void(const A&)> consumer) const {
        for(int i = 0; i < length(); i++){
            consumer(get(i));
        }
    }

    template <typename B>
    unique_ptr<ArrayList<B>> map(std::function<B(const A&)> mapper) const {
        unique_ptr<ArrayList<B>> mapped = make_unique<ArrayList<B>>(capacity());
        for(int i = 0; i < length(); i++){
            mapped->append(mapper(get(i)));
        }
        return mapped;
    }

    unique_ptr<ArrayList<A>> sort(
        std::function<bool(const A&, const A&)> comparator) const {
        unique_ptr<ArrayList<A>> sorted = make_unique<ArrayList<A>>(capacity());
        sorted->appendAll(*this);
        quickSort<A>(sorted, 0, sorted->length()-1, comparator);
        return sorted;
    }

    unique_ptr<ArrayList<A>> intersection(ArrayList<A> const& list) const {
        unique_ptr<ArrayList<A>> res = make_unique<ArrayList<A>>();
        if(length() >= list.length()){
            for(int i = 0; i < length(); i++){
                if(list.contains(get(i))) res->append(get(i));
            }
            return res;
        }else{
            return list.intersection(*this);
        }
    }

    unique_ptr<ArrayList<A>> difference(ArrayList<A> const& list) const {
        unique_ptr<ArrayList<A>> res = make_unique<ArrayList<A>>();
        if(length() >= list.length()){
            for(int i = 0; i < length(); i++){
                if(!list.contains(get(i))) res->append(get(i));
            }
            for(int i = 0; i < list.length(); i++){
                if(!contains(list.get(i)) && !res->contains(list.get(i)))
                    res->append(list.get(i));
            }
            return res;
        }else{
            return list.difference(*this);
        }
    }

    static unsigned getDefaultReservedSpace() { return DEFAULT_RESERVED_SPACE; };
};


#endif //OOPPROJECT_ARRAYLIST_HPP
