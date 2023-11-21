/*
・ランダムケース用愚直解。
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

#include "string/is_palindrome.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    map<string, ll> dist;
    Deque<string> que;
    dist[S] = 0;
    que.pb(S);
    while (que.size()) {
        auto cur = que.pop_front();
        rep(i, N) {
            rep(j, i + 1, N) {
                auto nxt = cur;
                swap(nxt[i], nxt[j]);
                if (not dist.count(nxt)) {
                    dist[nxt] = dist[cur] + 1;
                    que.pb(nxt);
                }
            }
        }
    }
    ll ans = INF;
    for (auto [s, v] : dist) {
        bool ok = true;
        rep(i, ceil(N, 2LL)) {
            ll j = N - i - 1;
            if (s[i] == s[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            chmin(ans, v);
        }
    }
    if (ans >= INF) ans = -1;
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
