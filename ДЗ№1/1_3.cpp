#include <iostream>
#include <cassert>
#include <sstream>

/*
 * 1.3 Если в числе содержится только один бит со значением 1, записать в выходной поток OK. Иначе записать FAIL.
 * Требования:
 *  Необходимо использование битовых операций.
 *  Использование арифметических операций запрещено.
 *  Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном виде.
 */

ssize_t func(std::istream &in, std::ostream & out) {
    size_t x;
    in >> x;
    size_t result = 0;
    while(x > 0) {

        if (x == 1 && result == 0) {
            out << "OK";
            return 0;
        }
        result = x & 1 | result;
        x >>= 1;
    }
    out << "FAIL";
    return -1;
}

void tests() {
    {
        std::stringstream in;
        in << 0;
        std::stringstream out;
        func(in, out);
        assert(out.str() == "FAIL");
    }

    {
        std::stringstream in;
        in << 1;
        std::stringstream out;
        func(in, out);
        assert(out.str() == "OK");
    }

    {
        size_t num = 1;
        for (size_t i = 0; i < 32; ++i)
        {
            std::stringstream in;
            in << num;
            std::stringstream out;
            func(in, out);

            assert(out.str() == "OK");
            num <<= 1;
        }
    }

    {
        size_t num = 2;
        for (size_t i = 0; i < 32; ++i)
        {
            std::stringstream in;
            in << num + 1;
            std::stringstream out;
            func(in, out);

            assert(out.str() == "FAIL");
            num <<= 1;
        }
    }
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}
