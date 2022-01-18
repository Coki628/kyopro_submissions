/*
参考：https://img.atcoder.jp/data/arc/055/editorial.pdf
・arc055_c
・ローリングハッシュ、LCP
・切る位置を考える。ABC|ACで切ると、それぞれ接頭辞と接尾辞が一致させたい場所になるので、
　これをうまく使う。基本的には両方LCP取って、重なった分は余分に作れる。
　けど空文字列がダメなので結構ゴニョゴニョ場合分けが必要。(詳細はソース内コメント)
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

#include "../../../_lib/cpp/_src/string/RollingHash.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    auto revs = S;
    reverse(ALL(revs));
    RollingHash rh;
    auto table = rh.build(S);
    auto revtable = rh.build(revs);

    ll ans = 0;
    rep(i, 3, N-1) {
        ll revi = N-i;
        // |abc| <= |ac| はNG
        if (i <= revi) continue;
        ll ac = revi;
        ll a = rh.lcp(table, 0, i, table, i, N);
        ll c = rh.lcp(revtable, 0, revi, revtable, revi, N);
        // 左(abc)からbcの2文字分、右(ac)からcの1文字分は最低限必要
        chmin(a, min(i-2, revi-1));
        // 左(abc)からabの2文字分、右(ac)からaの1文字分は最低限必要
        chmin(c, min(i-2, revi-1));
        if (a == 0 or c == 0) continue;
        ans += max(a+c+1-ac, 0LL);
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
