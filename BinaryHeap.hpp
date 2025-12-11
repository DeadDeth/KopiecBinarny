#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "DynamicArray.hpp"

template<typename T>
class binaryheap {
    dynamicarray<T> data;
    size_t heap_size{0};

    void przekopcowanie_w_gore(size_t index) {
        if (index == 0) return;
        size_t parent = (index - 1) / 2;

        if (data[parent] < data[index]) {
            std::swap(data[parent], data[index]);
            przekopcowanie_w_gore(parent);
        }
    }

    void przekopcowanie_w_dol(size_t index) {
        size_t size = heap_size;
        size_t left_child  = 2 * index + 1;
        size_t right_child = 2 * index + 2;
        size_t best = index;

        if (left_child < size && data[best] < data[left_child]) {
            best = left_child;
        }
        if (right_child < size && data[best] < data[right_child]) {
            best = right_child;
        }

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

    void add(const T& value) {
        if (heap_size == data.get_size()) {
            data.push_back(value);
        }
        else
        {
            data[heap_size] = value;
        }
        przekopcowanie_w_gore(heap_size);
        heap_size++;
    }

    void clear_root() {
        if (heap_size == 0) return;
        heap_size--;
        if (heap_size > 0) {
            data[0] = data[heap_size];
            przekopcowanie_w_dol(0);
        }
    }

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
};
