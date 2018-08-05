#ifndef INTF_BYTESTREAM__BYTESTREAM_H
#define INTF_BYTESTREAM__BYTESTREAM_H

#include <streambuf>
#include "exception/exception.h"

namespace bytestream {

class ostreambuf_t
    : public std::streambuf
{
public:
    template<typename T, std::enable_if_t<std::is_integral<T>{}> * = nullptr>
    ostreambuf_t& operator||(T v)
    {
        for (int i = sizeof(v) - 1; i >= 0; --i)
        {
            write_byte(static_cast<unsigned char>(v >> (8 * i)));
        }
        return *this;
    }
private:
    void write_byte(unsigned char b)
    {
        sputc(b);
    }
};
static_assert(sizeof(ostreambuf_t) == sizeof(std::streambuf)); // to allow reinterpret_cast from std::streambuf to obytestream_t

class istreambuf_t
    : public std::streambuf
{
public:
    template<typename T, std::enable_if_t<std::is_integral<T>{}> * = nullptr, std::enable_if_t<!std::is_same<T, bool>{}> * = nullptr>
    istreambuf_t& operator||(T& v)
    {
        v = 0;
        for (int i = 1; i < sizeof(v); ++i)
        {
            v |= read_byte();
            v <<= 8;
        }
        v |= read_byte();
        return *this;
    }
    template<typename T, std::enable_if_t<std::is_same<T,bool>{}> * = nullptr>
    istreambuf_t& operator||(T& v)
    {
        v = read_byte();
        return *this;
    }
private:
    unsigned char read_byte()
    {
        int c = sbumpc();
        if (c == EOF)
        {
            THROW( std::ios_base::failure, << "Unexpected end of file");
        }
        return (c & 0xff);
    }
};
static_assert(sizeof(istreambuf_t) == sizeof(std::streambuf)); // to allow reinterpret_cast from std::streambuf to ibytestream_t

template<typename B> struct is_bytestreambuf : std::false_type {};
template<>           struct is_bytestreambuf<istreambuf_t> : std::true_type {};
template<>           struct is_bytestreambuf<ostreambuf_t> : std::true_type {};
#define BYTESTREAM_ENABLE_IF_IS_BYTESTREAM_BUF(B) std::enable_if_t<bytestream::is_bytestreambuf<B>{}> * = nullptr
#define BYTESTREAM_ENABLE_IF_IS_BYTESTREAM_BUF_DEFINITION(B) std::enable_if_t<bytestream::is_bytestreambuf<B>{}> *
template<typename B, typename T> struct parameter_type : std::false_type {};
template<            typename T> struct parameter_type<istreambuf_t,T> { using type = T;       };
template<            typename T> struct parameter_type<ostreambuf_t,T> { using type = T const; };
#define BYTESTREAM_PARAMETER_TYPE(B,T) typename bytestream::parameter_type<B,T>::type

}; // namespace bytestream

#endif // INTF_BYTESTREAM__BYTESTREAM_H
