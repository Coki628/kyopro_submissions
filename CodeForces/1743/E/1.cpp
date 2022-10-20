/*
参考：https://codeforces.com/blog/entry/108153
・この前のupsolveした。
・状態の持ち方を工夫するDP
・いやー、難しいDPだね。でも解説ちゃんと読んだら理解できた。
　今回は1時間くらいあった訳だから、こういう時にこのレベルを通せるようになるといいよね。
・ようは2つのビームが同時発射した瞬間で状態を持ってDPするといい。
　これだと2つ別々に持たなくていい。
　同時じゃない瞬間については、片方が打った瞬間を全部見る。
　ソース内にも細かくコメント入れといたので、そちらも参照。
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
    ll P[2], T[2];
    rep(i, 2) {
        cin >> P[i] >> T[i];
    }
    ll H, S;
    cin >> H >> S;

    // dp[h] := ダメージをh与えて同時打ち直後の状態となる最小所要時間
    vector<ll> dp(H+1, INF);
    dp[0] = 0;
    ll ans = INF;
    rep(h, H+1) {
        if (dp[h] == INF) continue;
        // p[a]をi回打ってから次の同時打ち
        rep(i, 1, H+1) {
            rep(a, 2) {
                ll b = 1 - a;
                // T[a]をi回打つ所要時間
                ll xa = i * T[a];
                // T[a]をi回打った時点までにT[b]も打てるだけ打つ
                ll j = xa / T[b];
                // xa以下で最大のT[b]の倍数
                ll xb = j * T[b];
                assert(xb <= xa);
                ll nxh = h + (P[a]-S)*i + (P[b]-S)*j;
                // ダメージがH以上に達していれば、これも答えに使う
                if (nxh >= H) {
                    chmin(ans, dp[h] + xa);
                }

                // T[a]をi回打った後、T[b]も整うまで待って同時打ち
                j = ceil(xa, T[b]);
                // xa以上で最小のT[b]の倍数
                xb = j * T[b];
                assert(xb >= xa);
                nxh = h + (P[a]+P[b]-S) + (P[a]-S)*(i-1) + (P[b]-S)*(j-1);
                // 次の同時打ちが終わった時点のダメージ量に遷移
                chmin(dp[min(nxh, H)], dp[h] + xb);
            }
        }
    }
    chmin(ans, dp[H]);
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
