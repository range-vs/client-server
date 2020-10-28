#pragma once

#include <array>

enum class TYPE_OPERATION: unsigned
{
    ADD = 0,
    CHECK,
    _DELETE,
    NONE = -1
};

class TransportBlock
{
    enum { HEADER_LENGTH = 8, DATA_LENGTH = 1024 };

    // header: 1 - type message, 2 - reserve

    std::array<char, HEADER_LENGTH + DATA_LENGTH> msg;

public:
    TransportBlock();
    void copyHeader(const TYPE_OPERATION& to, int not_used = -1);
    void copyData(const char* d);
    char* data();
    size_t size();
    size_t sizeHeader();
    size_t sizeBlock();
    char* dataHeader();
    char* dataBlock();
};