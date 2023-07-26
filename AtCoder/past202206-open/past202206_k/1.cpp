/*
・自力AC！やったね。
・部分列DP、包除(というかただのベン図)
・以前はLCSのDPみたいのをこじらせて終わったぽいが、今回は正解の方針を引けた。
　「いずれか」の条件が何とも直接数えづらくて余事象とか包除に行きたくなる。
　余事象の「S,Tどちらの部分列でもない」が数えられればそれも良さそうだが、
　部分列でないものを直接数えるのもまたぱっと方針が見えない。
　ベン図を書くと「Sの部分列+Tの部分列-S,T両方の部分列」でいけそう。
　前半はごく普通に部分列DP。問題は後半だけど、制約が2乗OKだし、
　両方の文字列の添字を持って同じことすればいいように思える。
　実際にやってみると、これでちゃんと通る。
・実装では、普通に作ったら1回TLEした。1000^2*文字数*にぶたんのlogなので、
　結構きついみたい。このDPは使わない場所がかなり多いと思うので、
　配る前に枝刈りcontinue入れたら無事AC。
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
    string S, T;
    cin >> S >> T;
    int N = S.size();
    int M = T.size();

    const ll L = 26;
    vector<Accumulate<int>> acc1(L, {N}), acc2(L, {M});
    rep(i, N) {
        acc1[S[i] - 'a'].set(i, 1);
    }
    rep(i, M) {
        acc2[T[i] - 'a'].set(i, 1);
    }
    rep(i, L) {
        acc1[i].build();
        acc2[i].build();
    }
    vector<mint> dp1(N + 1), dp2(M + 1);
    dp1[0] = 1;
    rep(i, N) {
        rep(c, L) {
            ll j = acc1[c].bisearch_fore(i, N - 1, 1);
            if (j != -1) {
                dp1[j + 1] += dp1[i];
            }
        }
    }
    mint ans1 = sum(dp1) - 1;
    dp2[0] = 1;
    rep(i, M) {
        rep(c, L) {
            ll j = acc2[c].bisearch_fore(i, M - 1, 1);
            if (j != -1) {
                dp2[j + 1] += dp2[i];
            }
        }
    }
    mint ans2 = sum(dp2) - 1;
    auto dp3 = listnd(N + 1, M + 1, (mint)0);
    dp3[0][0] = 1;
    rep(i, N) {
        rep(j, M) {
            if (dp3[i][j] == 0) continue;
            rep(c, L) {
                ll ii = acc1[c].bisearch_fore(i, N - 1, 1);
                ll jj = acc2[c].bisearch_fore(j, M - 1, 1);
                if (ii != -1 and jj != -1) {
                    dp3[ii + 1][jj + 1] += dp3[i][j];
                }
            }
        }
    }
    mint ans3 = 0;
    rep(i, N + 1) {
        rep(j, M + 1) {
            ans3 += dp3[i][j];
        }
    }
    ans3--;
    mint ans = ans1 + ans2 - ans3;
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
