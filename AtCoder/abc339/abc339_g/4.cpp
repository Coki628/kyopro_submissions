/*
・一応こっちの別解もやっておく。
・平方分割
・区間を平方分割しておくやつ。ブロック毎に累積和を取っておく。
　なんだけど、√N*Nサイズのll累積和を取っておくとメモリがきつかった。
　普通に均等にするやつだとダメで、ブロックサイズを大きめ、
　ブロック数を少なめにした。これだと愚直する部分が多くなるが、
　ブロック数=長さNの累積和配列の個数を少なくできる。
　ブロックサイズ500だと2.20秒(制約3.5秒)のメモリ951MBでギリギリだったけど、
　もっと大きく1000にしたら、1.14秒の481MBだったので、
　思った以上にブロックサイズを大きくしてよかった。
　これだと1クエリで最悪ループが1000くらい回るはずなので、
　20万*1000=2億くらいになるが、これはあくまで最悪の場合だし、
　C++は単純な処理めっちゃ速いからまあこんな感じなんだろう。
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

    A.eb(INF);
    Compress<ll> cp(A);
    ll M = cp.size();
    // ll D = ceil(sqrt(N));
    // ブロックサイズ
    ll D = 1000;
    // ブロック数
    ll L = N / D + 1;
    vector<Accumulate<ll>> acc(L, {M});
    rep(i, N) {
        acc[i / D].add(cp[A[i]], A[i]);
    }
    rep(d, L) {
        acc[d].build();
    }

    ll Q;
    cin >> Q;
    ll b = 0;
    rep(i, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l ^= b, r ^= b, x ^= b;
        l--;

        ll res = 0;
        ll ld = l / D;
        ll rd = (r - 1) / D;
        // 左端と右端が同じ区間
        if (ld == rd) {
            rep(i, l, r) {
                if (A[i] <= x) {
                    res += A[i];
                }
            }
        } else {
            // 左右の端は愚直に見る
            rep(i, l, (ld + 1) * D) {
                if (A[i] <= x) {
                    res += A[i];
                }
            }
            rep(i, rd * D, r) {
                if (A[i] <= x) {
                    res += A[i];
                }
            }
            // 全部を含む区間はまとめて処理
            ll cpx = cp[x + 1];
            rep(d, ld + 1, rd) {
                res += acc[d].query(0, cpx);
            }
        }
        print(res);
        b = res;
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
