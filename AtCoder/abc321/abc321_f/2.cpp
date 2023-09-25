/*
参考：https://atcoder.jp/contests/abc321/submissions/45866294
・自力ならず。悔しい。
・戻すDP、スパースなFPS演算
・題意を読み解くと、「部分和DPがあって、
　クエリで途中の遷移が増えたりなくなったりするから、
　その変化を線形くらいの計算量で更新しなよ」って感じ。
　FPSで戻すDPやる方針は思ったんだけど、
　FPSしばらく触ってなかったのもあり、詰め切れなかった。。
　DP遷移とFPS演算の対応がどう動くのかも正しく思い出せてなかった。
　ちゃんとメモしとこう…。
・ちなみにここで書いた実装はクエリ先読みとか頑張ってるんだけど、
　別にやらないで普通にその時々で必要な遷移を追加・削除すれば問題ない…。
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

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll Q, K;
    cin >> Q >> K;

    const int MX = 5000;
    vvl adj(MX + 1);
    vector<tuple<char, ll, ll>> qs;
    rep(i, Q) {
        char op;
        ll x;
        cin >> op >> x;
        if (op == '+') {
            // xを入れたindexを保持
            adj[x].eb(i);
            qs.pb({op, i, x});
        } else if (op == '-') {
            ll j = adj[x].back();
            adj[x].pop_back();
            qs.pb({op, j, 0});
        }
    }

    FPS<mint> F(K + 1);
    vector<ll> A(Q);
    F[0] = 1;
    rep(i, Q) {
        auto [op, j, x] = qs[i];
        if (op == '+') {
            A[j] = x;
            // x^0 + x^A[j]
            F *= SFPS<mint>{{0, 1}, {A[j], 1}};
        } else if (op == '-') {
            F /= SFPS<mint>{{0, 1}, {A[j], 1}};
            A[j] = 0;
        }
        while (F.size() > K + 1) F.pop_back();
        mint res = F[K];
        print(res);
    }
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
