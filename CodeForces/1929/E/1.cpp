/*
参考：https://twitter.com/KaikeyPro/status/1758169156732797070
　　　https://twitter.com/eco4kb/status/1758168177492836470
・TL見て、好きそうな問題だったから通しといた。
・Auxiliary Tree、木のパス取得、集合被覆問題、bitDP
・うーん、Dよりこっちのが自力行けただろうか。縮約は最近やってたからさておき、
　「パスをビットにして各辺にどのパスで使われたか持たせる」
　あたりが適切にイメージできたかちょっと分からない。
　でもそこまで行ければ、bitDPしたくなるのは制約からも分かるし、
　最後まで首尾よくいけたかもしれない。知らんけど。
　とりあえず方針知ってから解き始めて通すまでは結構詰まらず行けたよ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "graph/AuxiliaryTree.hpp"

void solve(int testcase) {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    AuxiliaryTree aux(nodes);
    ll K;
    cin >> K;
    vector<pii> paths;
    vector<int> vec;
    rep(i, K) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        paths.eb(u, v);
        vec.eb(u);
        vec.eb(v);
    }
    UNIQUE(vec);
    aux.build(vec);
    map<pii, ll> mp;
    rep(i, K) {
        auto [a, b] = paths[i];
        auto dfs = [&](auto &&f, ll u, ll prv, ll g) -> bool {
            if (u == g) {
                return true;
            }
            for (auto v : aux[u]) {
                if (v == prv) continue;
                if (f(f, v, u, g)) {
                    // 辺(u,v)はパス(a,b)に使われる
                    mp[minmax((int)u, v)] |= 1LL << i;
                    return true;
                }
            }
            return false;
        };
        dfs(dfs, a, -1, b);
    }

    ll L = mp.size();
    vector<ll> B;
    for (auto [k, val] : mp) {
        B.eb(val);
    }
    auto dp = listnd(2, 1LL << K, INF);
    dp[0][0] = 0;
    rep(i, L) {
        rep(bit, 1LL << K) {
            chmin(dp[(i + 1) % 2][bit], dp[i % 2][bit]);
            chmin(dp[(i + 1) % 2][bit | B[i]], dp[i % 2][bit] + 1);
        }
        dp[i % 2].assign(1LL << K, INF);
    }
    ll ans = dp[L % 2][(1LL << K) - 1];
    print(ans);
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
    rep(t, T) solve(t);

    return 0;
}
