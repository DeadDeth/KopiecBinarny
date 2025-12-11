#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <functional>
#include <string>
#include <stdexcept>
#include <cmath>
#include <fstream>
//pliki .hpp------------------
#include "DynamicArray.hpp"
#include "BinaryHeap.hpp"
//----------------------------

int sizes[3];
void create_size() {
    for (int i = 0; i < 3; i++) {
        int x = pow(10,i);
        sizes[i] = 10000 * x;
    }
}

void pomiar_trzy(binaryheap<int>* bh) {
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0,10000000);
    using clock = std::chrono::steady_clock;
    clock::time_point t0, t1;
    double ms = 0;
    double opms = 0;
    t0 = clock::now();
    for (int j = 0; j < sizes[2]; j++) {
        bh->add(dist(rng));
    }
    t1 = clock::now();
    ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    opms = 1000000/ms;

    std::cout << "Pomiary dodawania 1000000 elementow: ";
    std::cout << ms << " ms" << "   co daje:  " << opms <<" op/ms"<<std::endl;

    t0 = clock::now();
    for (int j = 0; j < sizes[2]; j++) {
        bh->clear_root();
    }
    t1 = clock::now();
    ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    opms = 1000000/ms;

    std::cout << "Pomiary usuwania 1000000 elementow: ";
    std::cout << ms << " ms" << "   co daje:  " << opms <<" op/ms"<<std::endl;

    bh->clear();
}

void pomiar_dwa(binaryheap<int>* bh) {

    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0,10000000);
    using clock = std::chrono::steady_clock;
    clock::time_point t0, t1;
    double ms = 0;
    double opms = 0;
    t0 = clock::now();
    for (int j = 0; j < sizes[1]; j++) {
        bh->add(dist(rng));
    }
    t1 = clock::now();
    ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    opms = 100000/ms;

    std::cout << "Pomiary dodawania 100000 elementow: ";
    std::cout << ms << " ms" << "   co daje:  " << opms <<" op/ms"<<std::endl;

    t0 = clock::now();
    for (int j = 0; j < sizes[1]; j++) {
        bh->clear_root();
    }
    t1 = clock::now();
    ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    opms = 100000/ms;

    std::cout << "Pomiary usuwania 100000 elementow: ";
    std::cout << ms << " ms" << "   co daje:  " << opms <<" op/ms"<<std::endl;

    bh->clear();
}

void pomiar_jeden(binaryheap<int>* bh) {

    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0,10000000);
    using clock = std::chrono::steady_clock;
    clock::time_point t0, t1;
    double ms = 0;
    double opms = 0;
    t0 = clock::now();
    for (int j = 0; j < sizes[0]; j++) {
        bh->add(dist(rng));
    }
    t1 = clock::now();
    ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    opms = 10000/ms;

    std::cout << "Pomiary dodawania 10000 elementow: ";
    std::cout << ms << " ms" << "   co daje:  " << opms <<" op/ms"<<std::endl;

    t0 = clock::now();
    for (int j = 0; j < sizes[0]; j++) {
        bh->clear_root();
    }
    t1 = clock::now();
    ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    opms = 10000/ms;

    std::cout << "Pomiary usuwania 10000 elementow: ";
    std::cout << ms << " ms" << "   co daje:  " << opms <<" op/ms"<<std::endl;

    bh->clear();
}

void graphviz(binaryheap<int>* bh) {

    for (int i = 0; i < 100; i++) {
        bh->add(i);
    }

    std::ofstream out("grapviz.txt");

    out << "digraph Heap {\n";

    size_t n = bh->get_size();
    for (size_t i = 0; i < n; i++) {
        size_t left = 2*i + 1;
        size_t right = 2*i + 2;

        if (left < n)
            out << "  " << i << " -> " << left << ";\n";
        if (right < n)
            out << "  " << i << " -> " << right << ";\n";
    }

    out << "}\n";

    bh->clear();
} // robienie wykresu do graphviz


int main()
{
    binaryheap<int> bh;
    create_size();

    pomiar_jeden(&bh);
    std::cout<<"-------------------------------------------------\n";
    pomiar_dwa(&bh);
    std::cout<<"-------------------------------------------------\n";
    pomiar_trzy(&bh);

    graphviz(&bh);
    return 0;
}