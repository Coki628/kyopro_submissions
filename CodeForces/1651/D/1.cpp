/*
・終了後5分くらいでAC。悔しい。
・グリッドBFS応用
・座標点の四方を予め全部見て、空白だった場所があればその座標を全部始点にして、多点スタートBFS。
　未訪問に着いたら答えとしてその空白だった場所の座標を入れる。
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
    ll N;
    cin >> N;
    set<pll> has;
    vector<ll> X, Y;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        has.insert({x, y});
        X.eb(x), Y.eb(y);
    }

    queue<pll> que;
    map<pll, pll> memo;
    rep(i, N) {
        ll x = X[i], y = Y[i];
        for (auto [dx, dy] : dir4) {
            ll nx = x+dx;
            ll ny = y+dy;
            if (not has.count({nx, ny})) {
                que.push({x, y});
                memo[{x, y}] = {nx, ny};
            }
        }
    }
    while (que.size()) {
        auto [cx, cy] = que.front(); que.pop();
        for (auto [dx, dy] : dir4) {
            ll nx = cx+dx;
            ll ny = cy+dy;
            if (has.count({nx, ny}) and not memo.count({nx, ny})) {
                memo[{nx, ny}] = memo[{cx, cy}];
                que.push({nx, ny});
            }
        }
    }
    rep(i, N) {
        ll x = X[i], y = Y[i];
        auto res = memo[{x, y}];
        print(res);
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
