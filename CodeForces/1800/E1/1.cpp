/*
・自力AC！
・スワップなんだけど、ある程度近い所ができない。
　これは最終的に、中央付近だけ動かせないみたいになる(だったはず)。
　ので、その部分に関しては一致してるか判定して、
　それ以外は自由に移動できるとして個数だけ合ってればOKなのでソートして比較とした。
・なんかこれもtitiaさんはUFで解いてたらしい。全然見えなかった…。
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
    ll N, K;
    cin >> N >> K;
    string S, T;
    cin >> S >> T;

    ll r = K;
    ll l = max(N - K, 0LL);
    if (l < r) {
        if (S.substr(l, r - l) != T.substr(l, r - l)) {
            NO();
            return;
        }
    }
    sort(ALL(S));
    sort(ALL(T));
    YESNO(S == T);
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
