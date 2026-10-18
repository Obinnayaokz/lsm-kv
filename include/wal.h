#ifndef LSM_KV_WAL_H
#define LSM_KV_WAL_H

#include <fstream>
#include <string>

class WAL {
public:
    WAL(const std::string& path);   // open (or create) the log file
    void append_put(const std::string& key, const std::string& value);
    void append_remove(const std::string& key);

private:
    std::ofstream out_;             // the open file we write to
};

#endif