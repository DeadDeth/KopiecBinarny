#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "DynamicArray.hpp"   // upewnij się, że tu jest twoja dynamicarray

template<typename T>
class binaryheap {
    dynamicarray<T> data;
    size_t heap_size{0};

    // przekopcowanie w górę (heapify up)
    void przekopcowanie_w_gore(size_t index) {
        if (index == 0) return;                  // root, dalej nie idziemy
        size_t parent = (index - 1) / 2;

        // dla max-heapa: jeśli rodzic < dziecko → zamiana
        if (data[parent] < data[index]) {
            std::swap(data[parent], data[index]);
            przekopcowanie_w_gore(parent);       // rekurencja w górę
        }
    }

    // przekopcowanie w dół (heapify down)
    void przekopcowanie_w_dol(size_t index) {
        size_t n = heap_size;
        size_t left_child  = 2 * index + 1;
        size_t right_child = 2 * index + 2;
        size_t best = index;

        // wybieramy większe z dzieci
        if (left_child < n && data[best] < data[left_child]) {
            best = left_child;
        }
        if (right_child < n && data[best] < data[right_child]) {
            best = right_child;
        }

        // jeśli któreś dziecko jest większe niż current → zamiana i lecimy w dół
        if (best != index) {
            std::swap(data[index], data[best]);
            przekopcowanie_w_dol(best);
        }
    }

public:
    binaryheap() = default;

    void clear() {
        data.clear_all();
        heap_size = 0;
    }

    // dodawanie elementu do kopca (max-heap)
    void add(const T& value) {
        if (heap_size == data.get_size()) {
            data.push_back(value);       // dynamicarray powiększy się jak trzeba
        } else {
            data[heap_size] = value;
        }
        przekopcowanie_w_gore(heap_size);
        heap_size++;
    }

    // usunięcie korzenia (największego elementu)
    void clear_root() {
        if (heap_size == 0) return;      // nic nie ma
        heap_size--;

        if (heap_size > 0) {
            data[0] = data[heap_size];   // ostatni element na górę
            przekopcowanie_w_dol(0);     // naprawa w dół
        }
    }

    // podejrzenie korzenia (max) bez usuwania
    const T& get_root() const {
        if (heap_size != 0) return data[0];
        throw std::out_of_range("nothing in root");
    }

    void display_heap() const {
        if (heap_size == 0) return;
        for (size_t i = 0; i < heap_size; i++) {
            std::cout << data[i] << '\n';
        }
    }

    size_t get_size() const {
        return heap_size;
    }

    bool empty() const {
        return heap_size == 0;
    }
};
