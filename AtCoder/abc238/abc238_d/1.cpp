/*
・andの条件より、aで立ってる所はx,y両方立たせる必要がある。
　この時点で既に和の方より大きくなってしまったら即NG。
　後は残ってるビットは上位桁から貪欲と信じる。
　(考えたら当然なんだけど)残ってるやつは片側ずつしか使えないことに
　気付くのにしばらく時間がかかって2WA。残念。
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
    ll a, s;
    cin >> a >> s;

    const ll L = 60;
    vector<bool> X(L), Y(L);
    ll sm = 0;
    rep(i, L) {
        if (a>>i & 1) {
            X[i] = true;
            Y[i] = true;
            sm += (1LL<<i)*2;
        }
    }
    if (sm > s) {
        No();
        return;
    }
    rep(i, L-1, -1, -1) {
        if (not X[i] and sm+(1LL<<i) <= s) {
            sm += 1LL<<i;
            X[i] = true;
        }
    }
    rep(i, L-1, -1, -1) {
        if (not X[i] and not Y[i] and sm+(1LL<<i) <= s) {
            sm += 1LL<<i;
        }
    }
    if (sm == s) {
        Yes();
    } else {
        No();
    }
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
