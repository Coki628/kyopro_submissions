/*
・自力AC！
・B解けなくてどん詰まってたけど、終了前にこれ通せたから何とか皮一枚つながった感じ。
・小さい色から決める。残ってる最大最小から長さ取って*2、終わったら自分消す。
　あとその色の要素が0の時は何もしない。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;
    A--;

    vvl adj(K);
    set<ll> se;
    rep(i, N) {
        adj[A[i]].eb(i);
        se.insert(i);
    }
    vector<ll> ans(K);
    rep(c, K) {
        if (adj[c].size()) {
            ll len = *--se.end() - *se.begin() + 1;
            ans[c] = len * 2;
            for (auto i : adj[c]) {
                se.erase(i);
            }
        }
    }
    print(ans);
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
