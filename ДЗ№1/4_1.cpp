#include <iostream>
#include <cassert>
#include <sstream>

/*
 * Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
 * Требования:
 * время работы O(N * logK). Ограничение на размер кучи O(K)..
 * Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Куча должна быть динамической.

 */
template<class T>
class Heap {
public:
    Heap(bool (*cmp) (const T&, const T&) = [](const T& lhs, const T& rhs) { return lhs < rhs; }):
            arr(nullptr),
            size(0),
            capacity(0),
            comp(cmp) {};
    Heap(T* a, size_t s, bool (*cmp) (const T&, const T&) = [](const T& lhs, const T& rhs) { return lhs < rhs; }):
            arr(a),
            size(s),
            capacity(s),
            comp(cmp) { build_heap();};
    ~Heap() {
        delete[] arr;
    }
    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;
    Heap& operator=(const Heap&) = delete;
    Heap& operator=(Heap&&) = delete;

    const T& top() const {
        return arr[0];
    }

    void pop() {
        arr[0] = arr[--size];
        if (!empty()) {
            sift_down(0);
        }
    }

    void push(const T& elem) {
        if (fool()) {
            if (capacity == 0) {
                capacity = 1;
                arr = new T[1];
            }
            else {
                capacity *= 2;
                T* new_arr = new T[capacity];
                for (size_t i = 0; i < size; ++i) {
                    new_arr[i] = arr[i];
                }
                delete[] arr;
                arr = new_arr;
            }
        }
        arr[size] = elem;
        sift_up(size);
        ++size;
    }

    size_t get_size() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

private:
    T* arr;
    size_t size, capacity;
    bool (*comp) (const T&, const T&);
    bool fool() const {
        return (size == capacity);
    };

    void build_heap() {
        if (!empty()) {
            for (size_t i = (size - 1) / 2; i > 0; --i) {
                sift_down(i);
            }
            sift_down(0);
        }
    };

    void sift_up(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (comp(arr[parent], arr[idx])) {
                return;
            }
            T tmp = arr[idx];
            arr[idx] = arr[parent];
            arr[parent] = tmp;
            idx = parent;
        }
    };

    void sift_down(size_t idx) {
        while (true) {
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;
            size_t largest = idx;
            if (left < size && comp(arr[left], arr[idx])) {
                largest = left;
            }
            if (right < size && comp(arr[right], arr[largest])) {
                largest = right;
            }
            if (largest == idx) {
                return;
            }
            T tmp = arr[idx];
            arr[idx] = arr[largest];
            arr[largest] = tmp;
            idx = largest;
        }
    };
};

template<class T>
class ArrayStruct {
public:
    T val;
    size_t num_of_array, idx;
    ArrayStruct() : val(T()), num_of_array(0), idx(0) {};
    ArrayStruct(const T& v, size_t n) : val(v), num_of_array(n), idx(0) {};
};


template<class T>
void merge_k_arrays(T** arr, size_t* sizes, size_t k, T* arr_to_sort, size_t n) {
    auto first_vals = new ArrayStruct<T>[k];
    for (size_t i = 0; i < k; ++i) {
        first_vals[i].val = arr[i][0];
        first_vals[i].num_of_array = i;
    }

    Heap<ArrayStruct<T>> heap(first_vals, k, [](const ArrayStruct<T>& lhs, const ArrayStruct<T>& rhs) {return lhs.val < rhs.val; });

    for (size_t i = 0; i < n; ++i) {
        ArrayStruct<T> min = heap.top();
        arr_to_sort[i] = min.val;
        heap.pop();
        min.idx++;
        if (min.idx < sizes[min.num_of_array]) {
            min.val = arr[min.num_of_array][min.idx];
            heap.push(min);
        }
    }
}

void func(std::istream &in, std::ostream &out) {
    size_t k = 0, n = 0;
    in >> k;

    auto arrays = new ssize_t * [k];
    auto *sizes = new size_t[k];
    for (size_t i = 0; i < k; ++i) {
        in >> sizes[i];
        n += sizes[i];
        arrays[i] = new ssize_t [sizes[i]];

        for (size_t j = 0; j < sizes[i]; ++j) {
            in >> arrays[i][j];
        }
    }

    auto * sorted_array = new ssize_t [n];
    merge_k_arrays<ssize_t>(arrays, sizes, k, sorted_array, n);
    if (n > 0) {
        out << sorted_array[0];
    }
    for (size_t i = 1; i < n; ++i) {
        out << ' ' << sorted_array[i];
    }
    for (size_t i = 0; i < k; ++i) {
        delete[] arrays[i];
    }
    delete[] arrays;
    delete[] sizes;
    delete[] sorted_array;
}

void tests() {
    {
        std::stringstream in;
        in << "3\n"
              "1\n"
              "6\n"
              "2\n"
              "50 90\n"
              "3\n"
              "1 10 70\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "1 6 10 50 70 90");
    }
    {
        std::stringstream in;
        in << "3\n"
              "3\n"
              "6 7 100\n"
              "2\n"
              "50 90\n"
              "3\n"
              "1 10 70\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "1 6 7 10 50 70 90 100");
    }
    {
        std::stringstream in;
        in << "1\n"
              "3\n"
              "1 3 4\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "1 3 4");
    }
    {
        std::stringstream in;
        in << "0\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}

int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}



