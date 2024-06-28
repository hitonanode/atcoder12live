#ifndef GREEDY_SOLVER_HPP
#define GREEDY_SOLVER_HPP

#include "common.hpp"
#include "atcoder12live.hpp"

std::vector<std::pair<int, Op>>
find_best_ops(const std::array<int, N> &state, const Instance &ins, int current_turn, int sz) {
    std::vector<std::pair<int, Op>> best_ops;

    static std::array<int, N> diffs;

    int diff_l1 = 0;
    {
        int last = 0;
        for (int v : state) diff_l1 += std::abs(v - last), last = v;
    }

    constexpr int UB = 4;
    constexpr int W = 8;
    constexpr int D = 1 << (UB - 1);

    for (int dv = -5; dv <= 5; ++dv) {
        if (dv == 0) continue;

        for (int i = 0; i < N; ++i) {
            int e = 0;
            const int c = state.at(i) + dv;

            for (int turn = 0; turn < UB; ++turn) {
                if (current_turn + turn >= T) break;
                const int u = std::abs(ins.val(current_turn + turn, i) - c) -
                              std::abs(ins.val(current_turn + turn, i) - state.at(i));
                e += u * (D >> turn);
            }

            diffs.at(i) = e;
        }

        int cs = 0;
        int max_cs = 0;
        int arg_maxcs = 0;

        for (int i = 0; i < N; ++i) {
            const int left_dy = std::abs(state.at(i) + dv - (i ? state.at(i - 1) : 0)) -
                                std::abs(state.at(i) - (i ? state.at(i - 1) : 0));

            const int right_dy = std::abs(state.at(i) + dv - (i + 1 < N ? state.at(i + 1) : 0)) -
                                 std::abs(state.at(i) - (i + 1 < N ? state.at(i + 1) : 0));

            if (chmax(max_cs, cs - left_dy * W)) arg_maxcs = i;
            cs += diffs.at(i);

            int e = cs + (right_dy + diff_l1) * W - max_cs;
            best_ops.emplace_back(e, Op{arg_maxcs, i + 1, dv});
        }
    }

    std::partial_sort(best_ops.begin(), best_ops.begin() + std::min<int>(sz, best_ops.size()), best_ops.end());
    best_ops.resize(std::min<int>(sz, best_ops.size()));

    return best_ops;
}

Solution greedy_solve(const Instance &ins) {
    Solution ans(T, {0, 1, 0});

    std::array<int, N> state;
    state.fill(0);

    for (int t = 0; t < T; ++t) {

        auto op = find_best_ops(state, ins, t, 11).at(0).second;
        ans.at(t) = op;

        auto [best_l, best_r, best_dv] = op;
        for (int i = best_l; i < best_r; ++i) state.at(i) += best_dv;
    }

    return ans;
}

#endif
