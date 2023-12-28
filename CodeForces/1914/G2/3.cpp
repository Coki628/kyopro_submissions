/*
・これは実はもうほぼ正解だったんだけどWA。
　どういうことしてるかはACコードのコメント参照。
・提出が96個目のテストケースでWAが出て、
　ランダムテスト書いても全部ACだし、もうどうしようかと思った。
　結局、「iota(ALL(R), 0);」が余計だったのが原因だった。
　確かに色毎の管理にしたから、後ろの方の添字で値が若いこと全然あるよね…。
　逆に何でそこまで滅多にWAが出なかったのか不思議なくらいではある。
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
    vector<ll> R(N / 2), L(N / 2);
    iota(ALL(R), 0);
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
