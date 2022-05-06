/*
・なんとか自力AC！
・木グラフ、DFS、マージテク
・葉側からのパスを1本だけ残して親に渡す、みたいなDFSをやる。
　普通にやったらTLEで、子から受けたパスが大きい時にマージテクしたら通った。
・長いパスを残すのがいいと思ってパス長持ってソートしたんだけど、
　これ今よく考えると残すパスどれでもよさそうね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto P = LIST(N);
    rep(i, N) P[i]--;

    vvi nodes(N);
    ll r = -1;
    rep(i, N) {
        if (P[i] != i) {
            nodes[i].eb(P[i]);
            nodes[P[i]].eb(i);
        } else {
            r = i;
        }
    }

    vvi ans;
    auto dfs = [&](auto&& f, int u, int prv) -> vector<pair<int, vector<int>>> {
        vector<pair<int, vector<int>>> res;
        ll sz = 0;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            auto tmp = f(f, v, u);
            if (sz < tmp[0].first) {
                sz += tmp[0].first;
                swap(res, tmp);
            } else {
                sz += tmp[0].first;
            }
            for (auto p : tmp) {
                res.eb(p);
            }
        }
        if (res.empty()) {
            return {{1, {u}}};
        } else {
            sort(res.rbegin(), res.rend());
            while (res.size() > 1) {
                ans.eb(res.back().second);
                res.pop_back();
            }
            res[0].first++;
            res[0].second.eb(u);
            return res;
        }
    };
    auto res = dfs(dfs, r, -1);
    ans.eb(res[0].second);

    print(ans.size());
    rep(i, ans.size()) {
        print(ans[i].size());
        reverse(ALL(ans[i]));
        rep(u, ans[i].size()) ans[i][u]++;
        print(ans[i]);
    }
    print();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
