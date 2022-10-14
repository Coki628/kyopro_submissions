/*
・互いに素、効率よく全探索
・同じ値を何回も見る意味はないので、indexが一番後ろのやつだけ取っておいて、
　そこから全ペア試す。値の範囲は1000なので2乗でOK。
・枝刈り頑張って無理矢理やってしまったけど、
　こうやって先に値を減らしておけばよかったんだな…。
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
    auto A = LIST(N);

    vector<bool> used(1001);
    vector<pll> B;
    rep(i, N-1, -1, -1) {
        if (used[A[i]]) continue;
        used[A[i]] = true;
        B.eb(A[i], i);
    }

    ll ans = -1;
    ll M = B.size();
    rep(i, M) {
        rep(j, i, M) {
            auto [b1, k1] = B[i];
            auto [b2, k2] = B[j];
            if (gcd(b1, b2) == 1) {
                chmax(ans, k1+k2+2);
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
