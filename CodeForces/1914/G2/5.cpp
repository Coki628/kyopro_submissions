/*
参考：https://twitter.com/shobonvip/status/1737160811431539128
・自力ならずはいいとして、大変だったー。。
・交差する区間、UF、BITにぶたん
・G1からの発展として、まずは交差する区間を高速に取得する必要がある。
　これは右端を左から見て行って「左端が自身の左端と右端の間にあり、右端が自身の右端より右にある」
　ようなもの(言語化するとややこしいね)を探した。
　BITに左端を入れておき、自身の右端が来た所で取得、終わったら自身の左端はBITから消す、
　とやるとうまくできた。
　でもこれでもまだ、該当の区間を取りに行く所でBITにぶたんをとてもたくさんやることになりTLEになる。
　そこで、比較的近い方針を取っていたしょぼんさんのツイートを参考にした。
　UFで組ませた区間は同一視できる。これをBIT上でもマージすることにした。
　具体的には、BITに入れておく左端としてはなるべく右にある方が得なので、
　UFで連結成分内で一番右にある左端を覚えさせておいて、ここにBIT上での左端もまとまる。
　こうすることで、探しに行く位置は1箇所で済むようになる。
　自身の左端をBITから消す時にも、UF代表点の情報をうまく使って消す。
　ここまで行ってからも最後のバグ取りが大変だったけど、まあそれは本質じゃないので…。
・BITにぶたんのバグが取れたり(これは上記最後のやつとは別)、
　UFのマージ時に他のもの(今回はBIT)を連動させてうまく状態管理したり、
　色々ためになることがあって、バチャで挑めて良かった。まあ大変だったけど。
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
    N *= 2;
    vector<ll> A(N);
    cin >> A;
    A--;

    vector<pll> seg(N / 2, {-1, -1});
    rep(i, N) {
        if (seg[A[i]].first == -1) {
            seg[A[i]].first = i;
        } else {
            seg[A[i]].second = i;
        }
    }
    UnionFind uf(N / 2);
    // R[i]:= 連結成分iの中で一番右にある右端
    // L[i]:= 連結成分iの中で一番右にある左端
    vector<ll> R(N / 2), L(N / 2);
    BIT<ll> bit(N);
    rep(i, N) {
        if (seg[A[i]].first == i) {
            bit.add(i, 1);
            chmax(L[A[i]], i);
        } else {
            chmax(R[A[i]], i);
        }
    }
    rep(i, N) {
        if (seg[A[i]].second == i) {
            ll j = seg[A[i]].first;
            ll k = j;
            while (1) {
                // debug(bit);
                k = bit.bisearch_fore(k + 1, i - 1, 1);
                if (k != -1) {
                    uf.merge(A[i], A[k], [&](ll r, ll ch) {
                        if (r == -1) return;
                        ll cnt = bit[L[r]] + bit[L[ch]];
                        bit.add(L[r], -bit[L[r]]);
                        bit.add(L[ch], -bit[L[ch]]);
                        chmax(R[r], R[ch]);
                        chmax(L[r], L[ch]);
                        bit.add(L[r], cnt);
                    });
                } else {
                    break;
                }
            }
            bit.add(L[uf.find(A[j])], -1);
            // rep(k, j + 1, i) {
            //     if (seg[A[k]].first == k and seg[A[k]].second > i) {
            //         uf.merge(A[i], A[k], [&](ll r, ll ch) {
            //             if (r == -1) return;
            //             chmax(R[r], R[ch]);
            //         });
            //     }
            // }
        }
    }
    ll i = 0, mn = 0;
    mint cnt = 1;
    while (i < N) {
        ll r = uf.find(A[i]);
        mn++;
        cnt *= uf.size(r) * 2;
        i = R[r] + 1;
    }
    print(mkp(mn, cnt));
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
