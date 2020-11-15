#pragma once

#include <cstring>

namespace mystd
{
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
};

constexpr string::string() : sz{0}, buf{0}, ptr{buf}
{
}

string::~string()
{
    if (ptr != buf)
    {
        delete[] ptr;
    };
}

size_t string::size() const noexcept
{
    return sz;
}

size_t string::capacity() const noexcept
{
    return ptr == buf ? smallStringSize : sz + space;
}

const char* string::c_str() const noexcept
{
    return ptr;
}

void string::assign(const char* str)
{
    if (not str) return;

    sz = strlen(str);
    if (strlen(str) > smallStringSize)
    {
//        allocate(strlen(str));
        ptr = new char[strlen(str) + 1];
        space = 2 * smallStringSize - sz;
    }
    memcpy(ptr, str, strlen(str));
    ptr[strlen(str)] = 0;
}

string& string::operator=(const char* newString)
{
    assign(newString);
    return *this;
}
}
