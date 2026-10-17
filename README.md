# lsm-kv

A key-value store built from scratch in modern C++ on a **log-structured merge-tree (LSM)** architecture, the storage-engine design behind LevelDB, RocksDB, and Cassandra.

This is a learning project: the goal is to understand how real storage engines handle fast writes, durability, and crash recovery by building one piece at a time.

## Status

| Component | Status |
|---|---|
| MemTable (in-memory sorted table) | ✅ Done |
| Write-ahead log (crash recovery) | 🔜 Next |
| SSTable flushing (on-disk sorted files) | Planned |
| Compaction (merging SSTables) | Planned |

## How it works so far

All writes go to the **MemTable**, an in-memory table backed by `std::map<std::string, std::optional<std::string>>` so keys stay sorted. Keeping keys in order means the table can later be written to disk as a sorted file (an SSTable) in a single pass.

Supported operations:

- `put(key, value)`: insert or overwrite a key
- `get(key)`: return the latest value, or nothing if the key is missing or deleted
- `remove(key)`: delete a key

**Deletes use tombstones.** Instead of erasing a key, `remove` stores `std::nullopt` as its value, a marker that can never be confused with real data (unlike a sentinel string such as `"DELETED"`). This matters once data lives on disk: an older copy of the key may still exist in a file, and the tombstone is what tells reads to treat it as gone.

## Build and run

Requires a C++17 compiler.

```bash
g++ -std=c++17 -Iinclude -o test_memtable tests/test_memtable.cpp src/memtable.cpp
./test_memtable
```

## Project layout

```
include/   headers (memtable.h)
src/       implementation (memtable.cpp)
tests/     unit tests
```

## Roadmap

1. **Write-ahead log:** append every write to a log file before applying it, so the MemTable can be rebuilt after a crash.
2. **SSTables:** when the MemTable gets full, flush it to an immutable sorted file on disk.
3. **Compaction:** merge SSTables in the background, dropping overwritten keys and expired tombstones.
4. **Benchmarks:** measure write and read throughput, and compare `std::map` against a skip list.
