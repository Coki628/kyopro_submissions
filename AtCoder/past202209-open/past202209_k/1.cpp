/*
・自力AC！
・オフラインダイコネ
・制約で辺追加クエリが10回しかないとのことなので、
　逆操作でこれ削除にするっぽいよなぁとは思いつつ、
　細かいこと考えるのが面倒でオフラインダイコネで殴った。
　割と使い方慣れてなくていつもゴチャるから、まあ練習にはなった。
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

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pii> edges;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges.eb(a, b);
    }
    ll Q;
    cin >> Q;
    vector<array<ll, 3>> qs;
    rep(i, Q) {
        ll op, x, y;
        cin >> op >> x >> y;
        x--, y--;
        qs.pb({op, x, y});
    }

    OfflineDynamicConnectivity odc(N, Q);
    ll t = 0;
    for (auto [a, b] : edges) {
        odc.insert(t, a, b);
    }
    vector<ll> mp(Q, -1);
    ll i = 0;
    for (auto [op, x, y] : qs) {
        if (op == 1) {
            odc.insert(t, x, y);
        } else if (op == 2) {
            odc.erase(t, x, y);
        } else {
            mp[t] = i;
            i++;
        }
        t++;
    }
    vector<string> ans(i);
    odc.run([&](ll t) {
        if (mp[t] != -1) {
            auto [_, x, y] = qs[t];
            ans[mp[t]] = odc.uf.same(x, y) ? "Yes" : "No";
        }
    });
    print(ans, '\n');
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
