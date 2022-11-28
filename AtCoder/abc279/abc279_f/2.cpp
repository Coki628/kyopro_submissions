/*
参考：https://twitter.com/SSRS_cp/status/1596499038907813890
　　　https://atcoder.jp/contests/abc279/submissions/36806843
・マージテク、番号の対応
・SSRSさんがほぼ同じ方針で通してくれていたので、参考にした。
・最後に提出したやつは結構惜しかった。
　まあでもちゃんと作れなかったことに変わりはない…。
　逆引きみたいな配列を適切に作ってちゃんと操作する必要がある。
　SAのsaとrsaみたいな関係。いつもこれこんがらがるから、
　ちゃんと頭の中で整理していきたい。
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

    // ids[i] = 位置iにある箱の番号
    // rev[i] = 番号iの箱がある位置
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
                mp[a] = ids[x];
            }
            adj[y].clear();
        } elif (op == 2) {
            ll x;
            cin >> x;
            x--;

            adj[x].eb(k);
            mp.eb(ids[x]);
            k++;
        } elif (op == 3) {
            ll a;
            cin >> a;
            a--;

            assert(a < mp.size());
            print(rev[mp[a]] + 1);
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
