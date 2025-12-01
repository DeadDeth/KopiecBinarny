#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iostream>

template <typename T>
class dynamicarray
{
    T* array{nullptr};
    size_t size{0};
    size_t capacity{0};
    static constexpr short int expand_rate{2};

    void expand()
    {
        if (capacity == 0) capacity = 1;
        else capacity = capacity * expand_rate;

        T* array_copy = new T[capacity];
        for (size_t i = 0; i < size; i++)
        {
            array_copy[i] = std::move(array[i]);
        }
        std::swap(array, array_copy);
        delete[] array_copy;
    }

    void add(const T& value)
    {
        if (size==capacity) expand();
        array[size] = value;
        size++;
    }

    T& find_value_by_value(const T& value)
    {
        for (size_t index = 0; index < size; index++)
        {
            if (array[index] == value) return array[index];
        }
        throw std::out_of_range("No such value.");
    }
    T& find_value_by_index(size_t index)
    {
        if (index<size)
        {
            return array[index];
        }
        else throw std::out_of_range("Invalid index");
    }



    void clear() noexcept
    {
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }
public:
    explicit dynamicarray() = default;
    ~dynamicarray() noexcept{ clear(); }

    void push_back(const T& value)
    {
        add(value);
    }

    T& value_find(const T& value)
    {
        return find_value_by_value(value);
    }
    T& operator[](size_t index)
    {
        return find_value_by_index(index);
    }

    size_t get_size() const
    {
        return size;
    }
    void info () const
    {
        std::cout<<"Size: " << size << " " << "Capacity: " << capacity <<'\n';
    }
};