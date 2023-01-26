#include <iostream>
#include <sstream>
#include <cassert>
/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
Задание:
 1_1. Для разрешения коллизий используйте квадратичное пробирование.
 i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
Требования:
 * В таблице запрещено хранение указателей на описатель элемента.
Формат входных данных
 Каждая строка входных данных задает одну операцию над множеством.
 Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
 Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
 При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
 При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
 Формат выходных данных
 Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.

*/

size_t str_hash(const std::string& data) {
    size_t hash = 0;
    for (size_t i = 0; i < data.length(); ++i) {
        hash = (hash + 127 * data[i]) % INT64_MAX;
    }
    return hash;
}

template<class T> struct Hasher {
    size_t operator ()(const T& data) {
        return data;
    }

};

template<> struct Hasher<int> {
    size_t operator ()(const int& data) {
        return data;
    }
};

template<> struct Hasher<std::string> {
    size_t operator ()(const std::string& data) {
        return str_hash(data);
    }
};


template <class Key, class Value, class Hash = Hasher<Key>>
class HashTable {
    static constexpr size_t LIMIT = 7;

    struct Node {
        Key key;
        Value value;

        Node* next;

        Node(const Key& a_key, const Value& a_value, Node* a_next): key(a_key), value(a_value), next(a_next) {
        }
    };
public:
    explicit HashTable(Hash hash = Hash()) : buckets(nullptr), items_count(0), buckets_count(0), hash(hash) {
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    ~HashTable() {
        for (int i = 0; i < buckets_count; i++) {
            Node* cur = buckets[i];
            while (cur) {
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] buckets;
    }

    bool insert(const Key& key, const Value& value) {
        if (find(key)) {
            return false;
        }

        if (!buckets || items_count > buckets_count * LIMIT) {
            grow();
        }

        size_t bucket_idx = hash(key) % buckets_count;
        buckets[bucket_idx] = new Node(key, value, buckets[bucket_idx]);
        items_count++;
        return true;

    }

    Value* find(const Key& key) {
        if (!buckets) {
            return nullptr;
        }

        size_t bucket_idx = hash(key) % buckets_count;
        Node* cur = buckets[bucket_idx];
        while (cur) {
            if (cur->key == key) {
                return &cur->value;
            }
            cur = cur->next;
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        if (!buckets) {
            return false;
        }
        size_t bucket_idx = hash(key) % buckets_count;
        Node* cur = buckets[bucket_idx];
        Node** prev = &buckets[bucket_idx];
        while (cur) {
            if (cur->key == key) {
                *prev = cur->next;
                items_count--;
                delete cur;
                return true;
            }
            prev = &(cur->next);
            cur = cur->next;
        }
        return false;
    }

private:
    void grow() {
        size_t new_buckets_count = std::max((size_t)7, buckets_count * 2);

        Node** new_buckets = new Node*[new_buckets_count];
        for (int i = 0; i < new_buckets_count; i++) {
            new_buckets[i] = nullptr;
        }

        for (int i = 0; i < buckets_count; i++) {
            Node* cur = buckets[i];
            while (cur) {
                size_t bucket_idx = hash(cur->key) % new_buckets_count;
                Node* tmp = cur;
                cur = cur->next;
                tmp->next = new_buckets[bucket_idx];
                new_buckets[bucket_idx] = tmp;

            }
        }

        delete[] buckets;
        buckets = new_buckets;
        buckets_count = new_buckets_count;
    }

    Node** buckets;
    size_t items_count;
    size_t buckets_count;

    Hash hash;

};

void func(std::istream & in, std::ostream & out) {
    HashTable<std::string, int> htable;
    std::string key;
    char operation = '\0';
    while (in >> operation >> key) {
        bool res = false;
        switch (operation) {
            case '+':
                res = htable.insert(key, 0);
                break;
            case '-':
                res = htable.erase(key);
                break;
            case '?':
                res = (htable.find(key) != nullptr);
                break;
            default:
                return;
        };
        if (res) {
            out << "OK" << std::endl;
        } else {
            out << "FAIL" << std::endl;
        }
    }
}

void tests() {
    {
        std::stringstream in;
        in << "+ hello\n"
              "+ bye\n"
              "? bye\n"
              "+ bye\n"
              "- bye\n"
              "? bye\n"
              "? hello";
        std::stringstream out;
        func(in, out);
        std::cout << out.str() << '\n';
        assert(out.str() == "OK\n"
                            "OK\n"
                            "OK\n"
                            "FAIL\n"
                            "OK\n"
                            "FAIL\n"
                            "OK\n");
    }
    std::cout<<"ALL TESTS PASSED!!!\n";
}
int main() {
//    tests();
    func(std::cin, std::cout);
    return 0;
}