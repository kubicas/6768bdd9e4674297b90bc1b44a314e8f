#ifndef INTF_BYTESTREAM__STRING_H
#define INTF_BYTESTREAM__STRING_H

#include <string>
#include "bytestream.h"

namespace bytestream {

inline ostreambuf_t& operator||(ostreambuf_t& obytestream, std::string const& container)
{
    obytestream || static_cast<uint16_t>(container.size());
    for (char v : container)
    {
        obytestream || v;
    }
    return obytestream;
}

inline istreambuf_t& operator||(istreambuf_t& ibytestream, std::string& container)
{
    uint16_t size;
    ibytestream || size;
    container.resize(size);
    for (int i = 0; i < size; ++i)
    {
        char v;
        ibytestream || v;
        container[i] = v;
    }
    return ibytestream;
}

}; // namespace bytestream

#endif // INTF_BYTESTREAM__STRING_H
