#include "memtable.h"

void MemTable::put(const std::string& key, const std::string& value) {
    table_[key] = value;
}

std::optional<std::string> MemTable::get(const std::string& key) const {
    auto it = table_.find(key);
    if (it == table_.end()) {
        return std::nullopt;
    }
    return it->second;
}

void MemTable::remove(const std::string& key) {
    table_[key] = std::nullopt; // leaves a tombstone instead of erasing
}

size_t MemTable::size() const {
    return table_.size();
}