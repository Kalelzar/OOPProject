#ifndef OOPPROJECT_HASHMAP_HPP
#define OOPPROJECT_HASHMAP_HPP

#include "ArrayList.hpp"
#include <cstdlib>

template<class Key, class Value>
struct Entry {
    Key key{};
    Value value{};
    bool uninit=true;

    bool operator==(Entry<Key, Value> const& other) const {
        return key == other.key && value == other.value && uninit == other.uninit;
    }

    bool operator!=(Entry<Key, Value> const& other) const {
        return !(*this == other);
    }
};

//TODO: Maybe don't use an ArrayList but implement a resizable array inside HashMap for more efficient expansion;
template<class Key, class Value>
class HashMap {
private:
    typedef Entry<Key, Value> SpecEntry;
    static const unsigned DEFAULT_SIZE = 64;
    static constexpr double EXPAND_FACTOR = 0.8;
    SpecEntry* array;
    unsigned reserved{};
    unsigned elemCount{};

    //32-bit FNV-1a hash function
    uint32_t hash(const Key *key) const {
        unsigned char *bytes = (unsigned char *) key;
        uint32_t hash = 2166136261u;
        uint32_t elems = sizeof(*key);
        for (int i = 0; i < elems; i++) {
            hash ^= bytes[i];
            hash *= 16777619;
        }

        return hash;
    };

    double loadFactor() const {
        return length()/(double)capacity();
    }


    void copy(HashMap<Key, Value> const &other) {
        delete[] array;
        array = new SpecEntry[other.capacity()];
        reserved = other.capacity();
        elemCount = 0;
        putAll(other);
    }

    unsigned findEntry(Key const &k) const {

        if(k==103){
            uint32_t hsh = hash(&k) % capacity();

            while (array[hsh].key != k && !array[hsh].uninit) {
                hsh++;
                if (hsh >= capacity()) {
                    hsh = 0;
                }
            }
            return hsh;
        }else{
            uint32_t hsh = hash(&k) % capacity();

            while (array[hsh].key != k && !array[hsh].uninit) {
                hsh++;
                if (hsh >= capacity()) {
                    hsh = 0;
                }
            }
            return hsh;

        }
    }

    void init(unsigned size) {
        array = new SpecEntry[size];
        reserved = size;
        elemCount = 0;
        for(int i = 0; i < size; i++){
            array[i] = SpecEntry{};
        }
    }

    void expand() {
        SpecEntry* const newarray = new SpecEntry[capacity()*2];

        for(int i = 0; i < capacity()*2; i++){
            newarray[i] = SpecEntry{};
        }

        const SpecEntry* const oldarray = array;

        array = newarray;
        reserved = capacity()*2;
        elemCount = 0;

        putAll(oldarray, capacity()/2);
        delete [] oldarray;
    }

    void putAll(const SpecEntry * other, unsigned size){
        for(int i = 0; i < size; i++){
            if(other[i].uninit) continue;

            put(other[i].key, other[i].value);
        }
    }

public:

    void putAll(HashMap<Key, Value> const& other){
        putAll(other.array, other.length());
    }

    HashMap() {
        init(DEFAULT_SIZE);
    }

    void print(){
        for(int i = 0; i < capacity(); i++){
            std::cout<<"("<<array[i].key<<", "<<array[i].value<<") - "<<std::boolalpha<<array[i].uninit<<std::endl;
        }
    }

    HashMap(HashMap<Key, Value> const &other) {
        if (this != &other)
            copy(other);
    }

    HashMap<Key, Value> &operator=(HashMap<Key, Value> const &other) {
        if (this == &other)
            copy(other);
        return *this;
    }

    unsigned length() const {
        return elemCount;
    }

    unique_ptr <Nullable<Value>> get(Key const &k) {
        unsigned hsh = findEntry(k);
        if (array[hsh].uninit) return std::make_unique<Null<Value>>();
        else return std::make_unique<NotNull<Value>>(array[hsh].value);
    }

    unsigned capacity() const {
        return reserved;
    }

    void put(Key const &k, Value const &v) {
        if (loadFactor() >= EXPAND_FACTOR) {
            expand();
        }
        unsigned hsh = findEntry(k);
        if (array[hsh].uninit) {
            array[hsh].key = k;
            array[hsh].uninit = false;
            elemCount++;
        }
        array[hsh].value = v;
    }


};

#endif //#define OOPPROJECT_HASHMAP_HPP
