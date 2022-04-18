/*
・dojo set_e_6_5
・きっちり自力AC！
・遅延セグ木、区間加算・区間最大値取得、後ろから決める、inplace DP
・後ろから順に確定させていく。自分より先で届く範囲の中で最大値を取る。
　ただし、前に戻るにつれて、先のものは1個ずつ得になっていくので、それを考慮する。
　1歩下がる毎に、自分より先の全体を+1することで帳尻が合う。
　これをやるために、区間加算・区間最大値取得の遅延セグ木を使う。
　後は答えのために元index持ちながらソートするとか、
　自分が何個先まで届くかをにぶたんとかでチェックしておくとか、そんな感じでいける。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/LazySegmentTree.hpp"

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

void solve() {
    ll N;
    cin >> N;
    vector<tuple<ll, ll, ll>> tp;
    rep(i, N) {
        ll x, h;
        cin >> x >> h;
        tp.eb(x, h, i);
    }
    sort(ALL(tp));
    auto [X, H, ids] = zip(tp);

    vector<ll> R(N);
    rep(i, N) {
        R[i] = bisect_left(X, X[i]+H[i]);
    }
    auto seg = get_lazy_segment_tree(f, g, h, T, E);
    seg.build(vector<ll>(N+1, 0));
    vector<ll> ans(N);
    rep(i, N-1, -1, -1) {
        ans[ids[i]] = seg.query(i, R[i]) + 1;
        seg.update(i, ans[ids[i]]);
        seg.update(i+1, N+1, 1);
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
