#ifndef LSM_KV_MEMTABLE_H
#define LSM_KV_MEMTABLE_H

#include <map>
#include <string>
#include <optional>

class MemTable {
public:
    void put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    void remove(const std::string& key);
    size_t size() const; // number of entries, including tombstones

private:
    // value = a real value, std::nukkopt = tombstone (key was deleted)
    std::map<std::string, std::optional<std::string>> table_;
};

#endif