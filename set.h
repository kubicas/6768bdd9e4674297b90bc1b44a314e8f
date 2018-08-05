#ifndef INTF_BYTESTREAM__SET_H
#define INTF_BYTESTREAM__SET_H

#include <set>
#include "bytestream.h"

namespace bytestream {

template<typename T>
inline ostreambuf_t& operator||(ostreambuf_t& obytestream, std::set<T> const& container)
{
    obytestream || static_cast<uint16_t>(container.size());
    for (T const& v : container)
    {
        obytestream || v;
    }
    return obytestream;
}

template<typename T>
inline istreambuf_t& operator||(istreambuf_t& ibytestream, std::set<T>& container)
{
    uint16_t size;
    ibytestream || size;
    for (int i = 0; i < size; ++i)
    {
        T v;
        ibytestream || v;
        container.insert(v);
    }
    return ibytestream;
}

}; // namespace bytestream

#endif // INTF_BYTESTREAM__SET_H
