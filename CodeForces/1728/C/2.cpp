/*
参考：https://twitter.com/AllDirections4/status/1567916842307690496
・multiset、貪欲
・なんかmultisetのcountがO(個数)みたいな話があったし気になって試してみた。
　TLE想定だったのに普通に通ってしまった。
　AllDirectionsさんのはTLEしてたのに、よく分からん。
　プリキュー*HashMapが0.36秒、multisetが0.47b秒だからさほど極端に遅くもないし。
・まあでもこれで通るなら、個数管理とか一緒にできて楽だよね。
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

const auto f = [](ll a) -> ll {
    return tostr(a).size();
};

void solve() {
    ll N;
    cin >> N;
    auto A = listnd(2, N, 0LL);
    rep(i, 2) {
        A[i] = LIST(N);
    }

    multiset<ll> se[2];
    rep(i, 2) {
        rep(j, N) {
            se[i].insert(A[i][j]);
        }
    }
    ll ans = 0;
    while (se[0].size() or se[1].size()) {
        // 末尾要素で大きい方から使う
        ll i = *--se[0].end() < *--se[1].end();
        ll a = *--se[i].end(); se[i].erase(--se[i].end());
        if (se[1-i].count(a)) {
            se[1-i].erase(se[1-i].find(a));
        } else {
            a = f(a);
            ans++;
            se[i].insert(a);
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
