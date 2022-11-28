/*
・自力ならず。。
・マージテク、番号の対応
・全部移動をマージテク使えば間に合うはず。がしかし番号が変わる中、元indexを適切に追えず時間切れ。
　その後も色々試行錯誤したけど、結局これでサンプルは合ったけどWAでギブアップ。。
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
    ll N, Q;
    cin >> N >> Q;

    vector<ll> ids(N), rev(N), mp(N);
    vvl adj(N);
    ll k = N;
    rep(i, N) {
        ids[i] = i;
        rev[ids[i]] = i;
        adj[i].eb(i);
        mp[i] = i;
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, y;
            cin >> x >> y;
            x--; y--;

            if (adj[x].size() < adj[y].size()) {
                swap(adj[x], adj[y]);
                swap(rev[ids[x]], rev[ids[y]]);
                swap(ids[x], ids[y]);
            }
            for (auto a : adj[y]) {
                adj[x].eb(a);
                mp[a] = x;
            }
            adj[y].clear();
        } elif (op == 2) {
            ll x;
            cin >> x;
            x--;

            adj[x].eb(k);
            mp.eb(x);
            k++;
        } elif (op == 3) {
            ll x;
            cin >> x;
            x--;

            assert(x < mp.size());
            print(rev[mp[x]]+1);
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
