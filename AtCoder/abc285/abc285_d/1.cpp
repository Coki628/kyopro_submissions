/*
・きっちり自力AC！
・有向グラフの閉路検出
・依存関係の有向辺を張って閉路検出。
・終了後TLより。迷いなく有向辺張ってDFSで有向グラフの閉路検出貼ったけど、
　今回の問題設定だと無向とみなしてUFでもOKなのね。。
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
    ll N;
    cin >> N;
    vector<string> S(N), T(N);
    map<string, ll> mp;
    rep(i, N) {
        cin >> S[i] >> T[i];
        mp[S[i]] = i;
    }

    vvi nodes(N);
    rep(i, N) {
        if (mp.count(T[i])) {
            ll j = mp[T[i]];
            nodes[i].eb(j);
        }
    }
    vector<ll> memo(N, -1);
    auto dfs = [&](auto &&f, ll u) -> void {
        if (memo[u] == 1) return;
        elif (memo[u] == 0) {
            No();
            exit(0);
        }
        memo[u] = 0;

        for (ll v : nodes[u]) {
            f(f, v);
        }
        memo[u] = 1;
    };
    rep(i, N) {
        dfs(dfs, i);
    }
    Yes();
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
