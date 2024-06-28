#ifndef GREEDY_SOLVER_HPP
#define GREEDY_SOLVER_HPP

#include "common.hpp"
#include "atcoder12live.hpp"

Solution greedy_solve(const Instance &ins) {
    Solution ans(T, {0, 1, 0});

    std::array<int, N> state;
    state.fill(0);

    std::array<int, N> diffs;

    for (int t = 0; t < T; ++t) {
        int best_l = -1, best_r = -1, best_dv = 0, best_eval = 1 << 30;

        for (int dv = -5; dv <= 5; ++dv) {
            if (dv == 0) continue;

            for (int i = 0; i < N; ++i) {
                int e = 0;
                const int c = state.at(i) + dv;

                constexpr int UB = 4;
                for (int turn = 0; turn < UB; ++turn) {
                    if (t + turn >= T) break;
                    const int u = std::abs(ins.val(t + turn, i) - c) - std::abs(ins.val(t + turn, i) - state.at(i));
                    e += u * (1 << (UB - turn - 1));
                }

                diffs.at(i) = e;
            }

            int cs = 0;
            int max_cs = 0;
            int arg_maxcs = 0;
            for (int i = 0; i < N; ++i) {
                cs += diffs.at(i);
                if (chmax(max_cs, cs)) arg_maxcs = i + 1;

                if (chmin(best_eval, cs - max_cs)) {
                    best_l = arg_maxcs;
                    best_r = i + 1;
                    best_dv = dv;
                }
            }
        }

        ans.at(t) = {best_l, best_r, best_dv};
        for (int i = best_l; i < best_r; ++i) state.at(i) += best_dv;
    }

    return ans;
}

#endif
