/*
・きっちり自力AC！
・題意の数は列挙できる。そう多くない。
　実装ちょっと面倒だったけど、桁数 → 先頭桁 → 差分 と順にループさせた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll X;
    cin >> X;

    if (X < 10) {
        print(X);
        return;
    }

    vector<ll> V;
    rep(len, 2, 19) {
        rep(a, 1, 10) {
            rep(d, -9, 10) {
                string s = tostr(a);
                ll i = 1;
                while (1) {
                    ll nxt = a+d*i;
                    if (nxt >= 10 or nxt < 0) break;
                    s += tostr(nxt);
                    if (s.size() == len) {
                        V.eb(toint(s));
                        break;
                    }
                    i++;
                }
            }
        }
    }
    ll res = *lower_bound(ALL(V), X);
    print(res);
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
