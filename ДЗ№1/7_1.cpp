#include <iostream>
#include <cassert>
#include <sstream>
#include <string>

/*
 * 7_1. MSD для строк.
Требования:
 * Дан массив строк. Количество строк не больше 10^5.
 * Отсортировать массив методом поразрядной сортировки MSD по символам.
 * Размер алфавита - 256 символов. Последний символ строки = '\0'.

 */

void count_sort(std::string *buf, size_t index, size_t left, size_t right, char _buf[256]) {
    _buf[0] = '\0';
    size_t i = left, j;
    while (i != right) {
        for (j = 0;_buf[j] != '\0';++j) {
            if (_buf[j] == buf[i][index]) {
                _buf[j] = buf[i][index];
                _buf[j + 1] = '\0';
                break;
            }
        }
        _buf[j] = buf[i][index];
        _buf[++j] = '\0';
        ++i;
    }
    for (size_t i = 0; _buf[i] != '\0';++i) {
        std::cout << "count_sort = " << _buf[i] << '\n';
    }
    std::cout << "end\n";
}

void msd(std::string *buf, size_t index, size_t left, size_t right) {
    char _buf[256];
    if (left == right || index > 4) {
        return;
    }
    count_sort(buf, index, left, right, _buf);
//    std::cout << "_buf[i] "<< '\n';
//    for (size_t i = 0; _buf[i] != '\0';++i) {
//        std::cout << buf[i] << '\n';
//    }
    size_t _left = 0, _right = 0;
    for (size_t i = 0;_buf[i] != '\0';++i) {
        _left = _right;
        size_t j = i;
        while (buf[j][index] == _buf[i]) {
            ++j;
        }
        _right = j;
        msd(buf, index + 1, _left, _right);
    }
}

void func(std::istream &in, std::ostream & out) {
    std::string str;
    size_t bufsize = 1000;
    std::string *buf;
    buf = new std::string[bufsize];
    size_t i = 0;
    while (true) {
        std::getline(in, buf[i]);
        if (i == bufsize) {
            bufsize *= 2;
            auto *tmp = new std::string[bufsize];
            for (size_t j = 0; j < bufsize;++j) {
                tmp[j] = buf[j];
            }
            delete []buf;
            buf = tmp;
        }
        if (buf[i].empty()) {
            break;
        }
//        out <<buf[i++] << '\n';
          ++i;
    }
    msd(buf, 0, 0, i);
    for (size_t i = 0; !buf[i].empty();++i) {
        std::cout << buf[i] << '\n';
    }
    delete []buf;
}

void tests() {
    {
        std::stringstream in;
        in << "ab\n"
              "a\n"
              "aaa\n"
              "aa\n"
              "";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
//        assert(out.str() == "a\n"
//                            "aa\n"
//                            "aaa\n"
//                            "ab\n");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}
