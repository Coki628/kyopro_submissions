/*
・きっちり自力AC！
・整数BFS
・よく見ると制約が100万までで、取りうる状態は列挙できる。
　整数BFSを適切にやれればOK。
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
    ll a, N;
    cin >> a >> N;

    const ll M = 1000000;
    vector<ll> memo(M, -1);
    queue<ll> que;
    memo[1] = 0;
    que.push(1);
    while (que.size()) {
        ll cur = que.front(); que.pop();
        ll nxt = cur*a;
        if (nxt < M and memo[nxt] == -1) {
            memo[nxt] = memo[cur]+1;
            que.push(nxt);
        }
        string s = tostr(cur);
        if (s.size() >= 2 and s.back() != '0')  {
            s = s.back()+s.substr(0, s.size()-1);
            nxt = toint(s);
            if (memo[nxt] == -1) {
                memo[nxt] = memo[cur]+1;
                que.push(nxt);
            }
        }
    }
    print(memo[N]);
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
