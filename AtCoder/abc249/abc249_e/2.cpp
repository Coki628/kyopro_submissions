/*
参考：https://twitter.com/cpbm_p/status/1517864674112417792
・自力ならず。。
・貰うDP高速化、累積和
・本番中は先に10以降で増える文字数が変わることを考慮しておらず、
　それに気付くのがだいぶ遅くなってしまったのが良くなかった。
　気付いて、正解の方針に近い愚直DPを書いている途中で時間切れ。
　十分時間があったとして、log 10でまとめて累積和する所を自分で導けたかは分からない。
・dp[i][j] := 変換後をi文字、変換前をj文字とする通り数
　みたいなDPにする。これは遷移が1~9,10~99,..とまとめられるので、やる。
　毎回、前回の文字以外全て使えるので、最初だけ*26、最初以外は*25する。
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;

void solve() {
    ll N, P;
    cin >> N >> P;
    mint::set_mod(P);

    auto dp = list2d(N, N+1, (mint)0);
    dp[0][0] = 1;
    rep(i, N-1) {
        Accumulate<mint> acc(dp[i]);
        rep(j, 1, N+1) {
            rep(add, 2, 6) {
                if (i+add >= N) break;
                ll r = j - pow(10, add-2) + 1;
                ll l = j - pow(10, add-1) + 1;
                chmax(r, 0LL);
                chmax(l, 0LL);
                dp[i+add][j] += acc.query(l, r) * (i == 0 ? 26 : 25);
            }
        }
    }
    mint ans = 0;
    rep(i, 1, N) {
        ans += dp[i][N];
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
