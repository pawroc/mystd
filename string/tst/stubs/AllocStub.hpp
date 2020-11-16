#pragma once

#include <cstdint>

std::size_t allocCount{0};
std::size_t deallocCount{0};
std::size_t allocBytes{0};
std::size_t deallocBytes{0};

void resetAllocStats()
{
    allocCount = deallocCount = allocBytes = deallocBytes = 0;
}

template<std::size_t N>
struct AllocStub
{
    char* allocate(std::size_t n)
    {
        allocBytes += n;
        ++allocCount;
        return buf;
    }

    void deallocate(char*, std::size_t n)
    {
        deallocBytes += n;
        ++deallocCount;
    }

    char buf[N];
};
