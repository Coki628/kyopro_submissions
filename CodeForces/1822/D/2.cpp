/*
・自力ならず。
・順列、構築
・結論から言えば、(mod Nで)0,1,-2,3,-4,5...と並べるとうまくいく。
　これを累積したら0,1,-1,2,-2,3...となってとても都合良くなってる。
　がしかし、これどうやって気付くんよって感じなんだけど、
　みんな「サンプルのN=6のケースの答えから察せ」の一点張りでマジでひどい。
　そこ見て見えなかったらどうすれば良かったんだろうか。
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

void solve() {
    ll N;
    cin >> N;

    if (N == 1) {
        print(1);
        return;
    } else if (N % 2 == 1) {
        print(-1);
        return;
    }
    vector<ll> ans(N);
    ans[0] = N;
    rep(i, 1, N) {
        if (i % 2 == 1) {
            ans[i] = i;
        } else {
            ans[i] = N - i;
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
