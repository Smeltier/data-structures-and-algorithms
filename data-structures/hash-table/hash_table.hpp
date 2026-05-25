#pragma once

#include <vector>
#include <iostream>
#include <functional>

template <typename key_type, typename value_type>
class HashTable {
private:
    struct Slot {
        key_type key;
        value_type value;
        enum class State { EMPTY, OCCUPIED, TOMBSTONE } state = State::EMPTY;
    };

    std::vector<Slot> table;
    size_t current_size;

    int hash(const key_type key) const {
        return std::hash<key_type>{}(key) % table.size();
    }

public:
    HashTable() : table(0), current_size(0) {}

    HashTable(const size_t size) : table(size), current_size(0) {}

    void insert(const key_type key, const value_type value) {
        if (full()) {
            return;
        }

        int index = hash(key);
        int tombstone_index = -1;

        for (size_t i = 0; i < table.size(); ++i) {
            if (table[index].state == Slot::State::OCCUPIED and table[index].key == key) {
                table[index].value = value;
                return;
            }
            else if (table[index].state == Slot::State::TOMBSTONE) {
                tombstone_index = (tombstone_index == -1) ? index : tombstone_index;
            }
            else {
                int target = (tombstone_index != -1) ? tombstone_index : index;
                table[target] = { key, value, Slot::State::OCCUPIED };
                current_size++;
                return;
            }

            index = (index + 1) % (int)table.size();
        }

        if (tombstone_index != -1) {
            table[tombstone_index] = { key, value, Slot::State::OCCUPIED };
            current_size++;
        }
    }

    void remove(const key_type key) {
        if (empty()) {
            return;
        }

        int index = hash(key);

        for (size_t i = 0; i < table.size(); ++i) {
            if (table[index].state == Slot::State::EMPTY) {
                return;
            }

            if (table[index].state == Slot::State::OCCUPIED and table[index].key == key) {
                table[index].state = Slot::State::TOMBSTONE;
                current_size--;
                return;
            }

            index = (index + 1) % (int)table.size();
        }
    }

    bool search(const key_type key) const {
        if (empty()) {
            return false;
        }

        int index = hash(key);

        for (size_t i = 0; i < table.size(); ++i) {
            if (table[index].state == Slot::State::EMPTY) {
                return false;
            }

            if (table[index].state == Slot::State::OCCUPIED and table[index].key == key) {
                return true;
            }

            index = (index + 1) % (int)table.size();
        }

        return false;
    }

    void print() const {
        for (Slot element : table) {
            if (element.state == Slot::State::EMPTY) {
                std::cout << "_ ";
            }
            else if (element.state == Slot::State::TOMBSTONE) {
                std::cout << "* ";
            }
            else {
                std::cout << "<" << element.key << " : " << element.value << ">";
            }
        }
    }

    size_t max_size() const {
        return table.size();
    }

    size_t size() const {
        return current_size;
    }

    bool empty() const {
        return current_size == 0;
    }

    bool full() const {
        return current_size == table.size();
    }
};
