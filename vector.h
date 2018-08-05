#ifndef INTF_BYTESTREAM__VECTOR_H
#define INTF_BYTESTREAM__VECTOR_H

#include <vector>
#include "bytestream.h"

namespace bytestream {

template<typename T>
inline ostreambuf_t& operator||(ostreambuf_t& obytestream, std::vector<T> const& container)
{
    obytestream || static_cast<uint16_t>(container.size());
    for (T const& v : container)
    {
        obytestream || v;
    }
    return obytestream;
}

template<typename T>
inline istreambuf_t& operator||(istreambuf_t& ibytestream, std::vector<T>& container)
{
    uint16_t size;
    ibytestream || size;
    container.reserve(size);
    for (int i = 0; i < size; ++i)
    {
        T v;
        ibytestream || v;
        container.emplace_back(std::move(v));
    }
    return ibytestream;
}

}; // namespace bytestream

#endif // INTF_BYTESTREAM__VECTOR_H
