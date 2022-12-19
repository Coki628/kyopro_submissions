/*
・きっちり自力AC！
・二部グラフ判定
・まず最初の状態で二部グラフかどうかチェック。問題なければ、
　連結成分毎に、二部グラフを壊してしまう辺の本数を数える。
　これは二部の同じ側で辺を繋ぐ全ペアなのですぐ数えられる。
　全ての辺からMと上記を引けば、二部グラフを保てる辺の本数になる。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    UnionFind uf(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        uf.merge(u, v);
    }

    vector<ll> C(N, -1);
    auto dfs = [&](auto &&f, ll u, ll c) -> bool {
        if (C[u] != -1) {
            return C[u] == c;
        }
        C[u] = c;
        for (auto v : nodes[u]) {
            if (!f(f, v, 1 - c)) {
                return false;
            }
        }
        return true;
    };
    rep(i, N) {
        if (C[i] == -1) {
            if (!dfs(dfs, i, 0)) {
                print(0);
                return;
            }
        }
    }

    map<pll, ll> C2;
    rep(i, N) {
        assert(C[i] != -1);
        C2[{uf.find(i), C[i]}]++;
    }
    ll ans = N * (N - 1) / 2 - M;
    for (auto [k, v] : C2) {
        ans -= v * (v - 1) / 2;
    }
    print(ans);
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
