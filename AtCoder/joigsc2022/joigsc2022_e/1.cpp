/*
・JOI埋め
・きっちり自力AC！
・累積和にぶたん、後ろからDP
・問題設定がこの前やったabc158_eのジャガイモとほぼ同じかと思ったら結構違った。
　こちらは無限に続く訳ではなくNが終われば終了だし、
　最後の箱に入れた重さとかが必要になって結構勝手が違う。
　結局、後ろからDPで確定していって、にぶたんで遷移先を決める、みたいにやる。
　ダブリングとか周期とかは要らない。
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
    ll N, L;
    cin >> N >> L;
    auto W = LIST(N);

    Accumulate<ll> acc(W);
    vector<ll> weight(N), cnt(N);
    rep(i, N-1, -1, -1) {
        ll j = bisearch_min(i-1, N+1, [&](ll r) {
            return acc.query(i, r) > L;
        });
        if (j == N+1) {
            weight[i] = acc.query(i, N);
            cnt[i] = 1;
        } else {
            weight[i] = weight[j-1];
            cnt[i] = cnt[j-1] + 1;
        }
    }
    rep(k, N) {
        print(mkp(cnt[k], weight[k]));
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
