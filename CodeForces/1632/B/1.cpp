/*
・きっちり自力AC！
・MSB、ビットの性質
・ビット演算で最大値の最小化なので、とりあえずMSBをいかに潰すか考えてみる。
　普通に昇順に置いてって、MSB立ってて他が0なやつの隣に0を置くと、
　最大はMSB単体にできる。(そこ以外のMSBは全部打ち消されるので)
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

    ll msb = bit_length(N-1);
    ll i = 1;
    vector<ll> ans;
    while (i < N) {
        if (bit_length(i) == msb) {
            ans.eb(0);
            ans.eb(i);
            i++;
            break;
        }
        ans.eb(i);
        i++;
    }
    while (i < N) {
        ans.eb(i);
        i++;
    }
    print(ans);
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
