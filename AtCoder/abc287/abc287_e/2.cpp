/*
参考：https://twitter.com/kyopro_friends/status/1619332267779964929
・公式解は多分こっち。
・Trie木、再帰探索
・Trie木っぽく再帰で構築する。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> S(N);
    cin >> S;

    ll L = 26;
    vector<ll> ans(N), P(N);
    iota(ALL(P), 0);
    auto rec = [&](auto &&f, ll i, const vector<ll> &vec) -> void {
        vvl adj(L);
        for (auto j : vec) {
            if (vec.size() >= 2) {
                chmax(ans[j], i);
            }
            if (i < S[j].size()) {
                adj[S[j][i] - 'a'].eb(j);
            }
        }
        rep(c, L) {
            if (adj[c].size()) {
                f(f, i + 1, adj[c]);
            }
        }
    };
    rec(rec, 0, P);
    print(ans, '\n');
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
