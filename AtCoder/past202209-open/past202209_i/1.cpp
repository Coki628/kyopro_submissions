/*
・自力AC！
・周期
・制約のでかさとマルチテストケースを見て、
　あー、数学だったら嫌だなぁ、、って思いながら考察して、
　これは周期でいけるやつだなぁと分かって、
　周期もちょっと嫌だなぁとか思いながらも実装した。
　やってみると、今回の周期は途中始まりもないし、
　周期に入る前もないし、まとめる所と後ろの尻尾だけ気にすればいいので、
　思ったより面倒な感じでもなかった。
・あと公式解説によるとfloor_sumに帰着していい感じに解けるみたい。
　see: https://atcoder.jp/contests/past202209-open/editorial/4970
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
    ll N, A, M;
    cin >> N >> A >> M;

    vector<ll> cycle;
    ll cur = 0;
    while (1) {
        ll nxt = (cur + A) % M;
        cycle.eb(nxt);
        cur = nxt;
        if (cur == 0) {
            break;
        }
    }

    ll L = cycle.size();
    ll sm = 0;
    rep(i, L) {
        sm += (M - cycle[i] % M) % M;
    }
    auto [d, m] = divmod(N, L);
    ll res = sm * d;
    rep(i, m) {
        res += (M - cycle[i] % M) % M;
    }
    print(res);
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
