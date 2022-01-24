/*
・きっちり自力AC！
・順列
・大きい要素を消すのが大変なのでそこから考える。降順ソートして大きい方から決める。
　すると、自分より手前は全部消せるので消す。
　ただしこの中で最小のやつを最後にやってその時自分が消えるとする。
　その最小要素より大きいのが後ろに残ってなければNG。
・大きいやつがいるか判定はサボってセグ木にしたけど、
　別に更新ないし端からだけなので、多分累積maxとかで大丈夫。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto A = LIST(N);
    rep(i, N) A[i]--;

    vector<pll> AI;
    rep(i, N) {
        AI.eb(A[i], i);
    }
    sort(AI.rbegin(), AI.rend());
    auto seg = get_segment_tree([](ll a, ll b) { return max(a, b); }, -INF);
    seg.build(A);

    vector<bool> used(N);
    ll j = 0, mn = INF;
    for (auto [a, i] : AI) {
        if (used[i]) continue;
        while (j < i) {
            used[j] = true;
            chmin(mn, A[j]);
            j++;
        }
        if (i != N-1 and seg.query(i+1, N) < mn) {
            NO();
            return;
        }
        used[j] = true;
        j++;
    }
    YES();
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
    while (T--) solve();

    return 0;
}
