#include <iostream>
#include <cassert>
#include <sstream>

/*
 * 2_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
 * Требования:
 * Время работы поиска для каждого элемента B[i]: O(log(k)).
 */

// A = {1, 2, 3, 4, 5, 5, 6}
// B = {3, 4, 1}

size_t exp_search(const ssize_t * arr, size_t size, ssize_t key) {
    size_t result_index = 1;
    while(result_index < size && *(arr + result_index) < key)
        result_index *= 2;
    if (result_index > size) {
        result_index = size - 1;
    }
    return result_index;
}


size_t bin_search(const ssize_t *A, size_t left, size_t right, ssize_t b) {
//    ptrdiff_t min = abs(A[left] - b);
//    std::cout<<"RL: "<<right<<' '<<left<<'\n';
    while (left < right) {
        size_t center = (left + right + 1) / 2;
        if (center == 0) {

        }
        if (abs(A[center] - b) < abs(A[center - 1] - b) && abs(A[center] - b) < abs(A[center + 1] - b)) {
            return center;
        }
        else {
            if (abs(A[center] - b) >= abs(A[center - 1] - b)) {
                right = center - 1;
            }
            else {
                left = center;
            }
        }
    }
//    std::cout<<"RL: "<<right<<' '<<left / 2<<'\n';
    return (abs(A[left] - b) < abs(A[right] - b))? left: right;
}

void func(std::istream &in, std::ostream & out) {
    size_t n = 0;
    in >> n;

    if (n <= 0) {
        return;
    }

    auto *A = new ssize_t[n];
    for (size_t i = 0; i < n; ++i) {
        in >> A[i];
    }

    size_t m = 0;
    in >> m;
    if (m <= 0) {
        return;
    }
    for (size_t i = 0; i < m; ++i) {
        ssize_t b = 0;
        in >> b;

        if (i > 0) {
            out << ' ';
        }
        if (A[n - 1] < b) {
            out << n - 1;
        }
        else
        {
            size_t right = exp_search(A, n, b);
            size_t left = right / 2;
            if (right > n) {
                right = n;
            }
            out << bin_search(A, left, right, b);
        }
    }

    delete[] A;
}


void tests() {
    {
        std::stringstream in;
        in << "7\n"
              "1 2 3 4 5 5 6\n"
              "3\n"
              "3 4 1\n";
        std::stringstream out;
//        func(in, out);
        ssize_t A[] = {10, 20, 30, 40, 50, 60};
        out << bin_search(A, 0, 3, 15);
        std::cout<<out.str()<<'\n';
//        assert(out.str() == "2 3 0");
    }
    {
        std::stringstream in;
        in << "3\n"
              "10 20 30\n"
              "3\n"
              "9 15 35\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "0 0 2");
    }
    {
        std::stringstream in;
        in << "3\n"
              "10 20 30\n"
              "4\n"
              "8 9 10 32\n";
        std::stringstream out;
        func(in, out);
        assert(out.str() == "0 0 0 2");
    }
    {
        std::stringstream in;
        in << "3\n"
              "10 20 30\n"
              "4\n"
              "8 33 24 1\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "0 2 1 0");
    }
    {
        std::stringstream in;
        in << "4\n"
              "1 2 2 10\n"
              "6\n"
              "8 3 2 1 3 6\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "3 2 1 0 2 2");
    }
    {
        std::stringstream in;
        in << "10\n"
              "1 2 3 5 10 11 13 14 100 1000\n"
              "6\n"
              "1 5 100 1000 5 550\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "0 3 8 9 3 8");
    }
    {
        std::stringstream in;
        in << "9\n"
              "33 39 57 60 67 77 78 79 88\n"
              "2\n"
              "73 76";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "5 5");
    }
    {
        std::stringstream in;
        in << "9\n"
              "33 39 57 60 67 77 78 79 88\n"
              "100\n"
              "60 51 18 85 17 90 71 55 16 12 79 69 45 10 0 43 79 25 64 80 96 65 20 33 31 40 64 64 "
              "6 30 93 26 51 53 97 89 51 44 13 58 32 5 90 47 43 44 28 4 24 77 58 48 63 26 62 8 32 "
              "29 71 74 27 46 13 79 12 48 47 72 44 84 25 69 2 31 59 83 73 40 11 75 56 73 76 29 4 55 "
              "86 5 24 38 81 22 18 96 89 14 66 5 15 41";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        std::cout<<"3 2 0 8 0 8 4 2 0 0 7 4 1 0 0 1 7 0 4 7 8 4 0 0 0 1 4 4 0 0 8 0 2 2 8 8 2 1 0 2 0 0 8 1 1 1 0 0 0 5 2 1 3 0 3 0 0 0 4 5 0 1 0 7 0 1 1 4 1 8 0 4 0 0 3 7 5 1 0 5 2 5 5 0 0 2 8 0 0 1 7 0 0 8 8 0 4 0 0 1\n";
        assert(out.str() == "3 2 0 8 0 8 4 2 0 0 7 4 1 0 0 1 7 0 4 7 8 4 0 0 0 1 4 4 0 0 8 0 2 2 8 8 2 1 0 2 0 0 8 1 1 1 0 0 0 5 2 1 3 0 3 0 0 0 4 5 0 1 0 7 0 1 1 4 1 8 0 4 0 0 3 7 5 1 0 5 2 5 5 0 0 2 8 0 0 1 7 0 0 8 8 0 4 0 0 1");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}

/*
 * test:
 * 9
33 39 57 60 67 77 78 79 88
100
60 51 18 85 17 90 71 55 16 12 79 69 45 10 0 43 79 25 64 80 96 65 20 33 31 40 64 64
 6 30 93 26 51 53 97 89 51 44 13 58 32 5 90 47 43 44 28 4 24 77 58 48 63 26 62 8 32
 29 71 74 27 46 13 79 12 48 47 72 44 84 25 69 2 31 59 83 73 40 11 75 56 73 76 29 4 55
 86 5 24 38 81 22 18 96 89 14 66 5 15 41
 answer:
 * 3 2 0 8 0 8 4 2 0 0 7 4 1 0 0 1 7 0 4 7 8 4 0 0 0 1 4 4 0 0 8 0 2 2 8 8 2 1 0 2 0 0 8 1 1 1 0 0 0 5 2 1 3 0 3 0 0 0 4 5 0 1 0 7 0 1 1 4 1 8 0 4 0 0 3 7 5 1 0 5 2 5 5 0 0 2 8 0 0 1 7 0 0 8 8 0 4 0 0 1
 */

int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}
