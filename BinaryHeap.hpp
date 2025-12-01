#pragma once


template<typename T>
class BinaryHeap
{
    dynamicarray<T> data;
    size_t size{0};

    template<typename Comp> // ldaczego tu jest jakis template comp i co to robi
    void sift_up(size_t index, Comp comp) // co to jest sift up i down
    {
        if (index == 0) return;
        size_t parent = (index - 1) / 2;
        if (comp(data[parent], data[index]))
        {
            std::swap(data[parent], data[index]);
            sift_up(parent,comp);
        }
    }
    template<typename Comp>
    void sift_down(size_t index, Comp comp)
    {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t best = index;

        if (left < size && comp(data[best], data[left]))
        {
            best = left;
        }
        if (right < size && comp(data[best], data[right]))
        {
            best = right;
        }
        if (best != index)
        {
            std::swap(data[index], data[best]);
            sift_down(best, comp);
        }
    } // co to jest
public:
    BinaryHeap() = default;

    template<typename Comp>
    void push(const T& value, Comp comp)
    {
        if (size == data.get_size())
        {
            data.push_back(value);
        }
        else
        {
            data[size] = value;
        }
        sift_up(size, comp);
        size++;
    }
    void push(const T& value)
    {
        push(value, std::less<T>{}); // co to robi co to anczy jak to dziala
    }

    template<typename Comp>
    bool pop_max(T& out, Comp comp)
    {
        if (size == 0) return false;

        out = data[0];
        size--;

        if (size > 0)
        {
            data[0] = data[size];
            sift_down(0,comp);
        }
        return true;
    }
    bool pop_max(T& out)  //dlaczego nie const T& out albo value czy cos
    {
        return pop_max(out, std::less<T>{});
    }
    const T& top() const
    {
        if (size == 0)
        {
            throw std::out_of_range("Heap is empty");
        }
        return data[0];
    }

};