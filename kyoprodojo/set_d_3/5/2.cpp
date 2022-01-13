/*
・arc119_c
・自力ならず。。
・偶奇で分ける、式変形
・条件を見つけるのも大変だったけど、「偶奇で分けて区間和が等しくなる所」
　の高速化もできなかった…。
・これはこのままだときつくて、式変形して右辺を0にしてzero sum rangesに帰着、ってやる。
　いやー、出なかったな。その手前の考察までが何とか出ただけに悔しい。
　2乗ペア高速化系はめっちゃ出るんだから、もう考察リスト作ってガッチリ固めた方がいいよな。
・ちなみに最初の条件見つけるパートは、公式解の式にする方針が思いつきやすそうって
　昔の自分も書いてたけど、今もそう思う。結局ガチャガチャ操作して筋力で無理やり導いたんだけど…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    rep(i, N) {
        if (i%2 == 1) {
            A[i] = -A[i];
        }
    }

    auto acc = A;
    rep(i, N-1) {
        acc[i+1] += acc[i];
    }
    acc.insert(acc.begin(), 0);

    map<ll, ll> mp;
    ll ans = 0;
    rep(i, N+1) {
        ans += mp[acc[i]];
        mp[acc[i]]++;
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
