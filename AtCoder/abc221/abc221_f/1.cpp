/*
・自力AC！！やったね。結構時間かかったけどね…。
・木の中心、木の直径、DFS
・最初重心かと思ったけど違って、木の中心になる頂点が必要。
　求め方は、直径求めた後、外周を構成する2頂点間のパスで真ん中見つける。
　重心と同じ感じで、1つになるか2つになるかってなる。それによって場合分け。
・頂点2つのが簡単で、両側から各1個ずつしか選べないので、
　両側でそれぞれ外周になる頂点数えて掛け合わせればOK。
　頂点1つだと、その頂点から出る全ての辺について、その先の頂点で外周になるものを数える。
　で、この各部分木みたいのからそれぞれ1つ以下の頂点を選ぶ感じの通り数を出して、
　そこから空集合と頂点が1つだけ選ばれるものを引く。
・考察的には、これでだいたい想定解の方針とも一致してたしいい感じなんだけど、
　頂点2つだけで中心と外周がイコールみたいなケースのWAで結構詰まったのはタイムロスだったな…。
　1つだけWAになった時真っ先に疑ったんだけど、考慮できてると思ったんだよね。
　実際には実装でミスってた…。木の中心求める所で、到達した外周の頂点で中心かチェックしてなかった。
　(1つめのDFSの u == y の下)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "graph/bfs.hpp"

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

    // 木の直径を求める
    auto dist0 = bfs(nodes, {0});
    int x = max_element(ALL(dist0)) - dist0.begin();
    auto dist1 = bfs(nodes, {x});
    int y = max_element(ALL(dist1)) - dist1.begin();
    ll diam = *max_element(ALL(dist1));

    // 木の中心を求める
    vector<int> centers;
    ll cnt = 0;
    auto dfs = [&](auto&& f, ll u, ll prev) -> bool {
        if (u == y) {
            if (cnt == diam/2 or cnt == ceil(diam, 2LL)) {
                centers.eb(u);
            }
            return true;
        }
        for (ll v : nodes[u]) {
            if (v == prev) continue;
            if (f(f, v, u)) {
                cnt++;
                if (cnt == diam/2 or cnt == ceil(diam, 2LL)) {
                    centers.eb(u);
                }
                return true;
            }
        }
        return false;
    };
    dfs(dfs, x, -1);

    if (centers.size() == 1) {
        // 各部分木の最遠点とその個数を求めるDFS
        auto dfs = [&](auto&& f, ll u, ll prv) -> pll {
            ll mxcnt = 1, mx = 0;
            for (auto v : nodes[u]) {
                if (v == prv) continue;
                pll res = f(f, v, u);
                if (res.first > mx) {
                    mx = res.first;
                    mxcnt = res.second;
                } elif (res.first == mx) {
                    mxcnt += res.second;
                }
            }
            return {mx+1, mxcnt};
        };
        ll z = centers[0];
        vector<ll> mxcnts;
        for (auto w : nodes[z]) {
            auto res = dfs(dfs, w, z);
            // この部分木の最遠点が外周なら使える
            if (res.first == diam/2) {
                mxcnts.eb(res.second);
            }
        }
        assert(diam%2 == 0);
        mint ans = 1;
        for (auto c : mxcnts) {
            ans *= c + 1;
        }
        ans -= sum(mxcnts) + 1;
        print(ans);
    } else {
        auto dist0 = bfs(nodes, {centers[0]});
        auto dist1 = bfs(nodes, {centers[1]});
        ll mx0 = max(dist0), mx1 = max(dist1);
        ll mxcnt0 = count(ALL(dist0), mx0);
        ll mxcnt1 = count(ALL(dist1), mx1);
        mint ans = mxcnt0 * mxcnt1;
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
