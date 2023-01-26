#include <iostream>
#include <functional>

#include <sstream>
#include <cassert>
/*
 * В одной военной части решили построить в одну шеренгу по росту.
 * Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
 * Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.
 * За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
 * Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать,
 * перед каким солдатом в строе он должен становится.

Требования:
 * скорость выполнения команды - O(log n).

Формат входных данных
 * Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000).
 * В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно)
 * и
 * число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя.
 * Солдаты в строе нумеруются с нуля.

Формат выходных данных
 * На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).
*/

template <class T>
struct DefaultComparator {
    int operator () (const T& l, const T& r) const {
        if ( l < r ) return 2;
        if ( l > r ) return 0;
        else return 1;
    }
};

template<typename Key, typename Comparator = DefaultComparator<Key>>
class AVLTree {
private:
    struct Node {
        Key data;
        Node * left;
        Node * right;
        int height, index;
        Node(const Key & data): data(data),
                                left(nullptr),
                                right(nullptr),
                                height(1),
                                index(1) {}
        int balance_factor() const { return get_height(right) - get_height(left); }

        static int get_index(const Node * node) {
            if (node == nullptr) return 0;
            return node->index;
        }

        static int get_height(const Node * node) {
            if (node == nullptr) return 0;
            return node->height;
        }
    };
public:
    AVLTree(): root(nullptr) {}
    AVLTree(const Comparator & comp): root(nullptr), comp(comp) {}

    AVLTree( const AVLTree& ) = delete;
    AVLTree( AVLTree&& ) = delete;
    AVLTree& operator =( const AVLTree& ) = delete;
    AVLTree& operator =( AVLTree&& ) = delete;

    ~AVLTree() { delete root; }

    int insert(const Key & key) {
        int index = 0;
        root = _insert(key, root, index);
        return index;
    }

    void erase(const int & index) { root = _erase(index, root);}
private:
    Node * find_min(Node * node, Node * & node_to_swap) {
        if (node == nullptr) {
            node_to_swap = nullptr;
            return nullptr;
        }
        if (node->left == nullptr) {
            node_to_swap = node;
            return node->right;
        }
        node->left = find_min(node->left, node_to_swap);
        return balance(node);
    }

    Node* _insert(const Key & key, Node * node, int & index) {
        if (node == nullptr) return new Node(key);

        const int comp_res = comp(key, node->data);

        if (comp_res == 0)
            node->left = _insert(key, node->left, index);
        else {
            index += Node::get_index(node->left) + 1;
            node->right = _insert(key, node->right, index);
        }

        return balance(node);
    }

    Node* _erase(const int index, Node * node) {
        if (node == nullptr) return nullptr;

        const int left_index = Node::get_index(node->left);

        if (left_index < index)
            node->right = _erase(index - left_index - 1, node->right);
        else if (left_index > index)
            node->left = _erase(index, node->left);
        else {
            // left_index == index
            Node * left = node->left;
            Node * right = node->right;

            delete node;

            if (!right) return left;
            Node * min;
            right = find_min(right, min);
            min->right = right;
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }


    Node* balance(Node * node) {
        fix_height(node);
        fix_index(node);
        const int bf = node->balance_factor();

        if (bf == -2) {
            if (node->left->balance_factor() > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (bf == 2) {
            if (node->right->balance_factor() < 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }

    void fix_height(Node * node) {
        if (node == nullptr) return;
        node->height = std::max(Node::get_height(node->left), Node::get_height(node->right)) + 1;
    }

    void fix_index(Node * node) {
        if (node == nullptr) return;
        node->index = Node::get_index(node->left) + Node::get_index(node->right) + 1;
    }

    Node * rotate_left(Node * node) {
        Node * tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fix_height(node);
        fix_index(node);

        fix_height(tmp);
        fix_index(tmp);

        return tmp;
    }

    Node * rotate_right(Node * node) {
        Node * tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fix_height(node);
        fix_index(node);

        fix_height(tmp);
        fix_index(tmp);

        return tmp;
    }

private:
    Node * root = nullptr;
    Comparator comp;
};

int comp(const int & a, const int & b) {
    if (a < b) return 2;
    else if (a > b) return 0;
    return 1;
}


void func(std::istream & in, std::ostream & out) {
    int N;
    int key, command;
    in >> N;
    if (N <= 0) {
        return;
    }
    AVLTree<int, std::function<int(const int &, const int &)>> avl_tree(comp);
    for (int i = 0; i < N; ++i) {
        in >> command >> key;
        if (command == 1) {
            out << avl_tree.insert(key) << '\n';
        } else {
            avl_tree.erase(key);
        }
    }
}

void tests() {
    {
        std::stringstream in;
        in << "5\n"
              "1 100\n"
              "1 200\n"
              "1 50\n"
              "2 1\n"
              "1 150";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "0\n"
                            "0\n"
                            "2\n"
                            "1\n"
                            "");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
    tests();
//    func(std::cin, std::cout);
    return 0;
}