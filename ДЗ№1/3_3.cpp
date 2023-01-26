#include <iostream>
#include <cassert>
#include <sstream>

/*
 * Реализовать очередь с помощью двух стеков.
 * Требования:
 * Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
 */


class Node
{
public:
    Node() {
        size = BUFSIZ;
        data = new ssize_t [BUFSIZ];
        top = 0;
    };
    ~Node() {
        delete []data;
    };
    void push(ssize_t value) {
        if (top >= size) {
            resize();
        }
        data[top] = value;
        ++top;
    };
    ssize_t pop() {
        if (top == 0) {
            return -1;
        }
        --top;
        return data[top];
    }
private:
    void resize() {
        auto * tmp = new ssize_t [size * 2];
        for (size_t i = 0;i < size;++i)
            tmp[i] = data[i];
        size *= 2;
        delete []data;
        data = tmp;
    }
    ssize_t *data;
    size_t size;
    size_t top;
};

class Queue {
private:
    Node *head;
    Node *tail;
public:
    Queue() {
        head = new Node;
        tail = new Node;
    };
    ~Queue() {
        delete tail;
        delete head;
    }
    Queue(const Queue &other) = delete;
    Queue& operator=(const Queue &other) = delete;
    void push(ssize_t data)
    {
        tail->push(data);
    }

    ssize_t pop()
    {
        ssize_t tmp;
        if ((tmp = head->pop()) == -1) {
            while((tmp = tail->pop()) != -1) {
                head->push(tmp);
            }
        }
        return (tmp == -1)? head->pop():tmp;
    }
};

void func(std::istream &in, std::ostream &out) {
    Queue *queue = new Queue();
    size_t count;
    char action;
    ssize_t data;
    in >> count;
    if (count > 1000000) {
        return;
    }
    for (size_t i = 0;i < count;++i) {
        in >> action >> data;
        if (action == '3') {
            (*queue).push(data);
        }
        else {
            ssize_t tmp = (*queue).pop();
            if (tmp != data) {
                out << "NO";
                delete queue;
                return;
            }
        }
    }
    out << "YES";
    delete queue;
}

void tests() {
    {
        std::stringstream in;
        in << "3\n"
              "3 44\n"
              "3 50\n"
              "2 44\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "YES");
    }
    {
        std::stringstream in;
        in << "2\n"
              "2 -1\n"
              "3 10\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "YES");
    }
    {
        std::stringstream in;
        in << "2\n"
              "3 44\n"
              "2 66\n";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "NO");
    }
    {
        std::stringstream in;
        in << "3\n"
              "3 11\n"
              "2 66\n"
              "3 1221";
        std::stringstream out;
        func(in, out);
        std::cout<<out.str()<<'\n';
        assert(out.str() == "NO");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}

int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}



