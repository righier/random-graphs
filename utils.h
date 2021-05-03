#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint8_t u8;

struct Edge {
    int a, b;
    float w;

    Edge() {}
    Edge(int a, int b, int w): a(a), b(b), w(w) {}

    bool operator<(const Edge &other) {
        return w < other.w;
    }
};

class GraphGenerator {
public:
    virtual bool hasNext() = 0;
    virtual Edge next() = 0;
};
