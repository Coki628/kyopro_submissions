/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・短く動かすタイプ。遅延セグ木との連携。
　尺取りには悩まなくていいが、セグ木で管理するのが点じゃなくて連結関係なので、
　1つ短くしないといけなくてそこで添字にちょっと悩む。
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

// 区間加算・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = INF;
const ll E = 0;

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<tuple<ll, ll, ll>> WLR;
    rep(i, N) {
        ll l, r, w;
        cin >> l >> r >> w;
        l--, r--;
        WLR.pb({w, l, r});
    }

    sort(ALL(WLR));
    auto [W, L, R] = zip(WLR);
    auto seg = get_lazy_segment_tree(vector<ll>(M - 1, 0), f, g, h, T, E);
    deque<ll> que;
    ll ans = INF, i = 0;
    rep(_, N) {
        while (i < N and seg.query(0, M - 1) == 0) {
            seg.update(L[i], R[i], 1);
            que.pb(i);
            i++;
        }
        if (seg.query(0, M - 1) > 0) {
            chmin(ans, W[que.back()] - W[que.front()]);
        }
        seg.update(L[que.front()], R[que.front()], -1);
        que.pop_front();
    }
    assert(ans < INF);
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
