/*
・きっちり自力AC！
・トポロジカルソート応用
・typical90_071をほぼ持ってきてちょっといじったらOKだった。
　ぱっとすぐ思い出せたのは良かったかな。
・後でTL見たら、JOIの最悪の記者がほぼ同じ感じだったらしい。
　なんかメモ化再帰した記憶しかないんだけど、そんなトポソっぽいことしたっけな。
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
    ll N, M;
    cin >> N >> M;
    vector<pll> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.eb(u, v);
    }

    vector<int> incnts(N);
    vvi outnodes(N);
    rep(i, M) {
        incnts[edges[i].second]++;
        outnodes[edges[i].first].pb(edges[i].second);
    }
    vector<int> S;
    rep(i, N) {
        if (incnts[i] == 0) {
            S.eb(i);
        }
    }

    vvi res;
    vector<int> L;
    auto rec = [&](auto &&f) -> bool {
        // 閉路があって正しくソート出来なかった場合
        if (S.empty() and L.size() < N) {
            return true;
        }
        // トポソ完了
        if (S.empty() and L.size() == N) {
            res.eb(L);
            if (res.size() >= 2) {
                return true;
            }
            return false;
        }
        // 今候補となる頂点を全部見る
        int n = S.size();
        rep(i, n) {
            int u = S[i];
            S.erase(find(ALL(S), u));
            L.eb(u);
            for (auto node : outnodes[L.back()]) {
                incnts[node]--;
                if (incnts[node] == 0) {
                    S.eb(node);
                }
            }
            if (f(f)) {
                return true;
            }
            // 状態を戻す
            for (auto node : outnodes[L.back()]) {
                if (incnts[node] == 0) {
                    S.pop_back();
                }
                incnts[node]++;
            }
            L.pop_back();
            S.insert(S.begin() + i, u);
        }
        return false;
    };
    rec(rec);
    if (res.size() >= 2) {
        No();
    } else {
        Yes();
        vector<ll> ans(N);
        rep(i, N) {
            ans[res[0][i]] = i;
        }
        ans++;
        print(ans);
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
