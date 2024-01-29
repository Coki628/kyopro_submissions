/*
・自力AC！今回Dがきつかったけど、これも結構Cにしてはしんどく思えた。
・片方決めて全探索
・よく見るとNが10と小さい。max(A[i])も10^6なので全部見れる大きさ。
　料理Aを何個作るか決め打てば、料理Bに使える材料が定まるので、これで全探索。
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
    vector<ll> Q(N), A(N), B(N);
    cin >> Q >> A >> B;

    ll M = 1000000;
    ll ans = 0;
    rep(acnt, M + 1) {
        auto bk = Q;
        ll cnt = INF;
        bool ok = true;
        rep(i, N) {
            ll need = A[i] * acnt;
            if (need > Q[i]) {
                ok = false;
                break;
            }
            Q[i] -= need;
        }
        if (not ok) {
            Q = bk;
            continue;
        }
        ll bcnt = INF;
        rep(i, N) {
            if (B[i] == 0) continue;
            ll cnt = Q[i] / B[i];
            chmin(bcnt, cnt);
        }
        chmax(ans, acnt + bcnt);
        Q = bk;
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
