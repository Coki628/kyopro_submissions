/*
参考：https://blog.hamayanhamayan.com/entry/2020/01/11/145024
・自力ならず。途中までの方針は悪くなかった。10WAから前に進めず。。
・LCM、実験エスパー
・とりあえずサンプルからそれっぽいものを整えると、10WAになり詰まる。
　手元で色々見てみると、なんかLCMが偶数になる時ダメになる場合がありそうで、
　なんだけどうまくいく場合もある。その先の規則性を見つけられず。
・結局必要だったのは「LCMがいずれかのAiの偶数倍だったらダメ」なんだけど、
　これは手元からじゃあきっと見つけられないなぁって感じ。
　はまやんさんも実験で見つけてたようだし、スゴイ考察力がなければ、
　こういうのは考えるより手動かして頑張るしかないんだろうなぁ。。
・昔の自分は粘って何とか通していたようなのですごい。(つらい)
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;

    rep(i, N) {
        A[i] /= 2;
    }
    ll l = 1;
    rep(i, N) {
        l = lcm(l, A[i]);
        if (l > M) {
            print(0);
            return;
        }
    }
    rep(i, N) {
        ll x = l / A[i];
        // LCMがAiの偶数倍だったらダメ(これが見つけられなかった)
        if (x % 2 == 0) {
            print(0);
            return;
        }
    }
    ll ans = ceil(M / l, 2LL);
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
