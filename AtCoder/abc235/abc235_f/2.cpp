/*
参考：https://atcoder.jp/contests/abc235/submissions/28518864
・自力ならず。これは悔しい。
・桁DP、bitDP、総和も数える桁DP
・制約からしてどう見ても桁DP。0~9の出現済状態を持てば、計算量きつめだけど何とかなりそう。
　で、とりあえず作って、それから通り数じゃなくて総和が求められていることに気付く。
　通り数と一緒に総和も持てばいけそうだけど、これのやり方が分からなかった。
　なんか、途中までしか通り数数えてないのに、最終的にその桁使う数分からなくない？って。
　結局、*10して今の桁分足すみたいな、見たことあるやつで良かった。
　何でこれでいいのかよくよく考えたけど、その先に通り数が増える分は、
　総和も同じ遷移をすればよしなに分裂して増えてくれるからOK、って感じだと思う。
・状態の持ち方はまあまあ面倒で、
　dp[i][j][k][l] := i桁見て、使った桁集合j、smallerフラグk=0/1、reading zero終わったかフラグl=0/1
　ってやった。なんかもっと省略できそう。
　今ぱっと思ったのは、reading zeroはビットが1つでも立ってるかで判定できそうだね。
・計算量は10000*1000*2*2*10=4億くらいでだいぶやばめ。
　よく通ったなって感じだけど、実際最初は1.93秒くらいだった。
　(遷移元 == 0) continue の枝刈り付けたら、0.82秒まで速くなった。
・reading zeroの添字なくしてみた。これだと0.68秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

const int L = 1LL<<10;
mint dp0[10007][L][2], dp1[10007][L][2];

void solve() {
    string S;
    cin >> S;
    ll N = S.size();
    ll M;
    cin >> M;

    auto C = LIST(M);
    dp0[0][0][0] = 1;
    rep(i, N) {
        ll a = toint(S[i]);
        rep(j, L) {
            rep(k, 2) {
                rep(d, 10) {
                    if (dp0[i][j][k] == 0) continue;
                    ll nxk = -1;
                    if (d < a or k == 1) {
                        nxk = 1;
                    } elif (d == a) {
                        nxk = k;
                    }
                    if (nxk == -1) continue;
                    if (d == 0 and j == 0) {
                        dp0[i+1][j][nxk] += dp0[i][j][k];
                        dp1[i+1][j][nxk] += dp1[i][j][k]*10+dp0[i][j][k]*d;
                    } else {
                        dp0[i+1][j|1LL<<d][nxk] += dp0[i][j][k];
                        dp1[i+1][j|1LL<<d][nxk] += dp1[i][j][k]*10+dp0[i][j][k]*d;
                    }
                }
            }
        }
    }

    mint ans = 0;
    rep(j, L) {
        bool ok = true;
        rep(i, M) {
            if (!(j>>C[i] & 1)) {
                ok = false;
                break;
            }
        }
        if (not ok) continue;
        rep(k, 2) {
            ans += dp1[N][j][k];
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
