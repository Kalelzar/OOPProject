#include<iostream>
#include "HashMap.hpp"
#include <random>
#include <chrono>

void put(int elems) {
    HashMap<int, int> map;
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < elems; i++) {
            map.put(i, i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Putting " << elems << " elements took " << dur << "ms" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < elems; i++) {
            if(map.get(i)->get() != i) throw i;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Linear Accessing " << elems << " elements took " << dur << "ms" << std::endl;
    }




}


int main() {

    put(10000000);

    std::cin.get();


    return 0;
}
