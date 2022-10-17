/*
・きっちり自力AC！
・次に'g'が出現する位置を覚えておいて、cがきたらchmax 前計算は適当に2,3周させた。
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
    char c;
    cin >> N >> c;
    string S;
    cin >> S;

    S = S + S + S;
    vector<ll> nxt(N*3, -1);
    rep(i, N*3-2, -1, -1) {
        if (S[i] == 'g') {
            nxt[i] = 0;
        } else {
            nxt[i] = nxt[i+1] + 1;
        }
    }

    ll ans = 0;
    rep(i, N) {
        if (S[i] == c) {
            chmax(ans, nxt[i]);
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
