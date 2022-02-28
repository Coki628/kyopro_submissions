/*
・自力AC！
・ちょっと遷移が特殊？なダブリング。前に使ったことなかったら解けてない。(AGC036B)
　なんか遷移先はmod Nするけど値はそのまま持つよみたいな状況はこうやる、って感じ。
・でもやっぱりなんか周期でも解けたぽい。
　だからこんなに解かれてたのか。周期ほんと苦手なんだよね。。
・終了後SSRSさんツイートによると、なんか普通に行き先と和を持つダブリングでも解けたぽい。
　だからこんなに解かれてたのか。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

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

vvl doubling(int MXLOG, const vector<ll> &A) {
    int N = A.size();
    auto nxt = list2d(MXLOG, N, -1LL);
    rep(i, N) {
        nxt[0][i] = A[i];
    }
    rep(k, 1, MXLOG) {
        rep(i, N) {
            if (nxt[k-1][i] != -1) {
                nxt[k][i] = nxt[k-1][i] + nxt[k-1][(i+nxt[k-1][i])%N];
            }
        }
    }
    return nxt;
}

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    ll MXLOG = 60;
    auto nxt = doubling(MXLOG, A);
    ll cur = 0, sm = 0;
    rep(k, MXLOG-1, -1, -1) {
        if (K>>k & 1) {
            sm += nxt[k][cur];
            cur = sm % N;
        }
    }
    print(sm);
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
