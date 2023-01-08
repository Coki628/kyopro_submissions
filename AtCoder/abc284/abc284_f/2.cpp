/*
・自力AC！
・ローリングハッシュ
・ロリハのライブラリにハッシュのマージを搭載してあるので、
　Tと逆Tで準備しておいて丁寧に切り貼りすればN箇所高速に見れる。
・終了後思ったけど、ハッシュのマージ今回は要らないよね。
　それぞれの対応する場所の部分ハッシュ取ればいいだけじゃん、ってことで直した。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    string T;
    cin >> T;

    RollingHash rh;
    auto table = rh.build(T);
    auto rev_table = rh.build(reversed(T));
    rep(i, N + 1) {
        auto lhash = rh.query(rev_table, N - i, N);
        auto rhash = rh.query(rev_table, N, N * 2 - i);
        auto mhash = rh.query(table, i, i + N);
        if (
            lhash == rh.query(table, 0, i) and
            mhash == rh.query(table, i, i + N) and
            rhash == rh.query(table, i + N, N * 2)
        ) {
            string S = reversed(T.substr(i, N));
            print(S);
            print(i);
            return;
        }
    }
    print(-1);
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
