#ifndef OOPPROJECT_HASHMAP_HPP
#define OOPPROJECT_HASHMAP_HPP

#include "ArrayList.hpp"
#include <cstdlib>
#include <type_traits>

template<class Key, class Value>
struct Entry {
    Key key{};
    Value value{};
    bool uninit = true;

    bool operator==(Entry<Key, Value> const &other) const {
        return key == other.key && value == other.value && uninit == other.uninit;
    }

    bool operator!=(Entry<Key, Value> const &other) const {
        return !(*this == other);
    }
};

template<class Key, class Value>
class HashMap {
private:
    typedef Entry<Key, Value> SpecEntry;
    static const unsigned DEFAULT_SIZE = 16;
    static constexpr double EXPAND_FACTOR = 0.8;
    SpecEntry *array;
    unsigned reserved{};
    unsigned elemCount{};

    //32-bit FNV-1a hash function
    template<typename T, typename std::enable_if_t<!std::is_pointer<T>::value> * = nullptr>
    uint32_t hash(const T *key) const {

        unsigned char *bytes = (unsigned char *) key;
        uint32_t hash = 2166136261u;
        uint32_t elems = sizeof(*key);
        for (int i = 0; i < elems; i++) {
            hash ^= bytes[i];
            hash *= 16777619;
        }

        return hash;
    };

    template<typename T, typename std::enable_if_t<std::is_pointer<T>::value> * = nullptr>
    uint32_t hash(const T *key) const {

        unsigned char *bytes = (unsigned char *) *key;
        uint32_t hash = 2166136261u;
        uint32_t elems = strlen(*key);
        for (int i = 0; i < elems; i++) {
            hash ^= bytes[i];
            hash *= 16777619;
        }

        return hash;
    };

    double loadFactor() const {
        return length() / (double) capacity();
    }


    void copy(HashMap<Key, Value> const &other) {

        array = new SpecEntry[other.capacity()];
        reserved = other.capacity();
        elemCount = 0;

        putAll(other);
    }

    unsigned findEntry(Key const &k) const {

        uint32_t hsh = hash(&k) % capacity();

        while (array[hsh].key != k && !array[hsh].uninit) {
            hsh++;
            if (hsh >= capacity()) {
                hsh = 0;
            }
        }
        return hsh;
    }

    void init(unsigned size) {
        array = new SpecEntry[size];
        reserved = size;
        elemCount = 0;
        for (int i = 0; i < size; i++) {
            array[i] = SpecEntry{};
        }
    }

    void expand() {
        SpecEntry *const newarray = new SpecEntry[capacity() * 2];

        unsigned oldCapacity = capacity();

        for (int i = 0; i < capacity() * 2; i++) {
            newarray[i] = SpecEntry{};
        }

        const SpecEntry *const oldarray = array;

        array = newarray;
        reserved = capacity() * 2;
        elemCount = 0;

        putAll(oldarray, oldCapacity);

        //delete[] newarray;
        delete[] oldarray;
    }

    void putAll(const SpecEntry *other, unsigned size) {
        for (unsigned i = 0; i < size; i++) {
            if (other[i].uninit) continue;
            put(other[i].key, other[i].value);
        }
    }

    void free() {
        delete[] array;
        reserved = 0;
        elemCount = 0;
    }

public:

    void putAll(HashMap<Key, Value> const &other) {
        putAll(other.array, other.capacity());
    }

    HashMap() {
        init(DEFAULT_SIZE);
    }

    ~HashMap() {
        free();
    }

    HashMap(HashMap<Key, Value> const &other) {
        if (this != &other)
            copy(other);
    }

    HashMap<Key, Value> &operator=(HashMap<Key, Value> const &other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    unsigned length() const {
        return elemCount;
    }

    unique_ptr<Nullable<Value>> get(Key const &k) {
        unsigned hsh = findEntry(k);


        if (array[hsh].uninit) {

            return std::make_unique<Null<Value>>();
        } else return std::make_unique<NotNull<Value>>(array[hsh].value);
    }

    bool contains(Key const &k) {
        unsigned hsh = findEntry(k);
        if (array[hsh].uninit) return false;
        else return true;
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

    /**
     * Removes the given key from the hash map by setting it's corresponding entry's
     * as uninitialized. This will probably not free any memory associated with the Key, Value pair
     * Such a thing should be handled by the caller.
     *
     * @param k the key to remove
     */
    void remove(Key const &k) {
        unsigned hsh = findEntry(k);
        if (array[hsh].uninit) return;
        array[hsh].uninit = true;
        elemCount--;
    }

    /**
     * Returns a constant reference to the underlying entry list
     * for the purposes of iteration
     * @return the entries
     */
    const SpecEntry *underlying() const {
        return array;
    }

    unique_ptr<ArrayList<Value>> values() const {
        unique_ptr<ArrayList<Value>> list = make_unique<ArrayList<Value>>(length());
        for (int i = 0; i < capacity(); i++) {
            if (!array[i].uninit) {
                list->append(array[i].value);
            }
        }

        return list;
    }

    unique_ptr<ArrayList<Key>> keys() const {
        unique_ptr<ArrayList<Key>> list = make_unique<ArrayList<Key>>(length());
        for (int i = 0; i < capacity(); i++) {
            if (!array[i].uninit) {
                list->append(array[i].key);
            }
        }

        return list;
    }

    /**
     * Clears the contents of the hash map.
     */
    void clear() {
        free();
        init(DEFAULT_SIZE);
    }
};


#endif //#define OOPPROJECT_HASHMAP_HPP
