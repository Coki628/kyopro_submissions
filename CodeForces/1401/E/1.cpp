/*
・dojo set_e_6_8
・自力AC！良い感じ。
・平面走査
・交点が1つ増えると領域の数も増えるみたいな数学典型っぽい話があった気がする。
　それに基づくと、平面走査っぽく数え上げればいいとなる。
　Y側に沿って進んで、X側をBITで管理して、その時残ってる縦線の数だけ区間和取って足す感じ。
　あと、両端に接している線は領域が1個増えるので先に足しておく。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    ll L = 1000000;
    vvpll segs(L+1);
    ll ans = 1;
    rep(i, N) {
        ll y, lx, rx;
        cin >> y >> lx >> rx;
        segs[y].eb(lx, rx);
        if (lx == 0 and rx == L) {
            ans++;
        }
    }
    vvl addx(L+1), remx(L+1);
    rep(i, M) {
        ll x, ly, ry;
        cin >> x >> ly >> ry;
        addx[ly].eb(x);
        remx[ry].eb(x);
        if (ly == 0 and ry == L) {
            ans++;
        }
    }

    BIT<ll> bit(L+1);
    rep(y, L+1) {
        for (auto x : addx[y]) {
            bit.add(x, 1);
        }
        for (auto [lx, rx] : segs[y]) {
            ans += bit.query(lx, rx+1);
        }
        for (auto x : remx[y]) {
            bit.add(x, -1);
        }
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
