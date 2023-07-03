/*
・自力AC！
・せっかく作ってあったFractionクラスが初期化で約分してなくて大幅タイムロス。。
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

#include "numbers/Fraction.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<pair<Fraction<ll>, ll>> A;
    rep(i, N) {
        ll a, b;
        cin >> a >> b;
        A.pb({{a, a + b}, i + 1});
    }

    sort(ALL(A), [](pair<Fraction<ll>, ll> a, pair<Fraction<ll>, ll> b) {
        if (a.first == b.first) {
            return a.second < b.second;
        } else {
            return a.first > b.first;
        }
    });
    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = A[i].second;
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
