/*
・自力AC！
・クエリ先読みで座圧、BITに個数と総和
・この日は本番中グタグダで全くここまで来れなかったんだよな。
　ちゃんと問題読んだら、考察実装通しても30分そこそこで解けた。
　こういうのを本番で通せれば嬉しいんだけど、中々うまくはいかんよね…。
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
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }
    ll Q;
    cin >> Q;
    vector<array<ll, 3>> qs;
    Compress<ll> cp;
    rep(i, N) {
        cp.add(A[i]);
    }
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 3) {
            ll x;
            cin >> x;
            qs.pb({op, x, -1});
        } else {
            ll x, y;
            cin >> x >> y;
            x--;
            qs.pb({op, x, y});
            if (op == 1) {
                cp.add(y);
            }
        }
    }
    cp.build();
    ll M = cp.size();

    BIT<ll> bitcnt(M), bitsm(M);
    rep(i, N) {
        bitcnt.add(cp[A[i]], B[i]);
        bitsm.add(cp[A[i]], B[i] * A[i]);
    }
    for (auto [op, x, y] : qs) {
        if (op == 1) {
            bitcnt.add(cp[A[x]], -B[x]);
            bitsm.add(cp[A[x]], -(B[x] * A[x]));
            bitcnt.add(cp[y], B[x]);
            bitsm.add(cp[y], B[x] * y);
            A[x] = y;
        } else if (op == 2) {
            bitcnt.add(cp[A[x]], -B[x]);
            bitsm.add(cp[A[x]], -(B[x] * A[x]));
            bitcnt.add(cp[A[x]], y);
            bitsm.add(cp[A[x]], y * A[x]);
            B[x] = y;
        } else if (op == 3) {
            ll i = bitcnt.bisearch_back(0, M - 1, x);
            if (i == -1) {
                print(-1);
            } else {
                ll rest = x - bitcnt.query(i + 1, M);
                ll res = cp.unzip(i) * rest + bitsm.query(i + 1, M);
                print(res);
            }
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
