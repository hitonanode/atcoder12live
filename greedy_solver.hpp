#ifndef GREEDY_SOLVER_HPP
#define GREEDY_SOLVER_HPP

#include "common.hpp"
#include "atcoder12live.hpp"

std::vector<std::pair<int, Op>>
find_best_ops(const std::array<int, N> &state, const Instance &ins, int current_turn, int sz) {
    std::vector<std::pair<int, Op>> best_ops;

    static std::array<int, N> last_vs;

    constexpr int UB = 4;

    for (int dv = -5; dv <= 5; ++dv) {
        if (dv == 0) continue;

        for (int l = 0; l < N; ++l) {
            for (int r = l + 1; r <= N; ++r) {
                int cost = 0;
                int last_v = 0;

                for (int i = 0; i < N; ++i) {
                    const int nxt_v = state.at(i) + (l <= i and i < r) * dv;

                    for (int turn = 0; turn < UB; ++turn) {
                        if (current_turn + turn >= T) break;
                        cost += abs(ins.val(current_turn + turn, i) - nxt_v) << (UB - turn - 1);
                    }

                    cost += abs(last_v - nxt_v) * 4;
                    last_v = nxt_v;
                }

                cost += abs(last_v);

                // for (int turn = 0; turn < UB; ++turn) {
                //     if (current_turn + turn >= T) break;

                //     int left = l ? ins.val(current_turn + turn, l - 1) : 0;

                //     const int nxt_v = state.at(l) + dv;
                //     cost += (abs(left - nxt_v) - abs(left - state.at(l))) << (UB - turn - 1);

                //     int right = r + 1 < N ? ins.val(current_turn + turn, r) : 0;

                //     const int nxt_v2 = state.at(r - 1) + dv;
                // }

                best_ops.emplace_back(cost, Op{l, r, dv});
            }
        }

        // for (int i = 0; i < N; ++i) {
        //     int e = 0;
        //     const int c = state.at(i) + dv;

        //     for (int turn = 0; turn < UB; ++turn) {
        //         if (current_turn + turn >= T) break;
        //         const int u = std::abs(ins.val(current_turn + turn, i) - c) -
        //                       std::abs(ins.val(current_turn + turn, i) - state.at(i));
        //         e += u * (1 << (UB - turn - 1));
        //     }

        //     diffs.at(i) = e;
        // }

        // int cs = 0;
        // int max_cs = 0;
        // int arg_maxcs = 0;
        // for (int i = 0; i < N; ++i) {
        //     cs += diffs.at(i);
        //     if (chmax(max_cs, cs)) arg_maxcs = i + 1;

        //     int eval = cs - max_cs;

        //     if (eval < 0) { best_ops.emplace_back(eval, Op{arg_maxcs, i + 1, dv}); }
        // }
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
