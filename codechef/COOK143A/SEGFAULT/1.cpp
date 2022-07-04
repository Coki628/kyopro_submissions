/*
・自力AC
・区間加算BIT
・各人について犯人になるかを調べる。自身の証言を除いた時に、
　自身にN-1個の区間が掛かっていれば答えに追加。
　この時自身の証言も自分に掛かっているとダメなので、雑に大きい値を一時的に引いた。
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

#include "segment/BIT2.hpp"

void solve() {
    ll N;
    cin >> N;

    BIT2<ll> bit(N);
    vector<ll> L(N), R(N);
    rep(i, N) {
        cin >> L[i] >> R[i];
        L[i]--;
        bit.add(L[i], R[i], 1);
    }
    vector<ll> ans;
    rep(i, N) {
        bit.add(L[i], R[i], -MOD);
        if (bit[i] == N-1) {
            ans.eb(i+1);
        }
        bit.add(L[i], R[i], MOD);
    }
    print(ans.size());
    print(ans, '\n');
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
