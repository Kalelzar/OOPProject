//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_ARRAYLIST_HPP
#define OOPPROJECT_ARRAYLIST_HPP

#include "IList.hpp"
#include <functional>
#include <iostream>

/**
 * An implementation of a list backed by a resizable array.
 * Due to some quirks of the implementation, type A
 * must implement operator==.
 */
template <class A> class ArrayList : public IList<A> {
private:
  static const unsigned DEFAULT_RESERVED_SPACE = 4;

  /**
   * Frees the resizable array.
   */
  void free() { delete[] elems; }

  /**
   * Initializes the list with the given size.
   * @param reserve the starting size to allocate for the resizable array
   */
  void create(unsigned reserve) {
    elems = new A[reserve];
    reserved = reserve;
    elemCount = 0;
  }

  /**
   * Copies another list into this one.
   * @param other the other list.
   */
  void copy(ArrayList<A> const &other) {
    delete[] elems;
    elems = new A[other.capacity()];
    reserved = other.capacity();
    elemCount = 0;
    appendAll(other);
  }

  /**
   * The partition function of the quicksort algorithm.
   *
   * @tparam B the type of the elements in the list
   * @param array the list to sort
   * @param from the start of the range to partition in
   * @param to the end of the range to partition in
   * @param comparator the function with which to compare elements
   * @return the pivot
   */
  template <typename B>
  unsigned static partition(
      std::unique_ptr<ArrayList<B>> const &array, unsigned from, unsigned to,
      std::function<bool(const B &, const B &)> comparator) {
    B pivot = array->get(to);
    unsigned i = from;
    for (unsigned j = from; j <= to; j++) {
      if (comparator(array->get(j), pivot)) {
          std::swap(array->elems[j], array->elems[i]);
        i++;
      }
    }
    std::swap(array->elems[i], array->elems[to]);
    return i;
  }

  /**
   * An implementation of the quicksort algorithm that allows for the use
   * of an arbitrary comparison function.
   * @tparam B the type of the elements in the list
   * @param array the list to sort
   * @param from the start of the range to sort in
   * @param to the end of the range to sort in
   * @param comparator the function with which to compare elements
   */
  template <typename B>
  void static quickSort(std::unique_ptr<ArrayList<B>> const &array,
                        unsigned from, unsigned to,
                        std::function<bool(const B &, const B &)> comparator) {
    if (from <= to) {
      unsigned part = partition<B>(array, from, to, comparator);
      if (part != 0)
        quickSort<B>(array, from, part - 1, comparator);
      quickSort<B>(array, part + 1, to, comparator);
    }
  }

protected:
  A *elems = nullptr;
  unsigned reserved;
  unsigned elemCount;

public:
  ArrayList() { create(getDefaultReservedSpace()); }

  /**
   * Prepend all elements of the given list to this one.
   * Very slow for large lists.
   * @param l the list to prepend
   */
  void prependAll(ArrayList<A> const &l) {
    for (int i = 0; i < l.length(); i++) {
      prepend(l.get(i));
    }
  }

  /**
   * Append all elements of the given list to this one.
   * @param l the list to append
   */
  void appendAll(ArrayList<A> const &l) {
    for (int i = 0; i < l.length(); i++) {
      append(l.get(i));
    }
  }

  explicit ArrayList(unsigned reserved) { create(reserved); }

  ArrayList(ArrayList<A> const &other) {
    if (&other != this)
      copy(other);
  }

  ArrayList<A> &operator=(ArrayList<A> const &other) {
    if (&other != this)
      copy(other);
    return *this;
  }

  ~ArrayList() { free(); }

  void insert(A const &elem, unsigned at) override {
    if (elemCount + 1 > capacity()) {
      expand(); // Expand the list if inserting one more element would
                // exceed the dynamic array's current capacity
    }

    if (at >= length()) { // Assume that indexes greater or equal to the
      // list's length mean an insertion at the end of
      // the list.
      elems[elemCount] = elem;
      elemCount++;
      return;
    }

    for (int i = length(); i > at; i--) {
      elems[i] = elems[i - 1]; // Shift all elements from index at to
                               // length() left by one to make space for
                               // the new element
    }

    elems[at] = elem;
    elemCount++;
  }

  /**
   * Double the capacity of the array.
   */
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
  /// Fill the array with elements created with the default constructor
  void fill() { fill(A{}); }
  /// Fill the entire array with the given element

  void fill(A const &elem) {
    for (int i = 0; i < capacity(); i++) {
      append(elem);
    }
  }

  void append(A const &elem) override { insert(elem, length()); }

  void prepend(A const &elem) override { insert(elem, 0); }

  bool contains(A const &elem) const override {
    for (int i = 0; i < length(); i++) {
      if (get(i) == elem)
        return true;
    }
    return false;
  }

  unsigned remove(const A &elem) override {
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

  std::unique_ptr<Nullable<A>> removeAt(unsigned ind) override {
    if (length() == 0)
      return std::make_unique<Null<A>>(); // No element to remove
    // so just return null

    A ret =
        elems[ind >= length() ? length() - 1
                              : ind]; // Save the element that will be removed

    if (ind < length() - 1) {
      for (unsigned i = ind; i < length() - 1; i++) {
        elems[i] = elems[i + 1];
      }
    }
    elemCount--;
    return std::make_unique<NotNull<A>>(ret);
  }

  std::unique_ptr<Nullable<A>> pop() override { return removeAt(length() - 1); }

  std::unique_ptr<Nullable<A>> shift() override { return removeAt(0); }

  A get(unsigned index) const override {
    if (index >= length())
      return elems[length() - 1];
    return elems[index];
  }

  /// return the amount of elements currently in the array

  unsigned length() const final { return elemCount; }
  /// return the current maximum capacity of the array

  unsigned capacity() const { return reserved; }

  void clear() override {
    free();
    create(getDefaultReservedSpace());
  }

  /**
   * Return a new ArrayList containing all elements in the current list that
   * match the provided predicate
   * @param predicate the condition that elements need to satisfy
   * @return the filtered list
   */
  std::unique_ptr<ArrayList<A>>
  filter(std::function<bool(const A &)> predicate) const {
    std::unique_ptr<ArrayList<A>> filtered = std::make_unique<ArrayList<A>>();
    for (int i = 0; i < length(); i++) {
      if (predicate(get(i))) {
        filtered->append(get(i));
      }
    }
    return filtered;
  }

  /**
   * Applies the provided function to each element of the list in order.
   * @param consumer the function to apply
   */
  void foreach (std::function<void(const A &)> consumer) const {
    for (int i = 0; i < length(); i++) {
      consumer(get(i));
    }
  }

  /**
   * Return a new ArrayList containing the result of applying
   * the provided mapping function to each element of the list
   * in order
   * @tparam B the type of elements in the new list
   * @param mapper the mapping function
   * @return the new ArrayList
   */
  template <typename B>
  std::unique_ptr<ArrayList<B>> map(std::function<B(const A &)> mapper) const {
    std::unique_ptr<ArrayList<B>> mapped =
        std::make_unique<ArrayList<B>>(capacity());
    for (int i = 0; i < length(); i++) {
      mapped->append(mapper(get(i)));
    }
    return mapped;
  }

  /**
   * Returns a new ArrayList containing the elements of this
   * list sorted with the QuickSort algorithm by the provided
   * comparison function
   * @param comparator the comparison function
   * @return the sorted list
   */
  std::unique_ptr<ArrayList<A>>
  sort(std::function<bool(const A &, const A &)> comparator) const {
    std::unique_ptr<ArrayList<A>> sorted =
        std::make_unique<ArrayList<A>>(capacity());
    if (length() == 0)
      return sorted;
    sorted->appendAll(*this);
    quickSort<A>(sorted, 0, sorted->length() - 1, comparator);
    return sorted;
  }

  /**
   * Convert a list of lists into a single list containing all elements of the
   * previously contained lists.
   */
  template <typename B,
            typename = std::enable_if_t<std::is_base_of<IList<B>, A>::value>>
  std::unique_ptr<ArrayList<B>> flatten() {
    std::unique_ptr<ArrayList<B>> res = std::make_unique<ArrayList<B>>();
    for (int i = 0; i < length(); i++) {
      res->appendAll(get(i));
    }
    return res;
  }

  /**
   * Returns the set intersection of this list and the provided one
   * @param list the other list
   * @return the set intersection of the two lists
   */
  std::unique_ptr<ArrayList<A>> intersection(ArrayList<A> const &list) const {
    std::unique_ptr<ArrayList<A>> res = std::make_unique<ArrayList<A>>();
    if (length() >= list.length()) {
      for (int i = 0; i < length(); i++) {
        if (list.contains(get(i)))
          res->append(get(i));
      }
      return res;
    } else {
      return list.intersection(*this);
    }
  }

  /**
   * Returns the set difference of this list and the provided one
   * @param list the other list
   * @return the set difference of the two lists
   */
  std::unique_ptr<ArrayList<A>> difference(ArrayList<A> const &list) const {
    std::unique_ptr<ArrayList<A>> res = std::make_unique<ArrayList<A>>();
    if (length() >= list.length()) {
      for (int i = 0; i < length(); i++) {
        if (!list.contains(get(i)))
          res->append(get(i));
      }
      for (int i = 0; i < list.length(); i++) {
        if (!contains(list.get(i)) && !res->contains(list.get(i)))
          res->append(list.get(i));
      }
      return res;
    } else {
      return list.difference(*this);
    }
  }

  bool operator==(ArrayList<A> const &other) {
    if (length() != other.length())
      return false;
    for (int i = 0; i < length(); i++) {
      if (!other.contains(get(i)) || !contains(other.get(i)))
        return false;
    }
    return true;
  }

  static unsigned getDefaultReservedSpace() { return DEFAULT_RESERVED_SPACE; };
};

#endif // OOPPROJECT_ARRAYLIST_HPP
