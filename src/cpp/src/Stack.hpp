#ifndef OOPPROJECT_STACK_HPP
#define OOPPROJECT_STACK_HPP

#include "ArrayList.hpp"

template <class A>
class Stack : private ArrayList<A> {
public:
    using ArrayList<A>::length;
    using ArrayList<A>::pop;

    Stack(Stack<A> const &stack) : ArrayList<A>(stack) {}
    Stack(int capacity) : ArrayList<A>(capacity) {}

    Stack() : ArrayList<A>() {}

    void push(A const& elem){
        this->append(elem);
    }

    void pushAll(Stack<A> const& stack){
        for(unsigned i = 0; i < stack.length(); i++)
            push(stack.get(i));
    }

    unique_ptr<Nullable<A>> peek() const {
        return (*this)[length()-1];
    }

};

#endif //OOPPROJECT_STACK_HPP
