/*
・upsolve、なんとか自力AC！
　でも時間かかったから本番中通すのはきつかっただろうな。。
・とりあえず真ん中をまとめる。連続部分列を長くするので、
　操作するうち両端のS以外は全てのxを変換したい。
　ここは「K/xの個数」でどのくらいいけるか計算できる。
・上記除算の余りで両端をどう処理するか検討する。この余りをmとして、
　ある位置からm+1個目のx直前までは全部oにできる。
　これは累積和にぶたんで高速に求まるので、左端を全探索。
　Mが十分大きければ(余分に使えるSが2つ以上あれば)、
　中途半端な位置を起点にしても追加のSを置けるので、
　この場合はSを2周使ってSの境界を跨ぐものもチェック。
　余分に使えるSが1つしかなければ、ぴったりSの区切りでまとめて1つ追加を置くか、
　中途半端な位置を起点にしてそこから余った部分を使うだけかになるので、
　この場合はSの境界を跨ぐものは見ないでSを1周でチェック。(この考察で合ってるか？)
　余分なSがなければM個めいっぱい使うのでこれらのチェックはしない。
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
    ll N, M, K;
    cin >> N >> M >> K;
    string S;
    cin >> S;

    ll ans = 0;
    ll xcnt = count(ALL(S), 'x');
    auto [d, m] = divmod(K, xcnt);
    Accumulate<ll> acc(N * 2);
    rep(i, N * 2) {
        if (S[i % N] == 'x') {
            acc.set(i, 1);
        }
    }
    acc.build();
    if (M >= d + 2) {
        rep(l, N * 2) {
            ll r = acc.bisearch_fore(l, N * 2 - 1, m + 1);
            if (r == -1) {
                r = N * 2;
            }
            chmax(ans, r - l);
        }
    } else if (M == d + 1) {
        rep(l, N) {
            ll r = acc.bisearch_fore(l, N - 1, m + 1);
            if (r == -1) {
                r = N;
            }
            chmax(ans, r - l);
        }
    }
    ans += N * min(d, M);
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
