#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint8_t u8;

typedef std::pair<float,int> NodeEdge;
typedef std::vector<NodeEdge> Node;
typedef std::vector<Node> Graph;

struct Edge {
    int a, b;
    float w;

    Edge() {}
    Edge(int a, int b, float w): a(a), b(b), w(w) {}

    bool operator<(const Edge &other) {
        return w < other.w;
    }
};

class GraphGenerator {
public:
    virtual bool hasNext() = 0;
    virtual Edge next() = 0;
};

static std::vector<Edge> generatorToEdges(GraphGenerator &gen) {
	std::vector<Edge> edges;
	while(gen.hasNext()) {
		edges.emplace_back(gen.next());
	}
	return edges;
}

static Graph edgesToGraph(const std::vector<Edge> &edges) {
    int n = 0;
    for (const Edge &e: edges) {
        n = std::max(n, std::max(e.a, e.b)+1);
    }

    Graph g(n);
    for (const Edge &e: edges) {
        g[e.a].emplace_back(std::make_pair(e.w, e.b));
        g[e.b].emplace_back(std::make_pair(e.w, e.a));
    }
    return g;
}