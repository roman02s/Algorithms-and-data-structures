#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdlib>

/*
 * Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Общее время работы алгоритма O(n log n).
5_1. Реклама.
 * В супермаркете решили оптимизировать показ рекламы.
 * Известно расписание прихода и ухода покупателей (два целых числа).
 * Каждому покупателю необходимо показать минимум 2 рекламы.
 * Рекламу можно транслировать только в целочисленные моменты времени.
 * Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
 * В каждый момент времени может показываться только одна реклама.
 * Считается, что реклама показывается мгновенно.
 * Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
 * Требуется определить минимальное число показов рекламы.
 */


template<typename T>
struct default_comporator {
    bool operator()(T& left, T& right) const {return left < right;};
};

template <typename T, typename Comparator = default_comporator<T>>
void merge(T * const arr, size_t left, size_t right, size_t mid, Comparator cmp) {
    size_t _left = mid - left;
    size_t _right = right - mid;

    T *L = new T[_left];
    T *R = new T[_right];

    for (size_t i = 0; i < _left; ++i) {
        L[i] = arr[i + left];
    }

    for (size_t i = 0; i < _right; ++i) {
        R[i] = arr[i + mid];
    }

    size_t index_l = 0, index_r = 0, index_arr = left;
    while (index_l < _left and index_r < _right) {
        if (cmp(L[index_l], R[index_r])) {
            arr[index_arr++] = L[index_l++];
        }
        else {
            arr[index_arr++] = R[index_r++];
        }
    }

    while (index_l < _left) {
        arr[index_arr++] = L[index_l];
    }
    while (index_r < _right) {
        arr[index_arr++] = R[index_r++];
    }
    delete []L;
    delete []R;
}

template <typename T, typename Comparator = default_comporator<T>>
void merge_sort(T* array, size_t left, size_t right, Comparator cmp = Comparator()) {
    if (left >= right) {
        return;
    }
    size_t mid = (right + left) / 2;
    merge_sort(array, left, mid, cmp);
    merge_sort(array, mid + 1, right, cmp);
    merge(array, left, right, mid, cmp);
}


class AD {
private:
    size_t come;
    size_t leave;
public:
    AD(size_t _come = 0, size_t _leave = 0) : come(_come), leave(_leave) {}
    friend size_t total_count(AD * arr, size_t n) {
        size_t n_ad = 2;
        for (size_t i = 1; i < n; ++i) {
            if (arr[i] == arr[i - 1]) {
                continue;
            }
            else if (arr[i].come == arr[i - 1].leave) {
                ++n_ad;
                continue;
            }
            else if (arr[i].come > arr[i - 1].leave) {
                n_ad += 2;
            }
            else {
                ++n_ad;
            }
        }
        return n_ad;
    }
    friend std::istream & operator>>(std::istream & in, AD & a) {
        in >> a.come >> a.leave;
        return in;
    }
    friend std::ostream & operator<<(std::ostream & out, AD & a) {
        out << a.come <<' ' << a.leave << '\n';
        return out;
    }
    bool operator==(AD & other) const {
        if (come != other.come) {
            return false;
        }
        else if (leave != other.leave) {
            return false;
        }
        else {
            return true;
        }
    }
    bool operator<(AD & right) const {
        if (this->leave < right.leave) {
            return true;
        }
        else if (this->come > right.come) {
            return false;
        }
        else {
            return true;
        }
    }
    bool operator>(AD & right) const {
        if (this->leave > right.leave) {
            return true;
        }
        else if (this->come < right.come) {
            return false;
        }
        else {
            return true;
        }
    }
};
void func(std::istream & in, std::ostream & out) {
    size_t n = 0;
    in >> n;

    if (n < 0) {
        return;
    }
    auto * arr = new AD[n];
    for (size_t i = 0; i < n; ++i) {
        in >> arr[i];
//        out << arr[i];
    }
    merge_sort(arr, 0, n);
    out << total_count(arr, n);
    delete [] arr;
}

void tests() {
    {
        std::stringstream in;
        in << "5\n"
              "1 10\n"
              "10 12\n"
              "1 10\n"
              "1 10\n"
              "23 24\n";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "5");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}