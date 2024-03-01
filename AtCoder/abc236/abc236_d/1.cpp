/*
・きっちり自力AC！
・マッチング、再帰全探索
・全探索っぽいけど間に合うのか？となる。
　最大の16人で考えると、ペア決まるたび2人ずつ減るので15*13*11*..=約200万、
　であれば行けそう？と恐る恐る再帰全探索を書いて投げると無事AC。
　ちょっと書き方悩んだけど、片側を決めておいて、逆側を試す時に潜る、ってやった。
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
    N *= 2;
    auto mat = list2d(N, N, 0LL);
    rep(i, N) {
        rep(j, i+1, N) {
            cin >> mat[i][j];
            mat[j][i] = mat[i][j];
        }
    }

    vector<bool> used(N);
    ll ans = 0;
    auto rec = [&](auto&& f, ll d, ll cur) -> void {
        if (d == N/2) {
            chmax(ans, cur);
            return;
        }
        ll a = -1, b = -1;
        rep(i, N) {
            if (not used[i]) {
                a = i;
                used[a] = true;
                break;
            }
        }
        if (a == -1) return;
        rep(i, N) {
            if (not used[i]) {
                b = i;
                used[b] = true;
                f(f, d+1, cur^mat[a][b]);
                used[b] = false;
            }
        }
        used[a] = false;
    };
    rec(rec, 0, 0);
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
