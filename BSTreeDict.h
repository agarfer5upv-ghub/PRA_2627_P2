#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <string>
#include <ostream>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() : tree(new BSTree<TableEntry<V>>()) {}

    ~BSTreeDict() override {
        delete tree;
    }

    void insert(std::string key, V value) override {
        tree->insert(TableEntry<V>(key, value));
    }

    V search(std::string key) override {
        return tree->search(TableEntry<V>(key)).value;
    }

    V operator[](std::string key) {
        return search(key);
    }

    V remove(std::string key) override {
        TableEntry<V> entry = tree->search(TableEntry<V>(key));
        tree->remove(entry);
        return entry.value;
    }

    int entries() override {
        return tree->size();
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& dict) {
        out << *dict.tree;
        return out;
    }
};

#endif
