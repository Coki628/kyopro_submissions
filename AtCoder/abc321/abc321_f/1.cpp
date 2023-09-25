/*
・これは自力TLE(をちょっとバグ取りしたもの)。
・部分和DPをFPSで高速に解くやつ使ったんだけどダメだった。
　高速と言っても線形logなので、5000^2の制約じゃきついんだろう。。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll Q, K;
    cin >> Q >> K;
    vector<ll> vec;
    ModTools<mint> mt(K);
    rep(i, Q) {
        char op;
        ll x;
        cin >> op >> x;
        if (op == '+') {
            vec.eb(x);
        } else if (op == '-') {
            vec.erase(find(ALL(vec), x));
        }
        vector<ll> C(K + 1);
        rep(i, vec.size()) {
            if (vec[i] <= K) {
                C[vec[i]]++;
            }
        }
        FPS<mint> ans(K + 1);
        rep(a, 1, K + 1) {
            if (C[a] == 0) continue;
            ll k = 1;
            while (a * k <= K) {
                ans[a * k] += (mint)(k & 1 ? 1 : -1) * mt.div(C[a], k);
                k++;
            }
        }
        ans = ans.exp(K + 1);
        print(ans[K]);
    }
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
