#include "memtable.h"
#include <iostream>
#include <cassert>

int main() {
    MemTable table;

    table.put("name", "Obinnaya");
    auto result = table.get("name");
    assert(result.has_value());
    assert(result.value() == "Obinnaya");
    std::cout << "[PASS] put/get works\n";

    auto missing = table.get("nothing_here");
    assert(!missing.has_value());
    std::cout << "[PASS] missing key returns nothing\n";

    table.remove("name");
    assert(!table.get("name").has_value());
    std::cout << "[PASS] remove works\n";

    std::cout << "All tests passed.\n";
    return 0;
}