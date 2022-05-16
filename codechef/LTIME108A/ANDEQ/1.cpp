/*
・きっちり自力AC！
・とりあえず全要素立ってるビットは消えないので除外した。これで0を目指す。
　で、全要素反転させると「この要素で消せるビット」みたいな状態にできて、
　これを前からorしていって、全ビット消せた所で1回区切る(操作回数が減る)のを貪欲にやったら通った。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    ll has_all = A[0];
    rep(i, 1, N) {
        has_all &= A[i];
    }
    rep(i, N) {
        A[i] ^= has_all;
    }

    ll msk = (1LL<<30) - 1;
    rep(i, N) {
        A[i] ^= msk;
    }
    ll cur = 0, cnt = 0;
    rep(i, N) {
        cur |= A[i];
        if (cur == msk) {
            cnt++;
            cur = 0;
        }
    }
    ll ans = N - cnt;
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
