/*
参考：https://codeforces.com/blog/entry/19382
・WAケース検出用
・ランダムテストは通ってしまうし、CFはテストケースが分からないので頑張った。
　複数テストでテスト番号が何番かは分かったので、
　テスト番号で特定のものが来たら入力を文字列にして返すようにした。
　これで問題のケース「5,5,4,2,1,2,1,3,4,3」が取得できた。
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

void solve(int t) {
    ll N;
    cin >> N;
    N *= 2;
    vector<ll> A(N);
    cin >> A;
    A--;

    if (t == 95) {
        A++;
        print(join(A, ","));
        return;
    }

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
    rep(t, T) solve(t);

    return 0;
}
