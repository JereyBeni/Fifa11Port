#ifndef BIG_PARSER_H
#define BIG_PARSER_H

#include <vector>
#include <string>
#include <cstdint>

struct BigFileEntry {
    uint32_t offset;
    uint32_t size;
    std::string name;
};

class BigArchiveParser {
private:
    std::string archivePath;
    uint32_t swapEndian(uint32_t val);

public:
    explicit BigArchiveParser(const std::string& path);
    bool parse(std::vector<BigFileEntry>& outEntries);
};

#endif // BIG_PARSER_H