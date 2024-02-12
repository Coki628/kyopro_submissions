/*
・自力AC！
・最初プリキューでやってTLEしたので、
　ああ、きっと2とかがめちゃ多くなるんだな、と思って、
　同値を個数まとめて処理できるようにmapを使った。
・想定はメモ化再帰だったみたい。まあ確かにそれでもいけるか。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve() {
    ll N;
    cin >> N;

    map<ll, ll> mp;
    ll ans = 0;
    mp[N] = 1;
    while (mp.size()) {
        auto itr = --mp.end();
        auto [k, v] = *itr;
        mp.erase(itr);
        ans += k * v;
        ll y1 = k / 2;
        ll y2 = ceil(k, 2LL);
        if (y1 > 1) {
            mp[y1] += v;
        }
        if (y2 > 1) {
            mp[y2] += v;
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
