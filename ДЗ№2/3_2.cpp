#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cassert>
/*
 * Постройте B-дерево минимального порядка t и выведите его по слоям.
 * В качестве ключа используются числа, лежащие в диапазоне 0..232 -1
Требования:
 * B-дерево должно быть реализовано в виде шаблонного класса.
 * Решение должно поддерживать передачу функции сравнения снаружи.

Формат входных данных
 * Сначала вводится минимальный порядок дерева t.
 * Затем вводятся элементы дерева.

Формат выходных данных
 * Программа должна вывести B-дерево по слоям.
 * Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.
*/

template <class T>
struct DefaultComparator {
    int operator () (const T& l, const T& r) const {
        if ( l < r ) return 2;
        if ( l > r ) return 0;
        else return 1;
    }
};
template <class Key, class Comparator = DefaultComparator<Key> >
class BTree {
public:
    struct Node {
        Node(bool leaf)
                : leaf(leaf) {}
        ~Node() {
            for (Node* child: children) {
                delete child;
            }
        }

        bool leaf;
        std::vector<Key> keys;
        std::vector<Node*> children;
    };

    BTree(size_t min_degree)
            : root(nullptr), t(min_degree) { assert(min_degree >= 2); }

    ~BTree(){ if (root) delete root; }

    void insert(const Key &key) {
        if (!root)
            root = new Node(true);

        if (is_node_full(root)) {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            split(root, 0);
        }

        insert_non_full(root, key);
    }

    bool find(const Key &key) { return find_aux(root, key); }

    void print(std::ostream & out) {
        if (root == nullptr) {
            return;
        }
        std::queue<Node *> q1;
        q1.push(root);
        while (!q1.empty()) {
            std::queue<Node *> q2;
            while (!q1.empty()) {
                Node *node = q1.front();
                q1.pop();
                for (int i = 0; i < node->keys.size(); ++i) {
                    out << node->keys[i] << ' ';
                }

                for (Node *child : node->children)
                    if (child != nullptr) {
                        q2.push(child);
                    }
            }

            while (!q2.empty()) {
                q1.push(q2.front());
                q2.pop();
            }
            out << '\n';
        }
    }
private:
    bool is_node_full(Node *node) { return node->keys.size() == 2*t - 1; }

    bool find_aux(Node* node, const Key &key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
            i++;

        if (i < node->keys.size() && key == node->keys[i])
            return true;
        else if (node->leaf)
            return false;
        else
            return find_aux(node->children[i], key);
    }

    void split(Node *node, int index) {
        Node *Y = node->children[index];
        Node *Z = new Node(Y->leaf);

        Z->keys.resize(t - 1);
        for (int j = 0; j < t - 1; ++j) {
            Z->keys[j] = Y->keys[j + t];
        }

        Z->children.resize(t);
        if (!Y->leaf) {
            for (int j = 0; j < t; ++j) {
                Z->children[j] = Y->children[j + t];
            }
        }

        Key &median_key = Y->keys[t - 1];
        Y->keys.resize(t - 1);
        Y->children.resize(t);
        node->children.resize(node->children.size() + 1);
        for (int j = node->children.size() - 2; j > index; --j) {
            node->children[j + 1] = node->children[j];
        }
        node->children[index + 1] = Z;

        node->keys.resize(node->keys.size() + 1);
        for (int j = node->keys.size() - 2; j >= index; --j) {
            node->keys[j + 1] = node->keys[j];
        }
        node->keys[index] = median_key;
    }


    void insert_non_full(Node *node, const Key &key) {
        int pos = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos]) {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && key < node->keys[pos]) {
                pos--;
            }
            if (is_node_full(node->children[pos + 1])) {
                split(node, pos + 1);
                if (key > node->keys[pos + 1]) {
                    pos++;
                }
            }
            insert_non_full(node->children[pos + 1], key);
        }
    }
private:
    Node *root;
    size_t t; // minimum degree
};

void func(std::istream & in, std::ostream & out) {
    size_t t = 0;
    in >> t;
    BTree<int> B_tree(t);
    int num;

    while (in >> num) {
        B_tree.insert(num);
    }
    B_tree.print(out);
}

void tests() {
    {
        std::stringstream in;
        in << "2\n"
              "0 1 2 3 4 5 6 7 8 9";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "3 \n"
                            "1 5 7 \n"
                            "0 2 4 6 8 9 \n");
    }
    {
        std::stringstream in;
        in << "4\n"
              "0 1 2 3 4 5 6 7 8 9";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "3 \n"
                            "0 1 2 4 5 6 7 8 9 \n");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}