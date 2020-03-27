#ifndef OOPPROJECT_HASHMAP_HPP
#define OOPPROJECT_HASHMAP_HPP

#include "ArrayList.hpp"
#include<cstdlib>

template<class Key, class Value>
struct Entry{
    Key k{};
    Value v{};
};

//TODO: Maybe don't use an ArrayList but implement a resizable array inside HashMap for more efficient expansion;
template<class Key, class Value>
class HashMap{
private:
    static const unsigned DEFAULT_SIZE = 64;
    static constexpr double EXPAND_FACTOR = 0.2;
    ArrayList<Entry<Key, Value>> al;
    unsigned elemCount{};

    //32-bit FNV-1a hash function
    uint32_t hash(Key* const key) const {
        unsigned char* bytes = (unsigned char*) key;
        uint32_t hash = 2166136261u;
        uint32_t elems = sizeof(*key);
        for(int i = 0; i < elems; i++){
            hash ^= bytes[i];
            hash *= 16777619;
        }

        return hash;
    };

    double loadFactor() const {
        return length()/(double)capacity();
    }

    void copy(HashMap const& other){
        al = other.al; //Should either Key or Value be a pointer of some kind this screws up.
    }

    Entry<Key, Value>* findEntry(Key const& k, ArrayList<Entry<Key, Value>> & al){
        uint32_t hsh = hash(k) % capacity();
        while(al.get(hsh).key != k && al.get(hsh).key != Key{}){
            hsh++;
            if(hsh>=capacity()){
                hsh=0;
            }
        }
        return &al.get(hsh);
    }

    void init(unsigned size){
        al = ArrayList<Entry<Key, Value>>(size);
        al.fill();
    }

    void expand(){
        ArrayList<Entry<Key, Value>> newal(capacity()*2);
        newal.fill();
        for(unsigned i = 0; i < capacity(); i++){
            Entry<Key, Value> entry = al.get(i);
            if(entry.key == Key{}) continue;
            put(entry.key, entry.value, newal);
        }
        al = newal;
    }

    void put(Key const& k, Value const& v, ArrayList<Entry<Key, Value>> &al){
        Entry<Key, Value>* current = findEntry(k, al);
        if(current->key == Key{}){
            if(loadFactor() >= EXPAND_FACTOR){
                expand();
            }
            current->key = k;
            elemCount++;
        }
        current->value = v;
    }

public:

    HashMap(){
        init(DEFAULT_SIZE);
    }

    HashMap(HashMap const& other){
        if(this != &other)
            copy(other);
    }

    HashMap& operator=(HashMap const& other){
        if(this != &other)
            copy(other);
        return *this;
    }

    unsigned length() const {
        return elemCount;
    }

    unique_ptr<Nullable<Value>> get(Key const& k){
        Entry<Key, Value>* entry = findEntry(k, al);
        if(entry->key == Key{}) return std::make_unique<Null<Value>>();
        else return std::make_unique<NotNull<Value>>(entry->value);
    }

    unsigned capacity() const {
        return al.capacity();
    }

    void put(Key const& k, Value const& v) {
        put(k, v, al);
    }


};

#endif //#define OOPPROJECT_HASHMAP_HPP
