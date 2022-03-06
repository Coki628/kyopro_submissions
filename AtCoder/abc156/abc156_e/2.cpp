/*
・dojo set_e_4_3
・自力AC！
・nCr系数え上げ
・苦手な部類をきっちり通せたのは嬉しい。
・色々ガチャガチャすると、0人の部屋が多いやつは操作を多くしないと作りづらいのが分かる。
　もうちょい詰めると、操作回数制限K = 0人の部屋を作れる最大数 だとなる。
　これで0人部屋の数を固定してkとすると、
　N人をN-k箇所にそれぞれ1人以上割り振る * N箇所からk箇所の0部屋をどこにするか
　がこのkでの答えとなる。前者は写像の6相なのでN-1箇所にN-k-1箇所の仕切りを入れるとできて、
　後者は素直にN箇所からk個選ぶなので、どちらもnCrで処理できる。
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
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;

    ModTools<mint> mt(N*2);
    mint ans = 0;
    rep(k, min(K+1, N)) {
        ans += mt.nCr(N, k)*mt.nCr(N-1, N-k-1);
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
