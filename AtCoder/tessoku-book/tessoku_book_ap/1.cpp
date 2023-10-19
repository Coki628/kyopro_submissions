/*
・オーバーキル。3乗とかOKの制約だけど、
　尺取りと遅延セグ木で線形logに。
　逆に3乗とかで効率の良いやり方が思いつかず。。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    vector<pll> AB;
    rep(i, N) {
        AB.eb(A[i], B[i]);
    }
    sort(ALL(AB));

    deque<ll> que;
    ll M = 100;
    auto seg = get_lazy_segment_tree(vector<ll>(M + 1, 0), f, g, h, T, E);
    ll ans = 0;
    rep(i, N) {
        que.eb(i);
        seg.update(AB[i].second, min(AB[i].second + K, M) + 1, 1);
        while (que.size() and AB[que.back()].first - AB[que.front()].first > K) {
            seg.update(AB[que.front()].second, min(AB[que.front()].second + K, M) + 1, -1);
            que.pop_front();
        }
        chmax(ans, seg.query(0, M + 1));
    }
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
