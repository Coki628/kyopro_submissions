/*
・Div.3残埋め
・なんとか自力AC！
・連続部分列、区間和、区間積、積はすぐ大きくなる
・まず1の時だけ積が損をするので、ここを特別扱いする。
　両端に余分な1を含ませるのは明らかに損なので、2以上の要素だけで作った数列で、
　全ペアから最適が取れれば良さそう。あと積はすぐ大きくなるので、
　十分大きくなりそうな場合は両端(1除く)を使うとした。
　それだけ大きければ1で作る和が勝つはずがないので。
　で、これでもペアが2乗ある。単調性でにぶたんとかできないか考えたけど無理で、
　適当に手元で試して端だけ試せば良さそうとかやったら嘘で、
　しばらく悩んで難しかったけど、よくよく考えると、
　十分大きいものを弾いてる時点で、2以上を集めた数列はかなり数が少なくなってる。
　具体的には、全部2だったとしてもせいぜい60個くらいまでのはず。
　これは普通に2重ループでペア全探索が効くので、やる。
　んー、こういうのもっとすぐ気付けるようになりたいなぁ…。
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
    vector<ll> A(N);
    cin >> A;

    vector<ll> B, btoa;
    rep(i, N) {
        if (A[i] > 1) {
            B.eb(A[i]);
            btoa.eb(i);
        }
    }
    if (B.empty()) {
        print({1, 1});
        return;
    }

    // 積が十分大きい時は両端(1除く)を使った方がいい
    ll mul = 1;
    ll i = btoa[0];
    ll j = btoa.back();
    for (auto b : B) {
        if (mul_overflow(mul, b)) {
            print({i + 1, j + 1});
            return;
        }
        mul *= b;
    }

    // 大きくないなら、2以上の要素の数はそんなに多くないのでペア全探索
    ll M = B.size();
    Accumulate<ll> acc(A);
    vector<ll> acc2(M + 1, 1);
    rep(i, M) {
        acc2[i + 1] = acc2[i] * B[i];
    }
    ll mx = 0;
    pll ans;
    rep(i, M) {
        rep(j, i, M) {
            ll ii = btoa[i];
            ll jj = btoa[j];
            ll cur = acc.query(0, ii) + (acc2[j + 1] / acc2[i]) + acc.query(jj + 1, N);
            if (chmax(mx, cur)) {
                ans = {ii + 1, jj + 1};
            }
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
