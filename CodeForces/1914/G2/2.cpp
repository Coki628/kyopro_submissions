/*
・これはWA。一度見た要素は消すようにしたら、合わなくなってしまった…。
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
    UnionFind uf(N);
    vector<ll> R(N);
    iota(ALL(R), 0);
    BIT<ll> bit(N);
    rep(i, N) {
        if (seg[A[i]].first == i) {
            bit.add(i, 1);
        }
    }
    rep(i, N) {
        if (seg[A[i]].second == i) {
            ll j = seg[A[i]].first;
            uf.merge(i, j, [&](ll r, ll ch) {
                if (r == -1) return;
                chmax(R[r], R[ch]);
            });
            ll k = j;
            while (1) {
                k = bit.bisearch_fore(k + 1, i - 1, 1);
                if (k != -1) {
                    uf.merge(i, k, [&](ll r, ll ch) {
                        if (r == -1) return;
                        chmax(R[r], R[ch]);
                    });
                    bit.add(k, -1);
                } else {
                    break;
                }
            }
            if (bit[j] == 1) {
                bit.add(j, -1);
            }
            // rep(k, j + 1, i) {
            //     if (seg[A[k]].first == k and seg[A[k]].second > i) {
            //         uf.merge(i, k, [&](ll r, ll ch) {
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
        ll r = uf.find(i);
        mn++;
        cnt *= uf.size(r);
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
