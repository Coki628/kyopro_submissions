/*
参考：https://atcoder.jp/contests/abc223/editorial/3584
　　　https://atcoder.jp/contests/abc223/submissions/30147315
・クエリ系、XOR基底、クエリ平方分割
・色々頑張ってみた。クエリ平方分割で、端数の部分も累積持つと1回で済むのは新しい知見だった。
　(自分が今まで見落としてただけで、普通はそうするものなのかも…。)
・他にも累積和配列をvectorから生配列にするとか、まあ色々やってるんだけどTLE。
　0.2秒くらい足りなくて4ケース落ちる。(制約3秒)
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/SparseTable.hpp"
#include "numbers/XorBasis.hpp"

const int MXLOG = 60;
auto f = [](XorBasis<ll> a, XorBasis<ll> b) {
    if (a.rank() == MXLOG or b.rank() == 0) {
        return a;
    }
    if (b.rank() == MXLOG or a.rank() == 0) {
        return b;
    }
    for (auto b : b.basis) {
        a.add(b);
    }
    return a;
};
const XorBasis<ll> T;

const int D = 50;
// L = 400000 / D + 1
const int L = 8001;
vector<pll> bucket[L];
XorBasis<ll> accl[L][D+1], accr[L][D+1];

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    rep(i, N) {
        bucket[i/D].pb({A[i], i});
    }
    // 同一区間内での基底取得高速化のため、前後からの累積を取っておく
    rep(i, L) {
        if (bucket[i].size()) {
            XorBasis<ll> cur;
            rep(j, bucket[i].size()) {
                accl[i][j] = cur;
                cur.add(bucket[i][j].first);
            }
            accl[i][bucket[i].size()] = cur;

            cur = XorBasis<ll>();
            rep(j, bucket[i].size()-1, -1, -1) {
                accr[i][j+1] = cur;
                cur.add(bucket[i][j].first);
            }
            accr[i][0] = cur;
        }
    }

    // 各区間bucket[i]全体を表す基底を前計算
    vector<XorBasis<ll>> tmp(L);
    rep(i, L) {
        for (auto [a, j] : bucket[i]) {
            tmp[i].add(a);
        }
    }
    auto st = get_sparse_table(tmp, f, T);

    rep(_, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--;

        XorBasis<ll> basis;
        ll ld = l / D;
        ll rd = (r-1) / D;
        // 左端と右端が同じ区間
        if (ld == rd) {
            rep(i, l, r) {
                basis.add(A[i]);
            }
        } else {
            // 全部を含む区間はまとめて処理
            basis = st.query(ld+1, rd);
            // 累積を使って端数もまとめて処理
            ll mo = l % D;
            basis = f(basis, accr[ld][mo]);
            mo = (r-1) % D;
            basis = f(basis, accl[rd][mo+1]);
            // // 左右の端は愚直に見る
            // for (auto& [a, i] : bucket[ld]) {
            //     if (l <= i and i < r) {
            //         basis.add(A[i]);
            //     }
            // }
            // for (auto& [a, i] : bucket[rd]) {
            //     if (l <= i and i < r) {
            //         basis.add(A[i]);
            //     }
            // }
        }
        if (basis.exists(x)) {
            Yes();
        } else {
            No();
        }
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
