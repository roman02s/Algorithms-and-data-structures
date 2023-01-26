#include <iostream>
#include <cassert>
#include <sstream>
#include <ctime>
#include <cstdlib>

/*
 * Дано множество целых чисел из [0..10^9] размера n.
 * Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
 * 10%  перцентиль
 * медиана
 * 90%  перцентиль
Требования: к дополнительной памяти: O(n).
 * Среднее время работы: O(n)
 * Должна быть отдельно выделенная функция partition.
 * Рекурсия запрещена.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 * Описание для случая прохода от начала массива к концу:
        Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
        Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
        Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
        Последним элементом лежит опорный.
        Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
        Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
        Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
        Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
        В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

template<typename T>
struct default_comporator {
    bool operator()(const T& left, const T& right) const {return (left > right);};
};

template<typename T, typename Comporator = default_comporator<T>>
size_t partition(T *arr, size_t begin, size_t end, Comporator cmp) {
    if (begin != end) {
        const size_t index = begin + rand() % (end - begin);
        T temp = arr[index];
        arr[index] = arr[begin];
        arr[begin] = temp;
    }
    const T elem = arr[begin];
    size_t i = end, j = i;

    while (true) {
        if (cmp(arr[i], elem) && i > begin && i == j) {
            i--;
            j--;
        }
        else {
            if (j > begin) {
                if (cmp(arr[j], elem)) {
                    T tmp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = tmp;
                    --i;
                }
                j--;
            }
        }
        if (j == begin) {
            T tmp = arr[i];
            arr[i] = arr[begin];
            arr[begin] = tmp;
            return i;
        }
    }
}

template<typename T, typename Comporator = default_comporator<T>>
size_t find_k_statistic(T *arr, size_t len, Comporator cmp, size_t index) {
    srand(time(NULL));
    size_t pos = 0, begin = 0, end = len - 1;
    while (pos != index) {
        pos = partition(arr, begin, end, cmp);
        if (pos < index) {
            begin = pos + 1;
        }
        else {
            if (pos > index) {
                end = pos - 1;
            }
        }
    }
    return arr[index];
}


void func(std::istream &in, std::ostream & out) {
    size_t n;
    in >> n;
    if (n <= 0) {
        return;
    }
    auto *arr = new ssize_t [n];
    for (size_t i = 0; i < n; ++i) {
        in >> arr[i];
    }
    default_comporator<ssize_t> cmp;
    out << find_k_statistic(arr, n, cmp, 0.1 * n) << '\n'; // 10% percentile
    out << find_k_statistic(arr, n, cmp, 0.5 * n) << '\n'; // Median
    out << find_k_statistic(arr, n, cmp, 0.9 * n) << '\n'; // 90% percentile
    delete[] arr;
}

void tests() {
    {
        std::stringstream in;
        in << "10\n"
              "1 2 3 4 5 6 7 8 9 10\n";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "2\n"
                            "6\n"
                            "10\n");
    }
    {
        std::stringstream in;
        in << "0\n";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "");
    }
    {
        std::stringstream in;
        in << "1\n"
              "1\n";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "1\n"
                            "1\n"
                            "1\n");
    }
    {
        std::stringstream in;
        in << "11\n"
              "1 2 3 4 5 6 7 8 9 10 11\n";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "2\n"
                            "6\n"
                            "10\n");
    }
    {
        std::stringstream in;
        size_t n = 100;
        in << n <<"\n";
        for (size_t i = 1;i <= n;++i) {
            in << n - i<<' ';
        }
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "10\n"
                            "50\n"
                            "90\n");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}
