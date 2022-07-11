/*
・自力TLE…。
・クエリ5回だけなら、結構愚直にやっていいだろ、っていけそうかと思ったらTLE…。
　DFSの中でsetを持ち回る感じ。でも今ちゃんと考えたら、
　クエリに出てくる値の数が計20万個だから、値全部から出発してチェックしちゃうと、
　頂点数の20万と2乗しちゃって確かにダメっぽいわ…。
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
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll m;
        cin >> m;
        auto A = LIST(m);
        rep(i, m) A[i]--;
        set<ll> se(ALL(A));
        auto dfs = [&](auto&& f, ll u, ll prv, set<ll>& cur) {
            if (cur.empty()) {
                return true;
            }
            for (auto v : nodes[u]) {
                if (v == prv) continue;
                bool removed = false;
                if (cur.count(v)) {
                    cur.erase(v);
                    removed = true;
                }
                if (f(f, v, u, cur)) {
                    if (removed) cur.insert(v);
                    return true;
                }
                if (removed) {
                    cur.insert(v);
                }
            }
            return false;
        };
        bool ok = false;
        rep(i, m) {
            se.erase(A[i]);
            if (dfs(dfs, A[i], -1, se)) {
                ok = true;
                break;
            }
            se.insert(A[i]);
        }
        if (ok) YES();
        else NO();
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
