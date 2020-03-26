#include<iostream>
#include <cstring>

#include "ArrayList.hpp"
#include "ArraySet.hpp"
#include "LinkedList.hpp"

#include <chrono>
#include <vector>

using namespace std::chrono;

#define PRINT



void popElements(char type[255], IList<int>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->pop();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Pop " << elements << " elements: " << mili<< std::endl;
}

void accessLast(char type[255], IList<int>* list, int elements){
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
void appendElements(char type[255], IList<int>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->append(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Append " << elements << " elements: " << mili<< std::endl;

    accessLast(type, list, elements);
}

void shiftElements(char type[255], IList<int>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->shift();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Shift " << elements << " elements: " << mili<< std::endl;
}

void accessFirst(char type[255], IList<int>* list, int elements){
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

void prependElements(char type[255], IList<int>* list, int elements){
    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->prepend(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Prepend " << elements << " elements: " << mili<< std::endl;
    accessFirst(type, list, elements);
}

void removeAtMiddle(char type[255], IList<int>* list, int elements){

    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->removeAt(list->length()/2);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Remove " << elements << " elements: " << mili<< std::endl;

}

void accessSeq(char type[255], IList<int>* list, int elements){

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

void insertAtMiddle(char type[255], IList<int>* list, int elements){

    auto start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list->insert(i, list->length()/2);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"("<< type << ") Insert " << elements << " elements: " << mili<< std::endl;
    accessSeq(type, list, elements);
}

void appendElementsVector(int elements){
    auto start = high_resolution_clock::now();
    std::vector<int> list(100000);

    for(int i = 0; i < elements; i++){
        list.push_back(i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"(std::vector) Append " << elements << " elements: " << mili<< std::endl;

    start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list.at(list.size()-1);
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    mili = duration.count();
    std::cout <<"(std::vector) Access Last " << elements << " elements: " << mili<< std::endl;

    start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list.pop_back();
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    mili = duration.count();
    std::cout <<"(std::vector) Pop " << elements << " elements: " << mili<< std::endl;
}


void prependElementsVector(int elements){
    auto start = high_resolution_clock::now();
    std::vector<int> list(elements);

    for(int i = 0; i < elements; i++){
        list.insert(list.begin(), i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"(std::vector) Prepend " << elements << " elements: " << mili<< std::endl;

    start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list.at(0);
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    mili = duration.count();
    std::cout <<"(std::vector) Access First " << elements << " elements: " << mili<< std::endl;

    start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list.erase(list.begin());
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    mili = duration.count();
    std::cout <<"(std::vector) Shift " << elements << " elements: " << mili<< std::endl;
}

void insertMiddleElementsVector(int elements){
    auto start = high_resolution_clock::now();
    std::vector<int> list(elements);

    for(int i = 0; i < elements; i++){
        list.insert(list.begin() + list.size()/2, i);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto mili = duration.count();
    std::cout <<"(std::vector) Insert " << elements << " elements: " << mili<< std::endl;

    start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list.at(i);
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    mili = duration.count();
    std::cout <<"(std::vector) Access Sequential " << elements << " elements: " << mili<< std::endl;

    start = high_resolution_clock::now();

    for(int i = 0; i < elements; i++){
        list.erase(list.begin() + list.size()/2);
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    mili = duration.count();
    std::cout <<"(std::vector) Remove " << elements << " elements: " << mili<< std::endl;
}

int main(){
    IList<int>* list;

    // Linked List

    std::cout<<std::endl;

    list = new LinkedList<int>;
    appendElements("LinkedList", list, 100000);

    list = new LinkedList<int>;
    prependElements("LinkedList", list, 100000);
    delete list;

    list = new LinkedList<int>;
    insertAtMiddle("LinkedList", list, 100000);
    delete list;

    // Array List

    std::cout<<std::endl;

    list = new ArrayList<int>;
    appendElements("ArrayList", list, 100000);
    delete list;

    list = new ArrayList<int>;
    prependElements("ArrayList", list, 100000);
    delete list;

    list = new ArrayList<int>;
    insertAtMiddle("ArrayList", list, 100000);
    delete list;

    // Array List Prealloc

    std::cout<<std::endl;

    list = new ArrayList<int>(100000);
    appendElements("ArrayList(prealloc)", list, 100000);
    delete list;

    list = new ArrayList<int>(100000);
    prependElements("ArrayList(prealloc)", list, 100000);
    delete list;

    list = new ArrayList<int>(100000);
    insertAtMiddle("ArrayList(prealloc)", list, 100000);
    delete list;

    // std::vector

    std::cout<<std::endl;

    appendElementsVector(100000);
    prependElementsVector(100000);
    insertMiddleElementsVector(100000);


}
