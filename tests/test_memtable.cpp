#include "memtable.h"
#include <iostream>
#include <cassert>

int main() {
    // ---------- Test 1: put then get ----------
    // Save a value, then read it back and check it's the same.
    {
        MemTable t;
        t.put("name", "Obinnaya");
        auto result = t.get("name");
        assert(result.has_value());              // something came back
        assert(result.value() == "Obinnaya");    // and it's the right value
        std::cout << "[PASS] put/get works\n";
    }

    // ---------- Test 2: missing key ----------
    // Asking for a key that was never saved returns nothing.
    {
        MemTable t;
        assert(!t.get("nothing_here").has_value());
        std::cout << "[PASS] missing key returns nothing\n";
    }

    // ---------- Test 3: remove ----------
    // After deleting a key, get() acts as if it doesn't exist.
    {
        MemTable t;
        t.put("name", "Obinnaya");
        t.remove("name");
        assert(!t.get("name").has_value());
        std::cout << "[PASS] remove works\n";
    }

    // ---------- Test 4: deletes are tombstones, not erasures ----------
    // Removing "a" keeps it in the table as a tombstone, so size stays 2.
    {
        MemTable t;
        t.put("a", "1");
        t.put("b", "2");
        t.remove("a");
        assert(t.size() == 2);                   // "a" is still stored, as a tombstone
        assert(!t.get("a").has_value());         // but reads treat it as gone
        assert(t.get("b").value() == "2");       // and "b" is untouched
        std::cout << "[PASS] remove leaves a tombstone\n";
    }

    // ---------- Test 5: tombstone for a key never seen ----------
    // Deleting an unknown key still records the delete, in case
    // an older value exists on disk.
    {
        MemTable t;
        t.remove("ghost");
        assert(!t.get("ghost").has_value());
        assert(t.size() == 1);                   // the tombstone is stored
        std::cout << "[PASS] remove on unknown key leaves a tombstone\n";
    }

    // ---------- Test 6: put after remove brings the key back ----------
    // A new put replaces the tombstone with a real value.
    {
        MemTable t;
        t.put("song", "old");
        t.remove("song");
        t.put("song", "new");
        assert(t.get("song").value() == "new");
        std::cout << "[PASS] put after remove restores the key\n";
    }

    std::cout << "All 6 tests passed.\n";
    return 0;
}