#include "wal.h"
#include <cstdio>
#include <iostream>

int main() {
    std::remove("test.wal");   // delete any old log so we start fresh

    {
        WAL wal("test.wal");
        wal.append_put("name", "Obinnaya");
        wal.append_put("song", "Jukebox");
        wal.append_remove("name");
    }   // the WAL is destroyed here, which closes the file

    std::cout << "Wrote test.wal\n";
    return 0;
}