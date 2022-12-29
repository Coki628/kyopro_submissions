/*
参考：https://twitter.com/kude_coder/status/1607779647877701634
・自力ならず。
・添字GCD畳み込み、大きい方から貪欲
・とりあえずグラフの全辺ペアについてgcd(u, v)を求めて集計しておきたい。
　グラフということで全然見えなかったんだけど、
　これは全ペアのgcdなので添字GCD畳み込みで求まる。気付きたいよねーこういうの。
　で、それが求まったら、貪欲にgcdが大きい方から使っていけばいい。
　この貪欲が必ず正しいのか分からなくなるけど、
　大きい方がまとめて辺を消費できるからまあ確かにお得感はある。
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

#include "numbers/gcd_convolution.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    vector<ll> A(N + 1, 1);
    A[0] = 0;
    auto res = gcd_convolution(A, A);
    rep(i, 1, N + 1) {
        res[i]--;
    }
    ll L = res.size();
    rep(i, L) {
        res[i] /= 2;
    }

    ll ans = 0, cur = M;
    rep(g, L - 1, 1, -1) {
        ll use = min(res[g], cur) / (g - 1) * (g - 1);
        cur -= use;
        ll opcnt = use / (g - 1);
        ans += opcnt * g;
    }
    if (cur == 0) {
        print(ans);
    } else {
        print(-1);
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
