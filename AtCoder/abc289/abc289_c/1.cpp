/*
・きっちり自力AC！
・ビット全探索
・一時期Cの定番だったけどなんか久々な気がする。
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
    vvl adj(M);
    rep(i, M) {
        ll sz;
        cin >> sz;
        adj[i].resize(sz);
        cin >> adj[i];
        adj[i]--;
    }

    ll ans = 0;
    rep(bit, 1, 1 << M) {
        vector<ll> used(N);
        rep(i, M) {
            if (bit >> i & 1) {
                for (auto a : adj[i]) {
                    used[a] = 1;
                }
            }
        }
        if (sum(used) == N) {
            ans++;
        }
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
