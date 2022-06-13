/*
・なんとか自力AC！
・十分条件が全然見えなくて、仕方なく必要条件を思いつく限り並べてった。
　・種類と出現数が同じ(これは多分自明)
　・bは結構色々動けそう(なのでひとまずスルー)
　・aは左に行けない
　・cは右に行けない
　・a,cはお互いに跨いだ移動はできない(のでbを全部除いたS,Tは同値)
　これで通った。。
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
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    auto C1 = Counter(S);
    auto C2 = Counter(T);
    if (C1 != C2) {
        NO();
        return;
    }
    ll cnta1 = 0, cnta2 = 0, cntc1 = 0, cntc2 = 0;
    rep(i, N) {
        if (S[i] == 'a') cnta1++;
        if (T[i] == 'a') cnta2++;
        if (cnta1 < cnta2) {
            NO();
            return;
        }
    }
    rep(i, N-1, -1, -1) {
        if (S[i] == 'c') cntc1++;
        if (T[i] == 'c') cntc2++;
        if (cntc1 < cntc2) {
            NO();
            return;
        }
    }
    string S2, T2;
    rep(i, N) {
        if (S[i] != 'b') {
            S2 += S[i];
        }
        if (T[i] != 'b') {
            T2 += T[i];
        }
    }
    if (S2 != T2) {
        NO();
        return;
    }
    YES();
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
