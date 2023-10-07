/*
・きっちり自力AC！
・mapで下からシミュする。要素が追加された時、
　mapの取得済のイテレータが壊れないか分からなかったので、
　一応毎回lower_boundで次の位置を取得してた。
　これだと1.97秒かかってた(それでもTL3秒なので問題はなかったけど)けど、
　要素追加されても普通にイテレータ進めて大丈夫のようだったのでそうしたら、
　0.84秒でかなり速くなった。
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
    vector<ll> S(N), C(N);
    rep(i, N) {
        cin >> S[i] >> C[i];
    }

    map<ll, ll> mp;
    rep(i, N) {
        mp[S[i]] += C[i];
    }
    auto itr = mp.begin();
    ll ans = 0;
    while (itr != mp.end()) {
        auto [k, v] = *itr;
        auto [d, m] = divmod(v, 2LL);
        ans += m;
        if (d > 0) {
            mp[k * 2] += d;
        }
        itr++;
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
