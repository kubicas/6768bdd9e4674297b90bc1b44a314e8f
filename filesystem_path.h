#ifndef INTF_BYTESTREAM__FILESYSTEM_PATH_H
#define INTF_BYTESTREAM__FILESYSTEM_PATH_H

#include "stb/filesystem.h" // stubbable version of <filesystem>
#include "bytestream.h"
#include <algorithm>

namespace bytestream {

inline ostreambuf_t& operator||(ostreambuf_t& obytestream, stb::filesystem::path const& container)
{
    uint16_t size = 0;
    for (stb::filesystem::path::const_iterator it = container.begin(); it != container.end(); ++it, ++size);
    obytestream || static_cast<uint16_t>(size);
    for (auto& part : container)
    {
        obytestream || part.string();
    }
    return obytestream;
}

inline istreambuf_t& operator||(istreambuf_t& ibytestream, stb::filesystem::path& container)
{
    uint16_t size;
    ibytestream || size;
    for (int i = 0; i < size; ++i)
    {
        std::string part;
        ibytestream || part;
        container /= part;
    }
    return ibytestream;
}

}; // namespace bytestream

#endif // INTF_BYTESTREAM__FILESYSTEM_PATH_H
