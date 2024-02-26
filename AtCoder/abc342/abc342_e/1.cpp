/*
・終了後自力AC。
・逆操作、ダイクストラ、にぶたん
・変数たくさんで混乱するけど、ようは題意は、
　「駅Nへ行くための各駅からの終電を求める」といったもの。
　駅Nから遡っていく。各駅にいられる最大時刻を大きい方から求めていく。
　各駅でどの電車に乗れるかはにぶたんで求まる。
・んー、これは落ち着いて見れれば本番ACもできたんじゃないかなぁ…。
　Dが通らなくて精神を乱され過ぎた。もったいない。メンタルが弱い…。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N);
    vector<array<ll, 6>> info;
    rep(i, M) {
        ll l, d, k, c, a, b;
        cin >> l >> d >> k >> c >> a >> b;
        a--, b--;
        nodes[b].eb(a, i);
        info.pb({l, d, k, c, a, b});
    }

    auto calc = [&](ll cur, ll i) {
        auto [l, d, k, c, a, b] = info[i];
        // 時刻cur以下で最大の(一番遅い)電車を見つける
        ll res = bisearch_max(-1, k, [&](ll x) {
            return l + d * x + c <= cur;
        });
        if (res != -1) {
            return l + d * res;
        } else {
            // 始発でも無理
            return -INF;
        }
    };
    auto dijkstra = [&](const vvpil &nodes, const vector<int> &src) {
        int N = nodes.size();
        // res[i] := 駅N-1に到着するために駅iにいられる最大時刻
        vector<ll> res(N, -INF);
        priority_queue<pli> que;
        for (auto s : src) {
            res[s] = LONG_LONG_MAX;
            que.push({LONG_LONG_MAX, s});
        }
        while (que.size()) {
            auto [cur, u] = que.top();
            que.pop();
            if (res[u] < cur) continue;
            for (auto [v, i] : nodes[u]) {
                ll nxt = calc(cur, i);
                if (chmax(res[v], nxt)) {
                    que.push({nxt, v});
                }
            }
        }
        return res;
    };
    auto res = dijkstra(nodes, {(int)N - 1});
    res.pop_back();
    for (auto d : res) {
        if (d <= -INF) {
            print("Unreachable");
        } else {
            print(d);
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
