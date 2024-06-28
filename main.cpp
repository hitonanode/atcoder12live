#include "common.hpp"

#include "atcoder12live.hpp"
#include "beamsearch.hpp"
#include "greedy_solver.hpp"

using namespace std;
using lint = long long;
using pint = std::pair<int, int>;
using plint = std::pair<lint, lint>;

struct fast_ios {
    fast_ios() {
        std::cin.tie(nullptr), std::ios::sync_with_stdio(false), std::cout << std::fixed << std::setprecision(20);
    };
} fast_ios_;

int main(int argc, char *argv[]) {
    // if (argc >= 2) { X = std::stoi(argv[1]); }

    Instance ins;
    {
        int n, t;
        cin >> n >> t;
        assert(n == N);
        assert(t == T);
        for (auto &v : ins._d) cin >> v;
    }

    auto ans = beamsearch(ins);

    dump_onlinejudge(encode_solution(ans));

    dbg(get_max_abs_dv(ans));
    dbg(evaluate(ins, ans));

    jdump("maxdv", get_max_abs_dv(ans));
    jdump("score", evaluate(ins, ans));
}
