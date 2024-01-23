/*
・これはMLE。
　遅延セグ木で区間chmin更新するようにしたけど、長さ300のセグ木9万本は多すぎたみたいだ。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間chmin・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return min(a, b); };
auto h = [](ll a, ll b) -> ll { return min(a, b); };
const ll T = INF;
const ll E = INF;

void solve() {
    ll N, H;
    cin >> N >> H;
    vector<ll> X(N);
    cin >> X;
    vector<ll> P(N), F(N);
    rep(i, 1, N) {
        cin >> P[i] >> F[i];
    }
    X.insert(X.begin(), 0);
    P.eb(0);
    F.eb(0);

    auto dp = listnd(N + 1, H + 1, get_lazy_segment_tree(H + 1, f, g, h, T, E));
    dp[0][H].update(0, H + 1, 0);
    rep(i, N) {
        ll dist = X[i + 1] - X[i];
        rep(h1, H + 1) {
            rep(h2, H + 1) {
                if (dp[i][h1][h2] >= INF) continue;
                // 給油しない
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    dp[i + 1][h1 - dist].update(h2 + dist, dp[i][h1][h2]);
                }
                // 行きに給油する
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    dp[i + 1][min(h1 - dist + F[i + 1], H)].update(h2 + dist, dp[i][h1][h2] + P[i + 1]);
                }
                // 帰りに給油する
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    ll l = max(h2 + dist - F[i + 1], 0LL);
                    ll r = h2 + dist;
                    dp[i + 1][h1 - dist].update(l, r, dp[i][h1][h2] + P[i + 1]);
                }
            }
        }
    }
    ll ans = INF;
    rep(h1, H + 1) {
        chmin(ans, dp[N][h1].query(0, h1 + 1));
    }
    if (ans >= INF) ans = -1;
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
