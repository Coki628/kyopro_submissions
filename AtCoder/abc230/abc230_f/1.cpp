/*
参考：https://www.youtube.com/watch?v=ZrSO7fB7nlA
・ABC残埋め
・自力ならず。
・部分列DP、区切るDP高速化、種類数のDP
・題意の操作は、数列を任意の位置で区切って区間和を作っていき、
　途中で重複がないようにするといったもの。
　区間和なので累積和列を取っておくと、この列では、区切りを1つ入れることが、
　使う値を1つ追加することと対応する。これは重複の出ないように文字を集める、
　部分文字列のDPと同じことを数列でやっている感じになる。
　(累積和の先頭と末尾は必ず区切るような形になるので、ここは必ず使うとする。)
　あと文字列の時と少し違うのが、文字種が26といった定数ではなく20万くらいあることだが、
　これは、各文字種で次回出現位置を管理して配るDPする方針ではなく、
　前回出現位置を管理して、その位置以降からまとめて遷移するようにすればいい。
　(ARC125_dでこのやり方を使ってたので、今回ほぼそれを流用した。)
・ちょっと追記。部分列DPという用語の割に区切って連続部分列を扱うので違和感があったんだけど、
　ここで扱う部分列は「使う区切り位置」の部分列と解釈できるはずなので、
　そう考えると数列として連続部分列であることとは別の話なので、
　ここは連続しない部分列の話で問題ない。(はず)
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

    auto acc = A;
    rep(i, N-1) {
        acc[i+1] += acc[i];
    }
    // prv[i] := i番目の要素と同じ値が直前に出現したindex+1
    vector<ll> prv(N-1);
    map<ll, ll> mp;
    rep(i, N-1) {
        if (mp.count(acc[i])) {
            prv[i] = mp[acc[i]];
        }
        mp[acc[i]] = i + 1;
    }

    // dp[i] := 最後にi番目を使った通り数
    BIT<mint> dp(N);
    dp.add(0, 1);
    rep(i, N-1) {
        // 直前にその値を使った位置以降から遷移
        // (前回区切った位置として[prv[i],i]を全部見る感じ)
        dp.update(i+1, dp.query(prv[i], i+1));
    }
    // 最後は絶対区切るので全体から遷移
    mint ans = dp.query(0, N);
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
