#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    std::string key;
    V value;

    TableEntry() : key(""), value{} {}
    TableEntry(std::string key) : key(key), value{} {}
    TableEntry(std::string key, V value) : key(key), value(value) {}

    friend bool operator==(const TableEntry<V>& a, const TableEntry<V>& b) {
        return a.key == b.key;
    }

    friend bool operator!=(const TableEntry<V>& a, const TableEntry<V>& b) {
        return !(a == b);
    }

    friend bool operator<(const TableEntry<V>& a, const TableEntry<V>& b) {
        return a.key < b.key;
    }

    friend bool operator>(const TableEntry<V>& a, const TableEntry<V>& b) {
        return a.key > b.key;
    }

    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& e) {
        out << "('" << e.key << "' => " << e.value << ")";
        return out;
    }
};

#endif
