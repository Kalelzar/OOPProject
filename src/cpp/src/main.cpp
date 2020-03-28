#include<iostream>
#include "BinaryTree.hpp"
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

int main() {

    srand(time(nullptr));

    int min = 0;
    int max = 100000;

    int nodes = 10000;

    int randnum = min + rand() % max;
    BinaryNode<int, int>* root = new BinaryNode<int, int>(randnum, randnum);
    {
        auto begin = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < nodes; i++){
            randnum = min + rand() % max;
            root->populate(randnum, randnum);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<"Populating the tree with "<<nodes<<" random entries took "<<duration.count()<<"ms\n";
    }

    {
        auto begin = std::chrono::high_resolution_clock::now();

        int smin = min + rand() % max;
        int smax = min + rand() % max;

        if(smin > smax) swap(smin, smax);

        unique_ptr<ArrayList<int>> res = root->allInRange(min, max);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout<<"Finding a random range in "<<nodes<<" random entries took "<<duration.count()<<"ms\n";
    }


        //for(unsigned i = 0; i < res->length(); i++){
        //    std::cout<<">> "<<res->get(i)<<"\n";
        //}

        delete root;

    return 0;
}
