/*
・これは自力TLE。
・N2側の頂点(a,b)でループを回して、その中の辺を見るんだけど、
　N2側は辺の数は多いから多分それでTLEしちゃう。
　swapで次数少ない方優先したりはしてるけど、全然通らない。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N1, N2, M;
    cin >> N1 >> N2 >> M;
    ll N = N1 + N2;
    vector<HashSet<int>> nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].insert(v);
        nodes[v].insert(u);
    }

    rep(a, N1, N) {
        rep(b, a+1, N) {
            vector<ll> cur = {a, b};
            if (nodes[a].size() < nodes[b].size()) {
                for (auto c : nodes[a]) {
                    if (nodes[b].count(c)) {
                        cur.eb(c);
                    }
                    if (cur.size() == 4) {
                        rep(i, 4) cur[i]++;
                        print(cur);
                        return;
                    }
                }
            } else {
                for (auto c : nodes[b]) {
                    if (nodes[a].count(c)) {
                        cur.eb(c);
                    }
                    if (cur.size() == 4) {
                        rep(i, 4) cur[i]++;
                        print(cur);
                        return;
                    }
                }
            }
        }
    }
    print(-1);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
