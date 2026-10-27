#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <stdexcept>
#include <ostream>
#include "Dict.h"
#include "TableEntry.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    std::list<TableEntry<V>>* table;

    int h(const std::string& key) const {
        int sum = 0;
        for (char c : key)
            sum += static_cast<unsigned char>(c);
        return sum % max;
    }

public:
    explicit HashTable(int size) : n(0), max(size), table(nullptr) {
        if (size <= 0)
            throw std::runtime_error("Invalid table size!");
        table = new std::list<TableEntry<V>>[max];
    }

    ~HashTable() override {
        delete[] table;
    }

    int capacity() const {
        return max;
    }

    int entries() override {
        return n;
    }

    void insert(std::string key, V value) override {
        int i = h(key);
        for (const auto& entry : table[i])
            if (entry.key == key)
                throw std::runtime_error("Duplicated element!");
        table[i].push_front(TableEntry<V>(key, value));
        ++n;
    }

    V search(std::string key) override {
        int i = h(key);
        for (const auto& entry : table[i])
            if (entry.key == key)
                return entry.value;
        throw std::runtime_error("Element not found!");
    }

    V operator[](std::string key) {
        return search(key);
    }

    V remove(std::string key) override {
        int i = h(key);
        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if (it->key == key) {
                V value = it->value;
                table[i].erase(it);
                --n;
                return value;
            }
        }
        throw std::runtime_error("Element not found!");
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        out << "Entries: " << ht.n << "\nCapacity: " << ht.max << "\n";
        for (int i = 0; i < ht.max; ++i) {
            out << i << ": ";
            for (const auto& entry : ht.table[i])
                out << entry << " ";
            out << "\n";
        }
        return out;
    }
};

#endif
