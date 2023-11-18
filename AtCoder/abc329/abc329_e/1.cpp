/*
・きっちり自力AC！
・上書きは逆操作、キューでシミュ
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

void solve() {
    ll N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;

    auto check = [&](ll i) {
        if (i < 0 or i + M > N) return false;
        rep(j, i, i + M) {
            if (S[j] != '#' and S[j] != T[j - i]) {
                return false;
            }
        }
        rep(j, i, i + M) {
            S[j] = '#';
        }
        return true;
    };
    Deque<ll> que;
    vector<ll> visited(N);
    rep(i, N - M + 1) {
        if (check(i)) {
            visited[i] = true;
            que.pb(i);
        }
    }
    while (que.size()) {
        auto i = que.pop_front();
        rep(j, i - M + 1, i) {
            if (j < 0 or visited[j]) continue;
            if (check(j)) {
                visited[j] = true;
                que.pb(j);
            }
        }
        rep(j, i + 1, i + M) {
            if (j >= N or visited[j]) continue;
            if (check(j)) {
                visited[j] = true;
                que.pb(j);
            }
        }
    }
    string goal(N, '#');
    if (S == goal) {
        Yes();
    } else {
        No();
    }
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
