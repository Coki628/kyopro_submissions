/*
参考：https://www.youtube.com/watch?v=xEQwyKJIfuE
・むずい。でもこれは慣れない概念だったししょうがないかな。
・式変形、区切るDP高速化、スタックで遷移高速化
・前提として、式変形を適切にやってDPができる形に持っていく必要がある。
　今回は内側の計算が加算じゃなくて乗算なので、シグマ入れ替えっぽくできないなぁとか思ったんだけど、
　できたね。。結局、操作列を1つ1つ求めて足し合わせる所から、
　ある区切り位置を決めてそこまでをまず全部求めて、次の位置に進むみたいな感じだから、
　縦横入れ替えというか、主客転倒的なアプローチであることに変わりはない。で、以下みたいな式になる。
　dp[i] = Σ(dp[j]*(max(j+1..i)-min(j+1..i))
　これを、さらにもう一段階、maxとminを分ける。このままだと気付けなかったんだけど、
　ΣX*(A-B) => ΣX*A - ΣX*B みたいに大きい変数だと思うと見えやすいのかも。
・さて、この形になったら、区間maxとかを遷移高速化して求める。
　多分この手の[i-1,i),[i-2,i)..[0,i)みたいな区切るDPにありがちっぽい遷移に汎用的に使えそうなんだけど、
　スタックに情報をまとめて持てる。max/minが同じ区間のDPの値をまとめて持って、
　新しい値がmax/minを更新しに来たら古い部分をスタックから捨てて今回の所にマージする。
・なんとなくスライド最小値みを感じたんだけど、あれはdequeだしまたちょっと違うか。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<mint> dp(N+1);
    // { ある区間のDPの値の和, その区間が持つ現時点でのmax/min }
    vector<pair<mint, ll>> stmx, stmn;
    dp[0] = 1;
    mint mxval = 0, mnval = 0;
    rep(i, N) {
        mint mxsm = dp[i];
        while (stmx.size() and stmx.back().second <= A[i]) {
            mxsm += stmx.back().first;
            mxval -= stmx.back().first * stmx.back().second;
            stmx.pop_back();
        }
        stmx.eb(mxsm, A[i]);
        mxval += mxsm * A[i];
        mint mnsm = dp[i];
        while (stmn.size() and stmn.back().second >= A[i]) {
            mnsm += stmn.back().first;
            mnval -= stmn.back().first * stmn.back().second;
            stmn.pop_back();
        }
        stmn.eb(mnsm, A[i]);
        mnval += mnsm * A[i];
        dp[i+1] = mxval - mnval;
    }
    mint ans = dp[N];
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
