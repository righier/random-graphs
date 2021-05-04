#pragma once

#include "utils.h"
#include <limits>
#include <functional>


class kdTree {
public:

    kdTree(std::vector<Pos> &points): kdTree(points.begin(), points.end()) {}

    template<class Iter>
    kdTree(Iter begin, Iter end, bool dim=0) {
        Iter mid = begin + (end - begin)/2;
        Pos minp = *begin, maxp = *begin;
        for (Iter it=begin; it<end; it++) {
            minp = min(minp, *it);
            maxp = max(maxp, *it);
        }
        this->boxHalfSize = (maxp - minp) / 2.f;
        this->boxCenter = minp + this->boxHalfSize;
        this->dim = dim;

        std::nth_element(begin, mid, end, comp());
        this->pos = *mid;
        this->id = mid - begin;

        if (mid-begin > 0) { this->left  = new kdTree(begin, mid, !dim); }
        if (end-mid > 1)   { this->right = new kdTree(mid+1, end, !dim); }
    }

    ~kdTree() {
        if (left) delete left;
        if (right) delete right;
    }

    Pos closest(const Pos &p, int id) {
        Pos best;
        float bestDist = std::numeric_limits<float>::infinity();
        closest(p, id, best, bestDist);
        return best;
    }

private:
    kdTree *left = nullptr, *right = nullptr;
    Pos pos, boxCenter, boxHalfSize;
    int id;
    bool dim;

    std::function<bool(const Pos&, const Pos &)> comp() { return dim ? compY : compX; }
    static bool compX(const Pos &a, const Pos &b) { return a.x < b.x; }
    static bool compY(const Pos &a, const Pos &b) { return a.y < b.y; }

    float minDist(const Pos &p) {
        return len2(max(Pos(0, 0), abs(p - boxCenter) - boxHalfSize));
    }

    void closest(const Pos &p, int id, Pos &best, float &bestDist) {
        if (minDist(p) < bestDist) {

        }
    }
};