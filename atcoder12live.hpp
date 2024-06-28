#ifndef ATCODER12LIVE_HPP
#define ATCODER12LIVE_HPP

#include <array>
#include <cassert>
#include <string>
#include <tuple>
#include <vector>

constexpr int N = 50;
constexpr int T = 500;

constexpr int Vmax = 3;

struct Instance {
    std::array<int, N * T> _d;
    Instance() { _d.fill(0); }

    int S0() const {
        int ret = 0;
        for (auto &v : _d) { ret += v > 0 ? v : -v; }
        return ret;
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const Instance &ins) {
        os << "[";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < T; j++) { os << ins._d[i * T + j] << " "; }
            os << "]";
        }
        return os;
    }

    int val(int t, int x) const {
        assert(0 <= t and t < T);
        assert(0 <= x and x < N);
        return _d.at(t * N + x);
    }
};

using Solution = std::vector<std::tuple<int, int, int>>; // l, r, dv

std::string encode_solution(const Solution &sol) {
    std::string ret;
    for (const auto &[l, r, dv] : sol) {
        ret += std::to_string(l) + " " + std::to_string(r - 1) + " " + std::to_string(dv) + "\n";
    }
    if (ret.size()) ret.pop_back();
    return ret;
}

int evaluate(const Instance &ins, const Solution &sol) {
    int S = 0;

    std::array<int, N> state;
    state.fill(0);
    for (int t = 0; t < T; ++t) {
        auto [l, r, dv] = sol.at(t);
        for (int pos = l; pos < r; ++pos) {
            state.at(pos) += dv;
        }

        for (int i = 0; i < N; ++i) S += std::abs(ins.val(t, i) - state.at(i));
    }

    return std::max(ins.S0() - S + 1, 0);
}

#endif
