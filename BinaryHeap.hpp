#pragma once

template<typename T>
class binaryheap {
    dynamicarray<T> data;
    size_t heap_size{0};
    template<typename Comp>
    void przekopcowanie_w_gore(size_t index, Comp comp) {
        if (index == 0) return;
        size_t parent = (index - 1) / 2;

        if (comp(data[parent], data[index])) {
            std::swap(data[parent], data[index]);
            przekopcowanie_w_gore(parent,comp);
        }
    }

    template<typename Comp>
    void przekopcowanie_w_dol(size_t index, Comp comp) {
        size_t n = heap_size;
        size_t left_child = 2 * index + 1;
        size_t right_child = 2 * index + 2;
        size_t best = index;

        if (left_child < n && comp(data[best], data[left_child])) {
            best = left_child;
        }
        if (right_child < n && comp(data[best], data[right_child])) {
            best = right_child;
        }
        if (best != index) {
            std::swap(data[index], data[best]);
            przekopcowanie_w_dol(best, comp);
        }
    }

public:
    binaryheap() = default;
    void clear() {
        data.clear_all();
        heap_size = 0;
    }

    template<typename Comp>
    void add(const T& value, Comp comp) {
        if (heap_size == data.get_size()) {
            data.push_back(value);
        }
        else {
            data[heap_size] = value;
        }
        przekopcowanie_w_gore(heap_size, comp);
        heap_size++;
    }

    template<typename Comp>
    void clear_root(Comp comp) {
        if (heap_size == 0) return;
        heap_size--;
        if (heap_size > 0) {
            data[0] = data[heap_size];
            przekopcowanie_w_dol(0,comp);
        }
    }
    const T& get_root() {
        if (heap_size != 0) return data[0];
        throw std::out_of_range("nothing in root");
    }

    void dsiplay_heap() const {
        if (heap_size == 0) return;
        for (size_t i = 0; i < heap_size; i++) {
            std::cout<<data[i] << '\n';
        }
    }
    size_t get_size() const {
        return heap_size;
    }
};