#pragma once

#include "random.h"
#include "utils.h"

#include <cmath>
#include <algorithm>
#include <vector>
#include <set>

struct Pos {
	float x, y;
	Pos(float x, float y): x(x), y(y) {}
};

static float dist2(const Pos &a, const Pos &b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return dx*dx + dy*dy;
}

static Pos randomPos(Random &rnd, float s) {
	return Pos(rnd.getFloat()*s, rnd.getFloat()*s);
}

static std::vector<Edge> randomGeometricGraph(Random &rnd, int n, i64 m, float maxcoord) {
	i64 maxm = i64(n) * (i64(n) - 1) / 2;
	if (m > maxm) m = maxm;

	std::vector<Pos> nodes;
	nodes.reserve(n);
	for (int i = 0; i < n; i++) nodes.emplace_back(randomPos(rnd, maxcoord));
	int k = int((double(m) / n) * 2);

	std::cout << "graph name {" << std::endl;

	for (int i = 0; i < n; i++) {
		Pos pos = nodes[i];
		std::string name = "p" + std::to_string(i);
		std::cout << name << " [pos = \"" << pos.x << "," << pos.y << "!\"];" << std::endl;
	}

	std::vector<Edge> edges;

	for (int i = 0; i < n; i++) {
		std::vector<std::pair<float, int>> cand;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				float dist = dist2(nodes[i], nodes[j]);
				cand.emplace_back(std::make_pair(dist, j));
			}
		}
		std::partial_sort(cand.begin(), cand.begin()+k, cand.end());
		for (const auto &c :cand) {
			int a = i;
			int b = c.second;
			if (a > b) std::swap(a, b);
			edges.emplace_back(Edge(a, b, c.first));
		}
	}

	std::sort(edges.begin(), edges.end(), [](Edge &a, Edge &b){
		return (a.a == b.a && a.b < b.b) || (a.a < b.a);
	});
	edges.resize(std::unique(edges.begin(), edges.end(), [](Edge &a, Edge &b) {
		return a.a == b.a && a.b == b.b;
	}) - edges.begin());

	for (Edge e: edges) {
		std::string n1 = "p" + std::to_string(e.a);
		std::string n2 = "p" + std::to_string(e.b);

	}
	std::cout << "}" << std::endl;
	std::cout << edges.size() << std::endl;

	return edges;
}

static std::vector<Edge> randomGraph(Random &rnd, int n, i64 m, float maxw) {
	i64 maxm = i64(n) * (i64(n) - 1) / 2;
	if (m > maxm) m = maxm;

	double ilogp = 1.0 / std::log(1.0 - double(m) / double(maxm)); // inverse logarithm of the probability of not picking an edge
	int a = 0, b = 0;

	std::vector<Edge> edges;
	edges.reserve(m * 1.001); //if the number of edges is big, we almost never need to resize the vector
	while (true) {

		double p0 = rnd.getDouble();
		double logpp = log(p0) * ilogp;
		int skip = std::max(int(logpp) + 1, int(1));
		b += skip;

		while (b >= n) { b += ++a - n + 1; }

		if (a >= n-1) break;

		float weight = rnd.getFloat() * maxw;
		edges.emplace_back(Edge(a, b, weight));
	}
	return edges;
}