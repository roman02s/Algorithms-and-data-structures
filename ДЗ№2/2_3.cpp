#include <iostream>
#include <queue>
#include <unordered_set>

#include <sstream>
#include <cassert>
/*
 * Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 * то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Задание:
 2_3. Выведите элементы в порядке post-order (снизу вверх).
Требования:
 Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
*/
template <class T>
struct DefaultComparator {
    int operator () (const T& l, const T& r) const {
        return l <= r;
    }
};

template<class Value, class Comparator = DefaultComparator<Value>>
class Tree {
public:
    Tree() {}
    ~Tree() {
        if (root == nullptr) {
            return;
        }
        std::queue<Node *> queue;

        queue.push(root);
        while (!queue.empty()) {
            Node *cur = queue.front();
            queue.pop();

            if (cur->left != nullptr) {
                queue.push(cur->left);
            }
            if (cur->right != nullptr) {
                queue.push(cur->right);
            }
            delete cur;
        }
    }

    void insert(Value value) {
        if (root == nullptr) {
            root = new Node;
            root->value = value;
            return;
        }

        Node* cur = root;
        while (true) {
            if (cmp(cur->value, value)) {
                if (cur->right == nullptr) {
                    Node* tmp = new Node;
                    tmp->value = value;
                    cur->right = tmp;
                    break;
                } else {
                    cur = cur->right;
                }
            } else {
                if (cur->left == nullptr) {
                    Node* tmp = new Node;
                    tmp->value = value;
                    cur->left = tmp;
                    break;
                } else {
                    cur = cur->left;
                    continue;
                }
            }
        }
    }
    friend void print(Tree<Value, Comparator> & tree, std::ostream & out) {
        auto cur = tree.root;
        std::unordered_set<Tree::Node*> visited;
        while (cur != nullptr && visited.find(cur) == visited.end()) {
            if (cur->left != nullptr && visited.find(cur->left) == visited.end()) {
                cur = cur->left;
            } else if (cur->right != nullptr && visited.find(cur->right) == visited.end()) {
                cur = cur->right;
            } else {
                out << cur->value << " ";
                visited.insert(cur);
                cur = tree.root;
            }
        }
        out << std::endl;
    }
private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Value value;
    };
    Node* root = nullptr;
    Comparator cmp;
};

void func(std::istream & in, std::ostream & out) {
    size_t count;
    in >> count;
    Tree<int, DefaultComparator<int>> tree;
    int value;

    for (size_t i = 0; i < count; ++i) {
        in >> value;
        tree.insert(value);
    }
    print(tree, out);
}

void tests() {
    {
        std::stringstream in;
        in << "10\n"
              "7\n"
              "2\n"
              "10\n"
              "8\n"
              "5\n"
              "3\n"
              "6\n"
              "4\n"
              "1\n"
              "9";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "1 4 3 6 5 2 9 8 10 7 \n");
    }
    {
        std::stringstream in;
        in << "10\n"
              "7\n"
              "10\n"
              "2\n"
              "6\n"
              "1\n"
              "9\n"
              "4\n"
              "5\n"
              "8\n"
              "3\n"
              "";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "1 3 5 4 6 2 8 9 10 7 \n");
    }
    {
        std::stringstream in;
        in << "10\n"
              "4\n"
              "3\n"
              "9\n"
              "5\n"
              "6\n"
              "8\n"
              "7\n"
              "2\n"
              "10\n"
              "1\n"
              "";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "1 2 3 7 8 6 5 10 9 4 \n");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}