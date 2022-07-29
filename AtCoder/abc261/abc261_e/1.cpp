/*
参考：https://twitter.com/US_kyopro/status/1550838245734264832
・自力ならず…。悔しい。
・ビット毎に見て後ろから確定させてこうとしたら、
　xorの時、そこより手前で使った個数がうまく数えられなかった。
　絶対これハズレ方針だって思ったけど、打開策を見出せなかった。
・内容的に、ビット毎に見るのが絶対いいとは思ったけど、DPは見えなかったなぁ…。
　dp[k][i][j] := kビット目を数列Aのi番目まで見た時で、初期値がj=0/1だった時の値(ビットの0/1)
　とすると、ある初期状態のビットがi番目まで進んだ時どうなるかがO(1)で分かるようになるので、
　この値に従ってi回進めて行けばビット毎に答えが求まる。
・ちなみに3次元vectorを(30,20万,2)でやると0.50秒かかってメモリも345MBもかかったんだけど、
　これを(30,2,20万)の順にしたら0.16秒でメモリも56MBで済んだ。
　C++だと配列の次元による大きさでそんなに影響出ないと思ってたけど、出るな。
　大きいサイズの部分をなるべく深い次元に置いた方が良さそうだ。
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
    ll N, x;
    cin >> N >> x;
    vector<pll> qs;
    rep(i, N) {
        ll op, a;
        cin >> op >> a;
        qs.eb(op, a);
    }

    ll M = 30;
    auto dp = list3d(M, 2, N+1, 0);
    rep(k, M) {
        dp[k][0][0] = 0;
        dp[k][1][0] = 1;
        rep(s, 2) {
            rep(i, N) {
                auto [op, a] = qs[i];
                if (op == 1) {
                    dp[k][s][i+1] = dp[k][s][i] & (a>>k & 1);
                } elif (op == 2) {
                    dp[k][s][i+1] = dp[k][s][i] | (a>>k & 1);
                } else {
                    dp[k][s][i+1] = dp[k][s][i] ^ (a>>k & 1);
                }
            }
        }
    }

    vector<ll> ans(N);
    rep(k, M) {
        int cur = x>>k & 1;
        rep(i, N) {
            int nxt = dp[k][cur][i+1];
            ans[i] |= nxt<<k;
            cur = nxt;
        }
    }
    print(ans, '\n');
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
