/*
・自力AC！
・座圧BITで個数と総和
・使う缶切りの数を全探索。BIT2本個数と総和のやつでシミュした。
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
    ll N, M;
    cin >> N >> M;
    Compress<ll> cp;
    vector<ll> T(N), X(N), A, B, C;
    rep(i, N) {
        cin >> T[i] >> X[i];
        if (T[i] == 0) {
            A.eb(X[i]);
            cp.add(X[i]);
        } else if (T[i] == 1) {
            B.eb(X[i]);
            cp.add(X[i]);
        } else {
            C.eb(X[i]);
        }
    }
    cp.build();
    ll L = cp.size();
    ll n1 = A.size();
    ll n2 = B.size();
    ll n3 = C.size();
    sort(B.rbegin(), B.rend());
    sort(C.rbegin(), C.rend());
    rep(i, n1) {
        A[i] = cp[A[i]];
    }
    rep(i, n2) {
        B[i] = cp[B[i]];
    }
    BIT<ll> bitcnt(L), bitsm(L);
    rep(i, n1) {
        bitcnt.add(A[i], 1);
        bitsm.add(A[i], cp.unzip(A[i]));
    }
    ll ans = 0;
    ll j = bitcnt.bisearch_back(0, L - 1, M);
    if (j == -1) {
        chmax(ans, bitsm.query(0, L));
    } else {
        ll rest = M - bitcnt.query(j + 1, L);
        chmax(ans, rest * cp.unzip(j) + bitsm.query(j + 1, L));
    }
    ll k = 0;
    rep(i, n3) {
        while (k < n2 and C[i] > 0) {
            bitcnt.add(B[k], 1);
            bitsm.add(B[k], cp.unzip(B[k]));
            k++;
            C[i]--;
        }
        ll m = M - i - 1;
        if (m == 0) break;
        j = bitcnt.bisearch_back(0, L - 1, m);
        if (j == -1) {
            chmax(ans, bitsm.query(0, L));
        } else {
            ll rest = m - bitcnt.query(j + 1, L);
            chmax(ans, rest * cp.unzip(j) + bitsm.query(j + 1, L));
        }
    }
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
