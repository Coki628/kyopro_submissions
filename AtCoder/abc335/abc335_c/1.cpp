/*
・きっちり自力AC。
・頭の位置を都度配列に追加してシミュ。
　vectorの末尾追加でやったけど、dequeの先頭追加にすればより直感的で手早く解けたかもしれない。
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
    ll N, Q;
    cin >> N >> Q;

    map<char, pll> mp = {{'R', {1, 0}}, {'L', {-1, 0}}, {'U', {0, 1}}, {'D', {0, -1}}};
    vector<pll> vec;
    rep(i, N, 0, -1) {
        vec.eb(i, 0);
    }
    ll offset = 0;
    ll cx = 1, cy = 0;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            char c;
            cin >> c;
            auto [dx, dy] = mp[c];
            cx += dx, cy += dy;
            vec.eb(cx, cy);
            offset++;
        } else {
            ll p;
            cin >> p;
            ll q = N - p + offset;
            print(vec[q]);
        }
    }
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
