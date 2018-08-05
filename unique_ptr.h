#ifndef INTF_BYTESTREAM__UNIQUE_PTR_H
#define INTF_BYTESTREAM__UNIQUE_PTR_H

#include <memory>
#include "bytestream.h"

namespace bytestream {

template<typename T>
inline bytestream::ostreambuf_t& operator||(bytestream::ostreambuf_t& streambuf, std::unique_ptr<T> const& p)
{
    return streambuf || *p.get();
}

template<typename T>
inline bytestream::istreambuf_t& operator||(bytestream::istreambuf_t& istreambuf, std::unique_ptr<T>& p)
{
    make_unique(p);
    return istreambuf || *p.get();
}

}; // namespace bytestream

#endif // INTF_BYTESTREAM__UNIQUE_PTR_H
