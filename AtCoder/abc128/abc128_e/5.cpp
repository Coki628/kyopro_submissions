/*
・当時と違う方針だったので通るか確認。
・イベントソートのキーを時間でなくx座標にすると、
　各座標で該当する工事の両端の範囲内にある人を取得する感じになって、
　これはsetでにぶたん、用済みを削除するとシミュできる。
　これだとイベントとして保持するのは1種類だし、
　範囲取得が縦軸じゃなくて横軸でできるので、自分的には考えやすかった。
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
    ll N, Q;
    cin >> N >> Q;
    vector<array<ll, 3>> events;
    rep(i, N) {
        ll s, t, x;
        cin >> s >> t >> x;
        events.pb({x, s, t});
    }
    sort(ALL(events));
    vector<ll> D(Q);
    cin >> D;
    map<ll, ll> dtoi;
    rep(i, Q) {
        dtoi[D[i]] = i;
    }
    set<ll> se(ALL(D));

    vector<ll> ans(Q, -1);
    for (auto [x, s, t] : events) {
        // 座標xに各人が着く時刻は、全員起点が座標0なので全体に+xしたとみなせる
        auto l = se.lower_bound(s - x);
        auto r = se.lower_bound(t - x);
        vector<ll> tmp;
        for (auto itr = l; itr != r; itr++) {
            ll d = *itr;
            tmp.eb(d);
        }
        for (auto d : tmp) {
            se.erase(d);
            ans[dtoi[d]] = x;
        }
    }
    print(ans, '\n');
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
