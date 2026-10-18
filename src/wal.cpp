#include "wal.h"
#include <stdexcept>

// Open the file in append mode, so new lines go at the end
// instead of erasing what's already there.
WAL::WAL(const std::string& path) : out_(path, std::ios::app) {
    if (!out_) {
        throw std::runtime_error("Could not open WAL file: " + path);
    }
}

void WAL::append_put(const std::string& key, const std::string& value) {
    out_ << "PUT " << key << " " << value << "\n";
    out_.flush();   // push it to disk right now
}

void WAL::append_remove(const std::string& key) {
    out_ << "DEL " << key << "\n";
    out_.flush();
}