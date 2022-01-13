/*
・cf1360_G
・自力ならず。
・グリッド、構築
・確実に言えることから言うと、まず1行目にはa個配置しないといかない。
　2行目も同様だ。偏りがあるとダメそうな気持ちにはなるので、
　列側については1ずつ順に進めてW周期で回すことにする。
　っていう考えになればよかったんだけど、列側を同じ所に固めちゃってたんだよね…。
　各行にa個ずつ置いていくのは良かったんだけど。
・で、上記の組み方で列側も合えばOKだし、ダメなら無理。
　a,bがグリッドより大きい場合は絶対無理なので場合分け。
・なんかagc056_aを類題として思い出して着想した人が多かったぽい。
　発想ゲーだったからupsolveしないで放置してたやつだね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll H, W, a, b;
    cin >> H >> W >> a >> b;

    if (H < b or W < a) {
        NO();
        return;
    }

    vector<string> ans(H, string(W, '0'));
    ll j = 0;
    rep(i, H) {
        rep(k, a) {
            ans[i][(j+k)%W] = '1';
        }
        j += a;
    }
    rep(j, W) {
        ll cnt = 0;
        rep(i, H) {
            if (ans[i][j] == '1') {
                cnt++;
            }
        }
        if (cnt != b) {
            NO();
            return;
        }
    }
    YES();
    rep(i, H) {
        print(ans[i]);
    }
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
