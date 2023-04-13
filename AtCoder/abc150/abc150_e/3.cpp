/*
・結局自力ならず。
・実験エスパー
・主客転倒かと思って頑張って注目する所を決めて二項係数こねくり回したりしてたのに、
　全然そんなんじゃなかった。それぞれの要素が使われるDの重みを愚直試すと、
　2冪だし差分は一定だしで、重みが計算で出るようになる。後は足すだけ。。
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

// #include "common/debug_print.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> cost(N);
    cin >> cost;

    // sort(ALL(cost));
    // auto mat = listnd(N, N + 1, 0);
    // vector<ll> W(N);
    // rep(A, 1 << N) {
    //     rep(B, 1 << N) {
    //         if (A == B) continue;
    //         ll d = 0, c = 0;
    //         rep(i, N - 1, -1, -1) {
    //             ll a = A >> i & 1;
    //             ll b = B >> i & 1;
    //             if (a != b) {
    //                 d++;
    //                 c += cost[i] * d;
    //                 mat[i][d]++;
    //                 W[i] += d;
    //             }
    //         }
    //     }
    // }
    // debug(mat);
    // debug(W);
    // rep(i, N - 1) {
    //     print(W[i] - W[i + 1]);
    // }

    ModTools<mint> mt(N);
    vector<mint> W(N);
    sort(rbegin(cost), rend(cost));
    mint base = mint(2).pow(N * 2 - 1);
    mint add = mint(2).pow(N * 2 - 2);
    rep(i, N) {
        W[i] = base + add * i;
    }
    mint ans = 0;
    rep(i, N) {
        ans += W[i] * cost[i];
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
