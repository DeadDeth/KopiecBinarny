#include <iostream>
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <cmath>
//pliki .hpp------------------
#include "DynamicArray.hpp"
#include "BinaryHeap.hpp"
//----------------------------



int main()
{
    size_t x = {2};
    for (int i = 1; i < 64; i++)
    {
        x = x * 2;
    }
    size_t wynik = x - 1;
    std::cout << wynik;
}

