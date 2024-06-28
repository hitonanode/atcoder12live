#ifndef BEAMSEARCH_HPP
#define BEAMSEARCH_HPP

#include <queue>
#include <vector>

#include "atcoder12live.hpp"
#include "greedy_solver.hpp"

struct State {
    std::array<int, N> val;
    int turn = 0;
    int par_id = -1;
    Op par_op;
    int cost = 0;

    static State initial_state() {
        State s;
        s.val.fill(0);
        return s;
    }

    // comp
    bool operator<(const State &rhs) const { return cost < rhs.cost; }

    State apply(const Op &op, const Instance &ins, int par_id) const {
        auto [l, r, dv] = op;
        State nxt = *this;
        for (int i = l; i < r; ++i) nxt.val.at(i) += dv;

        for (int i = 0; i < N; ++i) { nxt.cost += std::abs(ins.val(nxt.turn, i) - nxt.val.at(i)); }

        nxt.par_op = op;

        nxt.par_id = par_id;
        nxt.turn += 1;

        return nxt;
    }
};

Solution beamsearch(const Instance &ins) {
    std::vector<State> states;
    states.push_back(State::initial_state());

    using pint = std::pair<int, int>;
    std::vector<pint> bests; // (idx, score)

    bests.emplace_back(0, 0);

    constexpr int BEAM_WIDTH = 500;

    for (int t = 0; t < T; ++t) {
        const auto target = ins.vals(t);

        std::vector<std::tuple<int, int, Op>> nxt_bests; // score, idx, op
        for (auto [idx, score] : bests) {
            const auto &state = states.at(idx);
            auto ops = find_best_ops(state.val, ins, t, 20);
            for (auto [e, op] : ops) {
                int ee = e + state.cost * 8;
                nxt_bests.emplace_back(ee, idx, op);
            }
        }
        std::partial_sort(
            nxt_bests.begin(), nxt_bests.begin() + std::min<int>(BEAM_WIDTH, nxt_bests.size()), nxt_bests.end());

        if (nxt_bests.size() > BEAM_WIDTH) nxt_bests.resize(BEAM_WIDTH);

        bests.clear();
        for (auto [tmp_score, idx, op] : nxt_bests) {

            const int nxt_id = states.size();
            states.push_back(states.at(idx).apply(op, ins, idx));
            bests.emplace_back(nxt_id, states.back().cost);
        }
    }

    Solution ans;
    int head = bests.at(0).first;
    for (int t = 0; t < T; ++t) {
        ans.push_back(states.at(head).par_op);
        head = states.at(head).par_id;
    }
    std::reverse(ans.begin(), ans.end());

    return ans;
}

#endif
