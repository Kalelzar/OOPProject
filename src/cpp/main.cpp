#include<iostream>
#include "src/Date.hpp"
#include "src/collection/RangeBinaryTree.hpp"
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(nullptr));
    RangeBinaryTree<Hotel::Date, int> root{};
    root.populate({2020, 1, 21}, 21);
    root.populate({2020, 1, 15}, 15);


    root.populate({2020, 1, 30}, 30);


    root.populate({2020, 1, 13}, 13);


    root.populate({2020, 1, 18}, 18);


    root.populate({2020, 1, 3}, 3);


    root.populate({2020, 1, 8}, 8);


    root.populate({2020, 1, 25}, 25);

    std::cout << "=================\n";
    root.populate({2020, 2, 10}, 41);
    root.print();
    std::cout << "=================\n";
//        21
//      /   \
//     15    30
//    / \   /  \
//   6  18 25  41
//  / \
// 3  8

    int start = 1 + rand() % 30;
    int end = 1 + rand() % 30;
    if (start > end) std::swap(start, end);
    std::cout << "Start: " << start << " End: " << end << std::endl;
    root.populateWithRange({2020, 1, start}, {2020, 1, end}, (start + end) / 2);
    root.print();
    std::cout << "=================\n";
    unique_ptr<ArrayList<int>> res = root.inRange({2020, 1, 12}, {2020, 1, 19});
    for (int i = 0; i < res->length(); i++) {
        std::cout << res->get(i) << std::endl;
    }


    return 0;
}
