#include<iostream>
#include <cstring>

#include "Room.hpp"
#include "ArrayList.hpp"
#include "ArraySet.hpp"
#include "LinkedList.hpp"

#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace Hotel;

#define PRINT



void popElements(char type[255], IList<Room>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->pop();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Pop " << elements << " elements: " << mili<< std::endl;
}

void accessLast(char type[255], IList<Room>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->get(list->length()-1);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Access Last " << elements << " elements: " << mili<< std::endl;

    popElements(type, list, elements);
}
void appendElements(char type[255], IList<Room>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->append(Room(i, 1));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Append " << elements << " elements: " << mili<< std::endl;

    accessLast(type, list, elements);
}

void shiftElements(char type[255], IList<Room>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->shift();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Shift " << elements << " elements: " << mili<< std::endl;
}

void accessFirst(char type[255], IList<Room>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->get(0);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Access First " << elements << " elements: " << mili<< std::endl;
    shiftElements(type, list, elements);
}

void prependElements(char type[255], IList<Room>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->prepend(Room(i, 1));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Prepend " << elements << " elements: " << mili<< std::endl;
    accessFirst(type, list, elements);
}

void removeAtMiddle(char type[255], IList<Room>* list, int elements){

    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->removeAt(list->length()/2);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Remove " << elements << " elements: " << mili<< std::endl;

}

void accessSeq(char type[255], IList<Room>* list, int elements){

    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->get(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Access Sequential " << elements << " elements: " << mili<< std::endl;
    removeAtMiddle(type, list, elements);
}

void insertAtMiddle(char type[255], IList<Room>* list, int elements){

    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->insert(Room(i,1), list->length()/2);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Insert " << elements << " elements: " << mili<< std::endl;
    accessSeq(type, list, elements);
}

int main(){
    IList<Room>* list;

    // Linked List

    std::cout<<std::endl;

    list = new LinkedList<Room>;
    appendElements("LinkedList", list, 100000);

    list = new LinkedList<Room>;
    prependElements("LinkedList", list, 100000);
    delete list;

    list = new LinkedList<Room>;
    insertAtMiddle("LinkedList", list, 100000);
    delete list;

    // Array List

    std::cout<<std::endl;

    list = new ArrayList<Room>;
    appendElements("ArrayList", list, 100000);
    delete list;

    list = new ArrayList<Room>;
    prependElements("ArrayList", list, 100000);
    delete list;

    list = new ArrayList<Room>;
    insertAtMiddle("ArrayList", list, 100000);
    delete list;

    // Array List Prealloc

    std::cout<<std::endl;

    list = new ArrayList<Room>(100000);
    appendElements("ArrayList(prealloc)", list, 100000);
    delete list;

    list = new ArrayList<Room>(100000);
    prependElements("ArrayList(prealloc)", list, 100000);
    delete list;

    list = new ArrayList<Room>(100000);
    insertAtMiddle("ArrayList(prealloc)", list, 100000);
    delete list;



}
