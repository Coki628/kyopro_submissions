/*
・自力AC！
・決め打ちにぶたん、ダイクストラ
・制約が小さい。全頂点から探索やってどこか1つでもOKならOKってやる。
　ダイクストラ使ったけど、必要なのは辺が通れるかどうかと到達可否だけなので、BFSでもよかったね。。
・にぶたん境界で10^9*定数くらい必要だなー、って思ってMOD*10ってやってWA。
　あとでちゃんと見たら、intのまま10^10になってるね…。
　その後雑にINFにするとこれはこれで掛け算でオーバーフローしててWA。
　距離の最大値ちゃんと見積もってやっとAC…。
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
    vector<ll> X(N), Y(N), P(N);
    rep(i, N) {
        cin >> X[i] >> Y[i] >> P[i];
    }

    auto dist = [&](ll i, ll j) {
        return abs(X[i]-X[j]) + abs(Y[i]-Y[j]);
    };
    vvpll nodes(N);
    ll mxdist = 0;
    rep(i, N) {
        rep(j, N) {
            if (i == j) continue;
            nodes[i].eb(j, dist(i, j));
            chmax(mxdist, dist(i, j));
        }
    }

    ll res = bisearch_min(-1, mxdist+1, [&](ll s) {
        rep(src, N) {
            vector<ll> res(N, INF);
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
            res[src] = 0;
            que.push({0, src});
            while (que.size()) {
                auto [dist, u] = que.top(); que.pop();
                if (res[u] < dist) continue;
                for (auto [v, cost] : nodes[u]) {
                    if (P[u]*s < cost) continue;
                    if (chmin(res[v], dist+cost)) {
                        que.push({dist+cost, v});
                    }
                }
            }
            bool ok = true;
            rep(i, N) {
                if (res[i] >= INF) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return true;
            }
        }
        return false;
    });
    print(res);
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
