/*
・きっちり自力AC！
・上位ビットから貪欲
・題意を整理すると、K回好きなビットを足せる感じになるので、
　各ビットで残り必要な数を数えて、上位ビットから貪欲にやる。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ll L = 31;
    vector<ll> need(L);
    rep(i, L) {
        rep(j, N) {
            if (!(A[j] >> i & 1)) {
                need[i]++;
            }
        }
    }
    ll cur = K, ans = 0;
    rep(i, L - 1, -1, -1) {
        if (cur >= need[i]) {
            cur -= need[i];
            ans += 1LL << i;
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
