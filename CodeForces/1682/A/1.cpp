/*
・自力AC！
・回文判定、ロリハ
・絶対うまい方法があるだろうと思いながら、ロリハ使ってハッシュ更新しながら回文判定頑張った。
　ロリハの1点更新久しぶりに使ったけど、ちゃんと動いてよかった。
　テーブルじゃなくて、ハッシュを更新するので、回文判定がそのまま使えなくて困ったけど、
　今回は区間の変化はなかったので、同じハッシュそのまま使いまわして何とかなった。
・なんか、中央の同じ文字の個数でいいらしいよ。
　言われたらそんな気もするけど、気付けないよね～…。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    auto rev = reversed(S);
    RollingHash rh;
    auto hasha = rh.get_hash(S.substr(1), 0, N-1);
    auto hashrev = rh.get_hash(rev.substr(0, N-1), 0, N-1);
    ll ans = 0;
    if (hasha == hashrev) ans++;
    rep(i, N-1) {
        hasha = rh.update(hasha, N-1, i, S[i+1], S[i]);
        hashrev = rh.update(hashrev, N-1, N-2-i, S[i+1], S[i]);
        if (hasha == hashrev) ans++;
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
