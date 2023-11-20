/*
・終了後自力AC、、、悔しい。
・数列ペア数え上げ、2冪、式変形
・また式変形がぱっと気付かなかったー。。まじで弱点だな。
　とりあえず必要な値をAで表すと、(2^Ai)^(2^Aj)とその逆になるんだけど、
　全部2冪上にあるので、ひとまずそれを外す。Ai*2^Ajとなる。
　ここまで来るのも指数部分の変形とかで大変だった。
　で、Ai*2^Aj=Aj*2^Aiを満たすペアを数えたいので、
　これを式変形してAi/2^Ai=Aj/2^Ajとする。これでi,jが左右に分けれたので、
　それぞれの要素をこの形にできればこれをキーとして同値ペアを数えられる。
　まともにやると2冪が超でかくなってしまうので、
　分子側を素因数2とその他に分けて、素因数には分母と打ち消す。
　これで(その他,素因数2の個数)の形で要素を表せたので、mapに詰めて数える。
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
    vector<ll> A(N);
    cin >> A;

    map<pll, ll> C;
    rep(i, N) {
        ll p2 = 0;
        ll rest = A[i];
        while (rest % 2 == 0) {
            rest /= 2;
            p2++;
        }
        ll x = rest;
        ll y = A[i] - p2;
        // Ai / 2^Ai
        C[{x, y}]++;
    }
    ll ans = 0;
    for (auto [k, v] : C) {
        ans += nC2(v);
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
