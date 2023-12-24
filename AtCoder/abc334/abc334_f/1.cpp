/*
・なんとか自力AC！
・in-place DP、遅延セグ木、区間加算・区間最小値取得
・普通にDPしようとすると、Kの添字が必要になり厳しい。
　なんとか遷移をまとめられないか検討すると、
　「一度サンタの家に帰る」の部分でひと区切りとすると良さそう。
　これならKのことは考えなくて済む。後は遷移時のコストで、
　これも普通にやると遷移元によって必要コストが変わってしまうので厳しそうに思える。
　で、これは1つ添字を進めた時に増える所要コストが一定なのを利用して、
　今までの部分全てにまとめてコスト加算しておくといい。
　ここまで整えば考察としてはOKで、後は実装なんだけど、
　出発時と最後にサンタの家に帰る時に微妙に処理を変えなきゃだったりで、
　添字合わせがなかなかしんどかった。。
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

#include "geometry/Point.hpp"
#include "datastructure/LazySegmentTree.hpp"

// 区間加算・区間最小値取得
auto f = [](ld a, ld b) -> ld { return min(a, b); };
auto g = [](ld a, ld b) -> ld { return a + b; };
auto h = [](ld a, ld b) -> ld { return a + b; };
const ld T = INF;
const ld E = 0;

void solve() {
    ll N, K;
    cin >> N >> K;
    ld sx, sy;
    cin >> sx >> sy;
    Point<ld> s({sx, sy});
    vector<Point<ld>> P;
    rep(i, N) {
        ld x, y;
        cin >> x >> y;
        P.eb(x, y);
    }

    vector<ld> dist;
    dist.eb(s.abs(P[0]));
    rep(i, N - 1) {
        dist.eb(P[i].abs(P[i + 1]));
    }
    dist.eb(P[N - 1].abs(s));
    // dp[i] := 子どもiの直前で家に戻って最後にiに配った状態の最小コスト
    auto dp = get_lazy_segment_tree(vector<ld>(N), f, g, h, T, E);
    dp.update(0, dist[0]);
    rep(i, 1, N) {
        ld tosanta = P[i - 1].abs(s);
        ld fromsanta = s.abs(P[i]);
        ld mn = dp.query(max(i - K, 0LL), i);
        dp.update(i, mn + tosanta + fromsanta);
        dp.update(0, i, dist[i]);
    }
    ld ans = dp.query(max(N - K, 0LL), N) + dist[N];
    print(ans);
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
