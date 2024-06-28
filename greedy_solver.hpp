#ifndef GREEDY_SOLVER_HPP
#define GREEDY_SOLVER_HPP

#include "common.hpp"
#include "atcoder12live.hpp"

Solution greedy_solve(const Instance &ins) {
    Solution ans(T, {0, 1, 0});

    std::vector<int> state(N);

    for (int t = 0; t < T; ++t) {
        int best_l = -1, best_r = -1, best_dv = 0, best_eval = 1 << 30;

        for (int l = 0; l < N; ++l) {
            for (int r = l + 1; r <= N; ++r) {
                for (int dv = -10; dv <= 10; ++dv) {
                    int e = 0;
                    for (int i = 0; i < N; ++i) {
                        e += std::abs(ins.val(t, i) - (state.at(i) + (i >= l and i < r ? dv : 0)));
                    }
                    if (chmin(best_eval, e)) {
                        best_l = l;
                        best_r = r;
                        best_dv = dv;
                    }
                }
            }
        }

        ans.at(t) = {best_l, best_r, best_dv};
        for (int i = best_l; i < best_r; ++i) { state.at(i) += best_dv; }
    }

    return ans;
}

#endif
