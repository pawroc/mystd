#pragma once

#include <cstring>
#include <cstdint>
#include <memory>

namespace mystd
{

template<class Allocator = std::allocator<char>>
class string final
{
    static constexpr std::uint8_t smallStringSize{15};

public:
    constexpr string();
    ~string();

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    const char* c_str() const noexcept;

    string& operator=(const char* newString);

private:
    void assign(const char* str);

private:
    size_t sz;
    union
    {
        size_t space; // free space when dynamic allocation done
        char buf[smallStringSize + 1]; // 15 chars + NULL sign
    };
    char* ptr;
    Allocator alloc;
};

template<class Allocator>
constexpr string<Allocator>::string() : sz{0}, buf{0}, ptr{buf}, alloc{}
{
}

template<class Allocator>
string<Allocator>::~string()
{
    if (ptr != buf)
    {
        alloc.deallocate(ptr, space + 1);
    };
}

template<class Allocator>
size_t string<Allocator>::size() const noexcept
{
    return sz;
}

template<class Allocator>
size_t string<Allocator>::capacity() const noexcept
{
    return ptr == buf ? smallStringSize : sz + space;
}

template<class Allocator>
const char* string<Allocator>::c_str() const noexcept
{
    return ptr;
}

template<class Allocator>
void string<Allocator>::assign(const char* str)
{
    if (not str) return;

    auto newSz = strlen(str);
    if (newSz > capacity())
    {
        char* p = nullptr;
        if (ptr == buf)
        {
            space = 0;
            p = alloc.allocate(newSz + 1);
        }
        else
        {
            space = 2 * capacity() - newSz;
            p = alloc.allocate(capacity() + 1);
        }

        if (p)
        {
            ptr = p;
        }
    }
    else
    {
        if (ptr != buf)
        {
            if (newSz < sz)
            {
                space += sz - newSz;
            }
            else if(newSz > sz)
            {
                space -= newSz - sz;
            }
        }
    }

    memcpy(ptr, str, newSz);
    sz = newSz;
    ptr[newSz] = 0;
}

template<class Allocator>
string<Allocator>& string<Allocator>::operator=(const char* newString)
{
    assign(newString);
    return *this;
}
}
