/*
参考：https://twitter.com/momohara_kyopro/status/1670065075925975040
・クエリ先読み、座圧BIT、BIT2本で個数と総和
・動的にK番目までの和を求めるこれも、BIT2本のやつで求まる。汎用性高い。
　今回は同値があるので境界ちと面倒かと思ったけど、そんなじゃなかった。
　多分set2本でガチャガチャ出し入れする方がめんどい。
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
    ll N, K, Q;
    cin >> N >> K >> Q;
    Compress<ll> cp;
    vector<pll> qs;
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        x--;
        qs.eb(x, y);
        cp.add(y);
    }
    cp.add(0);
    cp.build();
    ll M = cp.size();

    BIT<ll> bitcnt(M), bitsm(M);
    vector<ll> A(N);
    rep(i, N) {
        bitcnt.add(0, 1);
        bitsm.add(0, 0);
    }
    for (auto [x, y] : qs) {
        y = cp[y];
        bitcnt.add(A[x], -1);
        bitsm.add(A[x], -cp.unzip(A[x]));
        bitcnt.add(y, 1);
        bitsm.add(y, cp.unzip(y));
        A[x] = y;

        ll i = bitcnt.bisearch_back(0, M - 1, K);
        // 境界だけ全部じゃないので個数取って別処理にする
        ll restcnt = K - bitcnt.query(i + 1, M);
        ll res = restcnt * cp.unzip(i) + bitsm.query(i + 1, M);
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
