/*
・きっちり自力AC！
・インタラクティブ、二分探索
・制約が二分探索。半分ずつ減らせる方法を考えると、
　その区間にお目当てのものがあるのか判定できないと無理だよな、となる。
　そういう目で手元で精査すると、「元位置がその区間内なのが奇数個あったらそっちにある」
　が怪しいと思う。信じて実装してぶん投げると通る。
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

// インタラクティブ用
vector<ll> ask(ll l, ll r) {
    cout << "? " << l+1 << ' ' << r << endl;
    auto res = LIST(r-l);
    rep(i, res.size()) {
        res[i]--;
    }
    return res;
}
void answer(ll i) {
    cout << "! " << i+1 << endl;
}

void solve() {
    ll N;
    cin >> N;

    ll l = 0, r = N;
    while (l+1 < r) {
        ll m = (l+r) / 2;
        auto res = ask(m, r);
        ll okcnt = 0;
        rep(i, res.size()) {
            if (m <= res[i] and res[i] < r) {
                okcnt++;
            }
        }
        // 奇数個合ってる方にある
        if (okcnt%2 == 0) {
            r = m;
        } else {
            l = m;
        }
    }
    answer(l);
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
