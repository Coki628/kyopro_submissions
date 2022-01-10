/*
参考：https://twitter.com/kyopro_dekomori/status/1479811038405357569
・自力ならず。。これは悔しい。
・数え上げDP、種類数のDP
・種類数のDPは部分文字列で次の出現位置に遷移させるやつしか思い出せなかった。
　この方針は初めてやったんじゃなかろうか。
・dp[i][j] := i種類目の文字まで見て、文字数がjの時の通り数
　っていうDPにする。確かにこれだと次の遷移は毎回新しい文字が入るので、
　種類数の数え上げでも被りなく数えられるし、遷移に二項係数絡めれば、
　任意順序の通り数にもできてる。すげー、ってなった。
　いくらやっても自分の知らない知見が無限に出てくるから楽しい。
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

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    const int M = 26;
    vector<ll> C(M);
    rep(i, N) {
        C[S[i]-'a']++;
    }
    ModTools<mint> mt(N);
    auto dp = list2d<mint>(M+1, N+1, 0);
    dp[0][0] = 1;
    rep(i, M) {
        rep(j, N+1) {
            rep(k, j, N+1) {
                ll use = k-j;
                if (use > C[i]) break;
                dp[i+1][k] += dp[i][j]*mt.nCr(k, use);
            }
        }
    }
    mint ans = sum(dp[M])-1;
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
