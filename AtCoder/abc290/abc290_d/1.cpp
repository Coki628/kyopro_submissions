/*
参考：https://twitter.com/kyopro_friends/status/1627304015070662659
・むずい。てか苦手なんだろうな、これ系。
・数学、周期
・公式解説はとても難しいのでフレンズさんのお気持ちを見る。
　とりあえずこの手のやつでg=gcd(N,D)個のサイクルになって、
　gの倍数を全部踏むってのは、多分前にも見たことある。
　で、このサイクルは踏む順番はバラバラだけど、
　どうやら最後には必ず最初に踏んだ位置に戻るらしい。
　なので題意の通り踏んだ位置が来たら1つ先にずれると、
　そのずれた位置でそのまま同じことを繰り返す感じになる。
　そこまで分かると、サイクル何周目の移動何回目なのかを割り算で求めて、
　色々整理すれば答えが出る。(ソース内コメントも参照)
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
    ll N, D, K;
    cin >> N >> D >> K;

    // サイクルの数
    ll cyclecnt = gcd(N, D);
    // サイクル長
    ll cyclelen = N / cyclecnt;
    K--;
    auto [d, m] = divmod(K, cyclelen);
    // サイクル何周目(0-indexed)か
    ll cyclecur = d % cyclecnt;
    // cyclecur周目の周回でm回移動した場所が答え
    ll ans = (cyclecur + m * D) % N;
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
