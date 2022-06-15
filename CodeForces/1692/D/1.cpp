/*
・自力AC。ちゃんと考えたら解けたけど、ちょっとだるそうに見えて1回飛ばした。
・ある開始位置から、mod 24*60の世界を+=Xしてぐるぐる回る感じになるので、
　訪問済に当たるまで回す。その間で条件に当てはまった数を数えればいい。
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

bool is_palindrome(ll t) {
    auto [h, m] = divmod(t, 60LL);
    return zfill(tostr(h), 2) == reversed(zfill(tostr(m), 2));
}

void solve() {
    string S;
    ll X;
    cin >> S >> X;

    auto tmp = split(S, ':');
    ll cur = tmp[0]*60 + tmp[1];
    ll mod = 24 * 60;
    vector<ll> visited(mod);
    ll ans = 0;
    while (not visited[cur]) {
        if (is_palindrome(cur)) {
            ans++;
        }
        visited[cur] = true;
        cur = (cur+X) % mod;
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
