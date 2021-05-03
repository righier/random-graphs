#pragma once

#include "random.h"
#include "utils.h"

#include <cmath>
#include <algorithm>
#include <vector>


std::vector<Edge> randomGraph(Random &rnd, int n, i64 m, float maxw) {
	std::vector<Edge> edges;

	i64 maxm = i64(n) * (i64(n)-1) / 2;
	m = std::min(m, maxm);

	double ilogp = 1.0 / std::log(1.0 - double(m) / double(maxm));
	

	return edges;
}

class RandomGraphGenerator: public GraphGenerator {
    int n, maxw;
    double ilogp;
	Random &rnd;

	int a, b;

public:
	RandomGraphGenerator(Random &rnd, int n, i64 m, float maxw):
	n(n), maxw(maxw), rnd(rnd), a(0), b(0) {
		i64 maxm = i64(n) * (i64(n)-1) / 2;
		if (m > maxm) m = maxm;
		ilogp = 1.0 / std::log(1.0 - double(m) / double(maxm));
		advance();
	}

	bool hasNext() {
		return a < n-1;
	}

	Edge next() {
		float weight = rnd.getFloat() * maxw;
		auto out = Edge(a, b, weight);
		advance();
		return out;
	}

	void advance() {
		double p0 = rnd.getDouble();
		double logpp = log(p0) * ilogp;
		int skip = std::max(int(logpp) + 1, int(1));
		b += skip;

		while (b >= n) {
			b += ++a + 1 - n;
		}
	}
};