/*
・O(N)なら悩みそう。制約は緩いので2乗で愚直シミュ。
　それでも(Bにしては)ちとめんどいと思った。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto A = LIST(N);

    vector<ll> V;
    V.eb(0);
    rep(i, N) {
        for (auto& v : V) {
            v = (v+A[i])%360;
        }
        V.eb(0);
    }
    sort(ALL(V));
    ll ans = 0;
    rep(i, N) {
        chmax(ans, V[i+1]-V[i]);
    }
    chmax(ans, 360-V.back());
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
